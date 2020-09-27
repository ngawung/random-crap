docker run --rm -ti \
-v ~/Desktop/tshock-demo/config:/tshock/config \
-v ~/Desktop/tshock-demo/world:/tshock/Worlds \
-v ~/Desktop/tshock-demo/log:/tshock/log \
-v ~/Desktop/tshock-demo/plugin:/tshock/ServerPlugins \
-p "7777:7777" -p "7878:7878" \
--memory="4g" --cpus="1.0" \
--name tshock tshock-mobile