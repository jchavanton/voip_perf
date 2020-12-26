#!/bin/bash

export PORT=${PORT=5060}
export PARAMS=${PARAMS=" --trying --ringing --delay=250"}

if [ "$1" = "" ]; then
	CMD="/voip_perf/voip_perf --local-port ${PORT} ${PARAMS}"
else
	CMD="$*"
fi

echo "Running ${CMD}"
exec ${CMD}
