FROM ubuntu:18.04
LABEL maintainer="chriamue@gmail.com"
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y build-essential clang git cmake \
	qt5-default qttools5-dev qttools5-dev-tools libboost-system-dev libboost-filesystem-dev libboost-python-dev python-numpy \
	libopencv-dev libpoco-dev libdlib-dev

RUN cd / && git clone https://github.com/annotatorproject/annotatorlib
RUN cd /annotatorlib && mkdir build && cd build \
    && cmake -DCMAKE_BUILD_TYPE=Release .. \
	&& make -j3 && make install && ldconfig \
	&& ln -s /usr/local/lib/pyannotatorlib.so /usr/lib/python2.7/pyannotatorlib.so

RUN cd /annotatorlib/source/imagesets && git clone https://github.com/annotatorproject/annotatorimageset_flickr \
    && cd ../../build && cmake .. && make -j3 && make install && ldconfig
