#ifndef EDGEDETECT_H
#define EDGEDETECT_H

#include "../image/image.h"
#include "../roi/roi.h"

#include <sstream>
#include <math.h>
#include <vector>

class edgeDetect
{
	public:	
		edgeDetect();
		virtual ~edgeDetect();
		static int sobelX(image &src, int chan, int x, int y);
		static int sobelY(image &src, int chan, int x, int y);
		static float sobelMagnitude(image &src, int chan, int x, int y);
		static void sobel(image &src, image&tgt, ROI roi, int chan);
		static void sobel(image &src, image &tgt, ROI roi, int chan, int thresh);
		static void directional(image &src, image &tgt, ROI roi, int chan, int thresh, float angle1, float angle2);
};

#endif

