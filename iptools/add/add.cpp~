#include "add.h"

/*-----------------------------------------------------------------------**/
void add::addGrey(image &src, image &tgt, ROI roi, int value){
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++){
		for (int j=0; j<src.getNumberOfColumns(); j++){
			if (roi.InROI(i,j)){
				tgt.setPixel(i,j,src.getPixel(i,j) + value); 
				//check for values outside range
		             	if (tgt.getPixel(i,j) > 255)
					tgt.setPixel(i,j,255);
				else if (tgt.getPixel(i,j) < 0)
					tgt.setPixel(i,j,0);	
			}else{	
				tgt.setPixel(i,j,src.getPixel(i,j));
			}
		}
	}
}

