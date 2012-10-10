#!/bin/bash
echo "This demo will use default images to demonstrate the advanced capabilities of this image processing tool. Press enter to continue."

echo " === GreyScale Histogram Equalization 'equalizeGrey' ==="
echo `./bin/iptool images_for_demo/grocery.pgm demo_equalizeGrey.pgm roi.txt equalizeGrey`

echo " === Color Histogram Equalization of color channels separately 'equalizeColors' ==="
echo `./bin/iptool images_for_demo/flowers.ppm demo_equalizeColors.ppm roi.txt equalizeColors`

echo " === Color Histogram Equalization using avg of color channels 'equalizeAvg' ==="
echo `./bin/iptool images_for_demo/flowers.ppm demo_equalizeAvg.ppm roi.txt equalizeAvg`

echo " === Color Histogram Equalization using HSI color space 'equalizeIntensity' ==="
echo `./bin/iptool images_for_demo/flowers.ppm demo_equalizeIntensity.ppm roi.txt equalizeIntensity`

echo " === Color Histogram Equalization of one color channel 'equalizeChannel' ==="
echo `./bin/iptool images_for_demo/flowers.ppm demo_equalizeChannelRED.ppm roi.txt equalizeChannel 0`
echo `./bin/iptool images_for_demo/flowers.ppm demo_equalizeChannelGREEN.ppm roi.txt equalizeChannel 1`
echo `./bin/iptool images_for_demo/flowers.ppm demo_equalizeChannelBLUE.ppm roi.txt equalizeChannel 2`
