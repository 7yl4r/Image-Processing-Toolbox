#ifndef ARRAYDISPLAY_H
#define ARRAYDISPLAY_H

#include "../image/image.h"
#include "../roi/roi.h"

class arrayDisplay{
	public:	
		arrayDisplay();
		virtual ~arrayDisplay();
		//draw array in tgt image using given roi taken from array & put into tgt image
		static void floorAndCeiling(int a[][], image &tgt, ROI roi, int floor, int ceiling); 

		static void floorAndCeiling(int a[][], image &tgt, int floor, int ceiling);	//assume roi is whole array

		//static void idealHistogram(int a[][], image &tgt);
};

#endif
