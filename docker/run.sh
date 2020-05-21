#!/bin/bash
IMAGE=voip_perf:latest
CONTAINER_NAME="voip_perf"

docker run -d --net=host \
    --name=voip_perf \
    ${IMAGE}
