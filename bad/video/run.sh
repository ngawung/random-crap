#!/bin/sh

palette="/home/melody/Desktop/random-crap/bad/video/palette.png"
video="video.mp4"
output="out.gif"

filters="fps=3,scale=16x9"
skip="-t 1 -ss 00:15"

ffmpeg  -i $video -vf "$filters,palettegen=max_colors=4:reserve_transparent=" -y $palette
ffmpeg  -i $video -i $palette -lavfi "$filters [x]; [x][1:v] paletteuse=dither=none" -y $output
