# ActivityWatcher
This is only works in LAN  
You must forwarding port 8000 on your router to port 8000 on your machine, where server will be running  
Do instruction step by step (row by row)  
  
## Run server
You must install python3.11 or later.  
For easy way to start - i recomend to download PyCharm.  
Open server folder in PyCharm.  
  
Go to terminal and execute this command:
<code>pip3 install requirments.txt</code>   
  
After this you may run server. Just run main.py for this:  
<code>python3 main.py</code>  
Or from your IDE  
  
## Run client
When server is running, you may run clients, which needs to be watched.  
  
Git must be installed on your machine.  
You can download it from official site or with PowerShell:  
<code>winget install --id Git.Git -e --source winget</code>  
  
For easy way to start - i recomend install Visual Studio 2022 or later and C++ (17 or later) components (Use default params) on your machine.  
### VERY IMPORTANT: Create dev folder in root of disk C ("C://dev/")   
  
Input in server_ip.txt file an ip of the server.  
Go to and run client/out/build/x64-debug/ActivityWatcherCMake/ActivityWatcherCMake.exe  
  
## Interface
Visit: http://your_server_ip:8000/  
Interface is simple
