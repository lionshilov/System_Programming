FROM ubuntu
RUN apt-get -y update
RUN apt-get -y install imagemagick
COPY ./convert_resize.sh /home/script.sh
COPY ./image1.png /home/input/image1.png
COPY ./image1.png /home/output/image1.png
ENTRYPOINT /bin/bash