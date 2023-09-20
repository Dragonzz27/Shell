FROM ubuntu:20.04

RUN apt update && apt upgrade
RUN apt install gcc g++ make cmake git -y
RUN apt install libtinfo-dev libreadline-dev -y

ADD . /shell

WORKDIR /shell/build

RUN cmake ..
RUN make

ENTRYPOINT [ "shell" ]