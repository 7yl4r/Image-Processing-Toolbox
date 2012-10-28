#!/bin/bash
echo "This demo will use default images to demonstrate the edge detection capabilities of this image processing tool. Press enter to continue."
read c

echo " === GreyScale Sobel Operator Edge Detection 'edgeDetect' ==="
echo `./bin/iptool images_for_demo/crossSec.pgm demo_edgeDetectGrey.pgm roi.txt edgeDetect 50`

echo " === Gradient Magnitude Image Display 'edgeDetect' ==="
echo `./bin/iptool images_for_demo/baboon.pgm demo_gradMagnitudeDisplay.pgm roi.txt edgeDetect`




echo "image processing demo complete."
echo "The following demo of video processing capability may take some time. Press enter to begin."
read c

#echo "=== Histogram Equalization of Video 'equalizeIntensity' ==="
#echo `./bin/iptool videos_for_demo/demo_short.mpeg demo_equalizeIntensity.mp4 foi.txt equalizeIntensity`