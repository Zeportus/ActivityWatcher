from fastapi import FastAPI, Request
from fastapi.responses import RedirectResponse, FileResponse, StreamingResponse
from fastapi.templating import Jinja2Templates
from pydantic import BaseModel
import base64
import io
import uvicorn

users = {}
templates = Jinja2Templates(directory='')

class User:
    def __init__(self, username, machine, ip, screenshot, domain, last_activity):
        self.username = username
        self.machine = machine
        self.ip = ip
        self.screenshot = base64.b64decode(screenshot)
        if not domain: self.domain = 'workgroup'
        else: self.domain = domain

        self.h = last_activity // 3600
        self.m = last_activity // 60
        self.s = last_activity % 60

    def update(self, last_activity, screenshot):
        self.screenshot = base64.b64decode(screenshot)
        self.h = last_activity // 3600
        self.m = last_activity // 60
        self.s = last_activity % 60

class Activity(BaseModel):
    last_activity: int
    domain: str
    machine: str
    username: str
    screenshot: str

app = FastAPI()

@app.post('/activity_report')
def activity_report(activity: Activity, request: Request):
    user_comp_key = (activity.machine, activity.username)
    if user_comp_key not in users:
        users[user_comp_key] = User(activity.username, activity.machine, request.client.host, activity.screenshot, activity.domain, activity.last_activity)
    else:
        users[user_comp_key].update(activity.last_activity, activity.screenshot)

    print(activity.domain, activity.machine, request.client.host, activity.username, sep=' / ')
    h = activity.last_activity // 3600
    m = activity.last_activity // 60
    s = activity.last_activity % 60
    print(f'Last activity H:{h} M:{m} S:{s}')


@app.post('/update')
def update(request: Request):
    return RedirectResponse('/', 302)

@app.get('/screenshot/{machine}/{username}')
def screenshot(machine, username):
    user_comp_key = (machine, username)
    user = users[user_comp_key]
    return StreamingResponse(io.BytesIO(user.screenshot))

@app.get('/')
def main(request: Request):
    return templates.TemplateResponse('index.html', {'request' : request, 'users' : users.values()})

uvicorn.run(app, host='0.0.0.0')