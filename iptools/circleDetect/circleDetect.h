#ifndef CIRCLEDETECT_H
#define CIRCLEDETECT_H

#include "../image/image.h"
#include "../roi/roi.h"

#include <math.h>	//for round()

class circleDetect{
	public:	
		circleDetect();
		virtual ~circleDetect();
		static void hough(image &edgeImg, image &tgt, ROI roi);
};

#endif

