# ActivityWatcher
This is only works in LAN  
You must forwarding port 8000 on your router to port 8000 on your machine, where server will be running

## Run server
To run the server firstly you must install requirments:  
<code>pip3 install requirments.txt</code>   
  
After this you may run server. Just run main.py for this:  
<code>python3 main.py</code>  

## Run client
When server is running, you may run clients, which needs to be watched.  
You must use C++ 17 or later.  
  
Input in server_ip.txt file an ip of the server.  
Go to and run client/out/build/x64-debug/ActivityWatcherCMake/ActivityWatcherCMake.exe  

## Interface
Visit: http://your_server_ip:8000/  
Interface is simple

# Main problems
If you don't wanna headache with C++ settings - just download Visual Studio and install C++ component.  
For python you need to install python of course and you may not use IDE, but i recomend to install PyCharm.
