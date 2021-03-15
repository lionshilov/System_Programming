FROM ubuntu
RUN apt-get -y update
RUN apt-get -y install gcc
RUN apt-get -y install gcc-multilib
COPY ./ccode/ccode.c /home/ccode/ccode.c
COPY ./gascode/simple_prog.s /home/gas/code/simple_prog.s
ENTRYPOINT /bin/bash