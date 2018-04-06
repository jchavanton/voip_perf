### ABOUT
voip_perf is initially a fork from pjsip-apps/src/samples/pjsip-perf.c

It is a complete program to measure the
 performance of PJSIP or other SIP endpoints. It consists of two
 parts:
   - the server, to respond incoming requests, and
   - the client, who actively submits requests and measure the
      performance of the server.

 Both server and client part can run simultaneously, to measure the
 performance when both endpoints are co-located in a single program.

 The server accepts both INVITE and non-INVITE requests.
 The server exports several different types of URL, which would
 control how the request would be handled by the server:
 *  URL with "0" as the user part will be handled statelessly.
     It should not be used with INVITE method.
 *  URL with "1" as the user part will be handled statefully.
     If the request is an INVITE request, INVITE transaction will
     be created and 200/OK response will be sent, along with a valid
     SDP body. However, the SDP is just a static text body, and
     is not a proper SDP generated by PJMEDIA.
 *  URL with "2" as the user part is only meaningful for INVITE
     requests, as it would be handled call-statefully by the
     server. The URL can also use random number using 
     this syntax sip:+1??????????@server.com
     For this URL, the server also would generate SDP dynamically
     and perform a proper SDP negotiation for the incoming call.
     Also for every call, server will limit the call duration to
     10 seconds, on which the call will be terminated if the client
     doesn't hangup the call.

 The client will generate SIP responses latency metrics at defined interval in CSV format.


### INSTALLATION (example ubuntu)

```
apt-get install build-essential
apt-get install libcurl4-openssl-dev
apt-get install cmake
apt-get install git
apt-get install libasound2-dev
apt-get install pkg-config

git clone https://github.com/jchavanton/voip_perf.git
cd voip_perf
git submodule update --init
cd pjsua/
./configure
make dep
make
make install
cd ..
cmake CMakeLists.txt
make

./voip_perf
```

### ADDING CUSTOM HEADERS

You can add custom headers in this file
```
include/custom_headers.h
```

### Example : starting a server

```bash
./voip_perf  \
   -p 5072 \               # server listening port
   --trying \              # when receiving invite 100 trying will be send
   --ringing \             # when receiving invite 183 will be sent
   --thread-count=4 \      # number of server threads created
   -d 10000                # ringing delay 1 second

```

### Example : starting a client

This will send one INVITE to a randomise number starting with +1206?????? to server 1.1.1.1

```bash
./voip_perf \
  -m INVITE \                 # method
  -p 5072 \                   # source port
  sip:+1206???????@1.1.1.1 \  # target R-URI, <?> will be replaced by random digit
  --count=1 \                 # total calls to send
  --proxy=2.2.2.2 \           # this will send the SIP message to a SIP proxy instead of the host in R-URI
  --duration=5 \              # send BYE after 5 seconds
  --call-per-second=500 \     # send 500cps
  --window=100000 \    # maximum amount of in progress calls
  --thread-count=1 \   # number of thread used
  --interval=1 \       # reporting interval, everyone second a line is added to voip_perf_stats.log with latency metrics
  -t 7200              # total run time , if all the requests where not send, voip_perf will stop and report scnenario timeout
```
