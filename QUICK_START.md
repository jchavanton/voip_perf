## Quick start with docker

### cloning voip_perf
(only needed to get the shell scripts to build your own image)
```
git clone https://github.com/jchavanton/voip_perf.git
```

### example: building docker image
(optional, you can pull unless you want to build your own image)
```
cd voip_perf/docker
./build_image.sh
```

### example: pulling image from dockerhub
```
docker pull jchavanton/voip_perf:latest
```

### example: running the container
```
cd voip_perf/docker
./run.sh
```
#### or use the following
```bash
#!/bin/sh
IMAGE=voip_perf:latest
CONTAINER_NAME=voip_perf
docker run -d --net=host --name=${CONTAINER_NAME} ${IMAGE}
```

### done, voip_perf should running as a server on 5060 !
```
docker logs voip_perf
voip_perf 0.5.2 started in server-mode
Receiving requests on the following URIs:
  sip:0@192.168.0.111:5060    for stateless handling
  sip:1@192.168.0.111:5060    for stateful handling
  sip:2@192.168.0.111:5060    for call handling
INVITE with non-matching user part will be handled call-statefully
Total(rate): stateless:0 (0/s), statefull:0 (0/s), call:0 (0/s)
Total(rate): stateless:0 (0/s), statefull:0 (0/s), call:0 (0/s)
```
