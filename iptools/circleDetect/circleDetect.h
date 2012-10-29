#ifndef CIRCLEDETECT_H
#define CIRCLEDETECT_H

#include "../image/image.h"
#include "../roi/roi.h"

#include <math.h>	//for round()
#include <algorithm>	//for sort()

class circleDetect{
	public:	
		circleDetect();
		virtual ~circleDetect();
		static void hough(image &edgeImg, image &tgt, ROI roi);
	private:
		static void normalizeArray(float **buffer,int nRows,int nCols);
};

#endif

