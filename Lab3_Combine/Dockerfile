FROM ubuntu
RUN apt-get update && apt-get install g++ -y
RUN apt-get install g++-multilib -y
COPY ./Combine.cpp /home/Combine.cpp
COPY ./run.sh /home/run.sh
WORKDIR /home
ENTRYPOINT ["sh","./run.sh"]