#!/bin/sh

palette="/home/melody/Desktop/bad/video/palette.png"
video="video.mp4"
output="out.gif"

filters="fps=30,scale=256x172"

ffmpeg -t 10 -ss 00:10 -i $video -vf "$filters,palettegen" -y $palette
ffmpeg -t 10 -ss 00:10 -i $video -i $palette -lavfi "$filters [x]; [x][1:v] paletteuse=dither=none" -y $output
