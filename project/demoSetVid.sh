#!/bin/bash
inFile="sample.jpg"

echo " === color thresholding of video 'colorthresh' === "
echo `./bin/iptool $inFile demo_colorThreshVideo.mp4 foi.txt colorthresh 100 150 200 150`

echo "=== Histogram Equalization of Video 'equalizeIntensity' ==="
echo `./bin/iptool $inFile demo_equalizeIntensity.mp4 foi.txt equalizeIntensity`

echo " === edgeDetect === "
gnome-terminal -e "./bin/iptool $inFile demo_edgeDetectVideo.mp4 foi.txt edgeDetect 150"
