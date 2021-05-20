#!/bin/sh

palette="/home/melody/workspace/random-crap/bad/video/palette.png"
video="video.mp4"
output="out.gif"

filters="fps=30,scale=256x192"
skip="-t 1 -ss 00:15"

ffmpeg -t 1 -ss 00:15 -i $video -vf "$filters,palettegen=max_colors=256:reserve_transparent=" -y $palette
ffmpeg -t 1 -ss 00:15 -i $video -i $palette -lavfi "$filters [x]; [x][1:v] paletteuse=dither=none" -y $output
