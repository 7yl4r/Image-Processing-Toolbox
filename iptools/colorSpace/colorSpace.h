#ifndef COLORSPACE_H
#define COLORSPACE_H

#include "../image/image.h"
#include "../roi/roi.h"

class colorSpace{
	public:	
		colorSpace();
		virtual ~colorSpace();
		static void RGBtoHSI(image &src, image &tgt);
		static void HSItoRGB(image &src, image &tgt);
};

#endif

