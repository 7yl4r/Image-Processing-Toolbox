#!/bin/bash
inFile="./sample.jpg"

echo " === gray thresholding 'graythresh' === "
echo `./bin/iptool $inFile demo_graythresh.ppm roi.txt graythresh 200`

echo " === color thresholding 'colorthresh' === "
echo `./bin/iptool $inFile demo_colorthresh.ppm roi.txt colorthresh 100 250 250 0`


echo " === 1d smoothing into 2d using convolution '1dSmooth' ==="
echo `./bin/iptool $inFile demo_1dSmooth.pgm roi.txt smooth1d 121`

echo " === weighted variable threshold 'adaptivethresh' ==="
echo `./bin/iptool $inFile demo_adaptiveThresh.ppm roi.txt adaptivethresh 5 10`

echo " === GreyScale Histogram Equalization 'equalizeGrey' ==="
echo `./bin/iptool $inFile demo_equalizeGrey.ppm roi.txt equalizeGrey`

echo " === Color Histogram Equalization using HSI color space 'equalizeIntensity' ==="
echo `./bin/iptool $inFile demo_equalizeIntensity.ppm roi.txt equalizeIntensity`

echo "=====GreyScale Thresholded Sobel Operator Edge Detection 'edgeDetect'====="
gnome-terminal -e "./bin/iptool $inFile demo_edgeDetectColor.ppm roi.txt edgeDetect 300"

gnome-terminal -e "./bin/iptool $inFile demo_gradMagnitudeDisplay.ppm roi.txt edgeDetect"

echo "done."
