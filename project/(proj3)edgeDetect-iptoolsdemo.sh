#!/bin/bash
echo "This demo will use default images to demonstrate the edge detection capabilities of this image processing tool. Press enter to continue."
read c

echo " *** Thresholded Gradient *** "
echo "=====GreyScale Thresholded Sobel Operator Edge Detection 'edgeDetect'====="
echo `./bin/iptool images_for_demo/crossSec.pgm demo_edgeDetect_GreySilicon.pgm roi.txt edgeDetect 100`
echo `./bin/iptool images_for_demo/bubbleChamber.pgm demo_edgeDetect_BubbleChamber.pgm roi.txt edgeDetect 200`
echo `./bin/iptool images_for_demo/moonCraters2.pgm demo_edgeDetect_MoonCraters2.pgm roi.txt edgeDetect 300`
echo `./bin/iptool images_for_demo/moonCraters.pgm demo_edgeDetect_MoonCraters.pgm ALL edgeDetect 400`

echo "=====Thresholded Gradient Image Display on color images 'edgeDetect'====="
echo `./bin/iptool images_for_demo/micro3.ppm demo_edgeDetectColor.ppm roi.txt edgeDetect 300`

echo "=====Directional Edge Detection 'detectEdgeDirection'====="
echo `./bin/iptool images_for_demo/sponge.pgm demo_directional0to45deg.pgm roi.txt detectEdgeDirection 150 0 45`
echo `./bin/iptool images_for_demo/sponge.pgm demo_directional45to90deg.pgm roi.txt detectEdgeDirection 150 45 90`

echo ""
echo " *** Gradient Magnitude Display *** "
echo "=====Gradient Magnitude Image Display 'edgeDetect'====="
echo `./bin/iptool images_for_demo/baboon.pgm demo_gradMagnitudeDisplay.pgm roi.txt edgeDetect`

echo `./bin/iptool images_for_demo/bubbleChamber.pgm demo_edgeMag_BubbleChamber.pgm roi.txt edgeDetect`
echo `./bin/iptool images_for_demo/moonCraters2.pgm demo_edgeMag_MoonCraters2.pgm roi.txt edgeDetect`

echo ""
echo " *** Circle Detection Using Hough Transform *** "
echo "=====GreyScale Circle Detection 'circleDetect'====="
echo `./bin/iptool images_for_demo/bubbleChamber.pgm demo_circleDetect.pgm ALL circleDetect 200`

echo ""
echo "image processing demo complete."
echo "The following demo of video processing capability may take some time. Press enter to begin."
read c

echo "=====Edge Detection on video 'edgeDetect'====="
echo `./bin/iptool videos_for_demo/newYork.m1v demo_edgeDetectVideo.m1v foi.txt edgeDetect 150`
