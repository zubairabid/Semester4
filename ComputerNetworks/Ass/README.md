# Simple Proxy Server

**Authors:** Athreya Chandramouli (2018121002), Zubair Abid (20171076)

## How to Use
Open at least three terminals.

Proxy Server
```
cd proxy 
python3 proxyServer.py 20100
```

You can do multiple clients, multiple terminals per client
```
cd client
python3 proxyClient.py 20100
```

Destination Server
```
cd server
python2 server.py 7205
```
**Note:** Server makes use of SimpleHttpServer

## Features Implemented
 - Threaded Proxy Server
 - Cache, with Validation and Cache-Control Header support
 - Blacklisting, CIDR format
 - Basic Access Authentication
 - Graceful Error Handling

