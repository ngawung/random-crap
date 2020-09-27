FROM mono:6.8


RUN apt-get update
RUN apt-get install -y unzip wget

ADD https://github.com/Fe7n/TShockMobile/releases/download/v4.3.26.1/TShock.Mobile.4.3.26.1.zip .
RUN unzip TShock.Mobile.4.3.26.1.zip
RUN rm TShock.Mobile.4.3.26.1.zip

RUN mv "TShock Mobile 4.3.26.1" tshock && \
    mkdir -p /tshock/config && \
    mkdir -p /tshock/log && \
    mkdir -p /tshock/ServerPlugins

ADD /ServerPlugins/* /tshock/ServerPlugins

WORKDIR /tshock

ENTRYPOINT ["mono", "TerrariaServer.exe", "-configpath", "/tshock/config", "-logpath", "/tshock/log"]