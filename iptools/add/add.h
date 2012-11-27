#ifndef ADD_H
#define ADD_H

#include "../image/image.h"
#include "../roi/roi.h"

class add{
	public:	
		add();
		virtual ~add();
		static void addGrey(image &src, image &tgt, ROI roi, int value);
		static void addGreyImage(image &src, image &addition, image &tgt, ROI roi, int chan);
};

#endif

