

![GitHub Logo](logo_small0.jpg)

### ABOUT
VoIP perf

It is a SIP signaling performance testing application that can provide a server and a client.
It can produce latency stats at specified intervals in csv to measure the response time of any SIP endpoint.
It can also read a json configuration file and randomize numbers.



### Docker quick start
[quick start with docker](QUICK_START.md)

### Linux Debian building from sources
[see commands in Dockerfile](docker/Dockerfile)

### Example : starting a server

```bash
./voip_perf  \
   --local-port=5072 \     # server listening port
   --trying \              # when receiving invite 100 trying will be send
   --ringing \             # when receiving invite 183 will be sent
   --thread-count=4 \      # number of server threads created
   --duration=10000       # ringing delay 1 second
```
### Example : starting a client

This will send one INVITE to a randomise number starting with +1206?????? to server 1.1.1.1

```bash
./voip_perf \
  "sip:+1206???????@1.1.1.1" \ # target R-URI, <?> will be replaced by random digit
  --method="INVITE" \          # method
  --local-port=5072 \          # source port
  --caller-id="+1??????????" \ # user part of the From header, <?> will be replaced by random digit
  --count=1 \                 # total calls to send
  --proxy=2.2.2.2 \           # this will send the SIP message to a SIP proxy instead of the host in R-URI
  --duration=5 \              # send BYE after 5 seconds
  --call-per-second=500 \     # send 500cps
  --window=100000 \           # maximum amount of in progress calls
  --thread-count=1 \          # number of thread used
  --interval=1 \              # reporting interval, everyone second a line is added to voip_perf_stats.log with latency metrics
  --timeout 7200              # total run time , if all the requests where not send, voip_perf will stop and report scnenario timeout
# --verbose                   # runwith verbose logs
```

### Example : starting a client with TLS

```bash
./voip_perf "sip:+1??????????@sip.domain.com:5061;transport=tls" \
	--local-port=5050 \
	--method="INVITE" \
	--caller-id="+1??????????" \
	--interval=1 \
	--count=20 \
	--call-per-second=10 \
	--window=25 \
	--thread-count=1 \
	--use-tls \
	--timeout 7200 \
	--tls-cert="tls/certificate.pem" \
	--tls-key="tls/key.pem" \
	--tls-calist="tls/ca_list.pem" \
	--conf="conf.json"
#	--verbose \
```

### Example : config in json file

```json
{
	"server" : [
		{
			"response" : [
				{ "code" : 200,
				  "reason" : "OK",
				  "probability" : 1.0
				}
			]
		}
	],
	"client" : [
		{
			"extra-headers" : [
				{ "Foo" : "Bar",
				  "Bar" : "Foo"
				}
			]
		},{
			"users" : [
				{ "ruri" : "sip:1106388????@192.168.10.10" },
				{ "ruri" : "sip:1206388????@192.168.11.11" },
				{ "ruri" : "sip:1306388????@192.168.10.10:5060" }
			]
		}
	]
}
```

### Example : adding headers from a C header file

You can add custom headers in this file
```
include/custom_headers.h
```

### Additional notes

voip_perf was initially a fork from pjsip-apps/src/samples/pjsip-perf.c

http://www.pjsip.org/release/0.5.4/PJSIP-Dev-Guide.pdf
