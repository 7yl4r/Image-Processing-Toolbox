#ifndef SCALE_H
#define SCALE_H

#include "../image/image.h"
#include "../roi/roi.h"

#include <math.h>

class scale{
	public:	
		scale();
		virtual ~scale();
		static int scale2or4(image &src, image &tgt, ROI roi, int s);
};

#endif

