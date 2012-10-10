#ifndef SMOOTH_H
#define SMOOTH_H

#include "../image/image.h"
#include "../roi/roi.h"

#include <math.h>		

class smooth{
	public:	
		smooth();
		virtual ~smooth();
		static int smooth2d(image &src, image &tgt, ROI roi, int winS);
		static int smooth1d(image &src, image &tgt, ROI roi, int winS);
};

#endif

