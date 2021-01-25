#!/bin/sh

palette="/home/melody/Desktop/github/random-crap/bad/video/palette.png"
video="video.mp4"
output="out.gif"

filters="fps=30,scale=256x192"
skip="-t 1 -ss 00:10"

ffmpeg  -i $video -vf "$filters,palettegen" -y $palette
ffmpeg  -i $video -i $palette -lavfi "$filters [x]; [x][1:v] paletteuse=dither=none" -y $output
