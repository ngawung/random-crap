FROM mono:6.8


ADD https://github.com/Pryaxis/TShock/releases/download/v4.4.0-pre12/TShock4.4.0_Pre12_Terraria1.4.0.5.zip /tshock/

WORKDIR /tshock

RUN apt-get update && \
	apt-get install -y unzip wget && \
	unzip TShock4.4.0_Pre12_Terraria1.4.0.5.zip && \
	rm TShock4.4.0_Pre12_Terraria1.4.0.5.zip && \
#	mv "TShock Mobile 4.3.26.1" tshock && \
    mkdir -p /tshock/config && \
    mkdir -p /tshock/log && \
    mkdir -p /tshock/ServerPlugins

ADD /ServerPlugins/* /tshock/ServerPlugins

ENV PORT "7777"

ENTRYPOINT ["mono TerrariaServer.exe -autocreate 1 -world LonelyEskrim.wld -port 7777 -ip 0.0.0.0 -maxplayers 3"]