FROM ubuntu:18.04

ADD jdk-8u261-linux-i586.tar.gz /usr/lib/jvm/

RUN dpkg --add-architecture i386 && \
	apt-get update -y && \
	apt-get upgrade -y && \
	apt-get install -y ant && \
	apt-get install -y libc6:i386 libstdc++6:i386 libxext6:i386 libxrender1:i386 libxtst6:i386 libxi6:i386 libxt6:i386 && \
	update-alternatives --install "/usr/bin/java" "java" "/usr/lib/jvm/jdk1.8.0_261/bin/java" 5000 && \
	mkdir -p ngawung && \
	apt-get clean

ADD /sunwtktoolkit ngawung/sunwtktoolkit
ADD /antenna-bin-1.2.1-beta.jar ngawung/antenna.jar

ENTRYPOINT ["ant", "-Dantenna.lib=/ngawung/antenna.jar", "-Dwtk.home=/ngawung/sunwtktoolkit"]

