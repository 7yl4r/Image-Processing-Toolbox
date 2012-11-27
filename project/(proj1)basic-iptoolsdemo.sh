#!/bin/bash
inFile="./../../LAB1/DIPlab1/D1.png"

read c
echo " === simple 'add' === "
echo `./bin/iptool $inFile demo_add.pgm roi.txt add 100`

echo " === gray thresholding 'graythresh' === "
echo `./bin/iptool images_for_demo/boats.pgm demo_graythresh.pgm roi.txt graythresh 100`

echo " === scaling up 200% or 400% 'scale' === "
echo `./bin/iptool images_for_demo/blobs.pgm demo_scaleUp.pgm ALL scale 400`

echo " === scaling down 50% or 25% 'scale' === "
echo `./bin/iptool images_for_demo/auditorium.pgm demo_scaleDown.pgm ALL scale 25`

echo " === color thresholding 'colorthresh' === "
echo `./bin/iptool images_for_demo/Lena.ppm demo_colorthreshLena.ppm roi.txt colorthresh 200 250 0 250`
echo `./bin/iptool images_for_demo/micro.ppm demo_colorthreshMicro.ppm roi.txt colorthresh 100 0 0 100`

echo " === 2d smoothing '2dSmooth' ==="
echo `./bin/iptool images_for_demo/closet.pgm demo_2dSmooth.pgm roi.txt smooth2d 15`

echo " === 1d smoothing into 2d using convolution '1dSmooth' ==="
echo `./bin/iptool images_for_demo/closet.pgm demo_1dSmooth.pgm roi.txt smooth1d 15`

echo " === weighted variable threshold 'adaptivethresh' ==="
echo `./bin/iptool images_for_demo/baboon.pgm demo_adaptiveThreshBaboon.pgm roi.txt adaptivethresh 5 30`
echo `./bin/iptool images_for_demo/micro2.pgm demo_adaptiveThreshMicro.pgm roi.txt adaptivethresh 5 30`



echo "Images have been stored in the project directory. Press enter to begin the video processing demo."
read c

echo " === color thresholding of video 'colorthresh' === "
echo `./bin/iptool videos_for_demo/demo_short.mpeg demo_colorThreshVideo.avi foi.txt colorthresh 100 150 200 150`

echo "Video file has been written to project directory."
