#!/bin/bash

rm -f shot0001.png
mplayer -vf screenshot tv://0 # save frame from camera to file
tesseract shot0001.png out -psm 1 characters # open file to decode
cat out.txt
