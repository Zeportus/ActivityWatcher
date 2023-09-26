# CMakeList.txt: проект CMake для ActivityWatcherCMake; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (ActivityWatcherCMake "ActivityWatcherCMake.cpp"  "base64.cpp" "base64.h")



if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ActivityWatcherCMake PROPERTY CXX_STANDARD 20)
endif()

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG 0817715923c9705e68994eb52ef9df3f6845beba) # The commit hash for 1.10.x. Replace with the latest from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

target_link_libraries(ActivityWatcherCMake PRIVATE cpr::cpr)
# TODO: Добавьте тесты и целевые объекты, если это необходимо.
