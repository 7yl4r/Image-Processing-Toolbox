#ifndef THRESHOLD_H
#define THRESHOLD_H

#include "../image/image.h"
#include "../roi/roi.h"

#include <math.h>

class threshold{
	public:	
		threshold();
		virtual ~threshold();
		static void thresh(image &src, image &tgt, ROI roi, int thresh);	//greyscale
		static void adapThresh(image &src, image &tgt, ROI roi, int wS,int w);	//adaptive grayscale
		static void thresh(image &src, image &tgt, ROI roi, int thresh,int R,int G,int B);	//color
};

#endif

