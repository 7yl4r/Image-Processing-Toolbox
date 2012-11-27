#!/bin/bash
echo "This demo will use default images to demonstrate the edge detection capabilities of this image processing tool. Some of these operations take quite a bit of time, and this script does not show outputs during wait time, so you may find it more enjoyable to try out the commands given here in a terminal. After each section, the script will wait to continue so that you may have a look at the output images in the project directory."

echo " *** Thresholded Gradient *** "
echo "=====GreyScale Thresholded Sobel Operator Edge Detection 'edgeDetect'====="
echo "press enter to continue"
read c
gnome-terminal -e "./bin/iptool images_for_demo/crossSec.pgm demo_edgeDetect_Silicon.pgm roi.txt edgeDetect 100" 
gnome-terminal -e "./bin/iptool images_for_demo/bubbleChamber.pgm demo_edgeDetect_BubbleChamber.pgm roi.txt edgeDetect 200"
gnome-terminal -e "./bin/iptool images_for_demo/moonCraters2.pgm demo_edgeDetect_MoonCraters2.pgm roi.txt edgeDetect 300"
gnome-terminal -e "./bin/iptool images_for_demo/moonCraters.pgm demo_edgeDetect_MoonCraters.pgm ALL edgeDetect 400"

echo "=====Thresholded Gradient Image Display on color images 'edgeDetect'====="
echo "press enter to continue"
read c
gnome-terminal -e "./bin/iptool images_for_demo/micro3.ppm demo_edgeDetectColor.ppm roi.txt edgeDetect 300"

echo "=====Directional Edge Detection 'detectEdgeDirection'====="
echo "press enter to continue"
read c
gnome-terminal -e "./bin/iptool images_for_demo/sponge.pgm demo_directional0to45deg.pgm roi.txt detectEdgeDirection 150 0 45"
gnome-terminal -e "./bin/iptool images_for_demo/sponge.pgm demo_directional45to90deg.pgm roi.txt detectEdgeDirection 150 45 90"

echo ""
echo " *** Gradient Magnitude Display *** "
echo "=====Gradient Magnitude Image Display 'edgeDetect'====="
echo "press enter to continue"
read c
gnome-terminal -e "./bin/iptool images_for_demo/baboon.pgm demo_gradMagnitudeDisplay.pgm roi.txt edgeDetect"

gnome-terminal -e "./bin/iptool images_for_demo/bubbleChamber.pgm demo_edgeMag_BubbleChamber.pgm roi.txt edgeDetect"
gnome-terminal -e "./bin/iptool images_for_demo/moonCraters2.pgm demo_edgeMag_MoonCraters2.pgm roi.txt edgeDetect"

echo ""
echo " *** Circle Detection Using Hough Transform *** "
echo "=====GreyScale Circle Detection 'circleDetect'====="
echo "press enter to continue"
read c
gnome-terminal -e "./bin/iptool images_for_demo/daphniaPulex.ppm demo_circleDetect_Daphnia.ppm ALL circleDetect 170 10"
echo "That will take some time, and the next circleDetection will overwrite some of the outputs that may be interesting to you. Wait for it to finish, take a look at the generated images in the project directory, and then..."
echo "press enter to continue"
read c
gnome-terminal -e "./bin/iptool images_for_demo/bubbleChamber.pgm demo_circleDetect_BubbleChamber.pgm ALL circleDetect 300 7"

echo ""
echo "image processing demo complete."
echo "The following demo of video processing capability may take some time. Press enter to begin."
read c

echo "=====Edge Detection on video 'edgeDetect'====="
echo "press enter to continue"
read c
gnome-terminal -e "./bin/iptool videos_for_demo/newYork.m1v demo_edgeDetectVideo.m1v foi.txt edgeDetect 150"

echo ""
echo "=====Circle Detection on video 'circleDetect'====="
echo "I wouldn't reccomend running this... it takes a VERY long time and thus is not well tested; if you dare..."
echo "press enter to continue"
read c
echo gnome-terminal -e "./bin/iptool videos_for_demo/demo_short.mpeg demo_circleDetect.mpeg ALL circleDetect 300 40"
