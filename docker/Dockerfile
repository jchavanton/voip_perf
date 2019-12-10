FROM alpine:3.8

RUN echo "building VoIP Perf" \
	&& apk update && apk add git cmake g++ cmake make curl-dev alsa-lib-dev jansson jansson-dev \
	&& mkdir /git && cd /git && git clone https://github.com/jchavanton/voip_perf.git \
	&& cd voip_perf && git checkout master \
	&& git submodule update --init \
	&& cd pjsua && ./configure && make dep && make && make install \
	&& cd .. && cmake CMakeLists.txt && make
