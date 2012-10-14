#include "smooth.h"

/*-----------------------------------------------------------------------**/
//smooth using 2d window. less efficient than 1d smooth, same result. Included for demonstration purposes only.
int smooth::smooth2d(image &src, image &tgt, ROI roi, int winS){
	if ((winS-1)%2 || winS < 1){	//if window size is not odd
		cout<<"ERR: window size "<<winS<<" must be positive, odd int.\n";
		return 1;
	}
	int winR = (winS-1)/2;	//radius of window
	cout<<"smoothing over "<<winS<<"pixel square window...\n";
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++){
		for (int j=0; j<src.getNumberOfColumns(); j++){
			if (roi.InROI(i,j)) {
				int value = 0;
				for(int ii=0-winR; ii<=winR; ii++){	//get 2d average in window
					for(int jj=0-winR; jj<=winR; jj++){
						value += src.getPixel(i+ii,j+jj);
					}
				}
				value = (int)round( (float)value/((float)(winS*winS)) );
				tgt.setPixel(i,j,value);
			}else{
				tgt.setPixel(i,j,src.getPixel(i,j));
			}
		}
	}
	return 0;
}

//smooth in horizontal & then vertical direction, producing identical results as 2d smoothing, but with more efficiency.
int smooth::smooth1d(image &src, image &tgt, ROI roi, int winS){
	if ((winS-1)%2 || winS < 1){	//if window size is not odd
		cout<<"ERR: window size "<<winS<<" must be positive, odd int.\n";
		return 1;
	}
	int winR = (winS-1)/2;	//radius of window
	cout<<"smoothing over "<<winS<<"pixel square window in 1d, then combining with convolution...\n";
	image buffer;
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	buffer.resize(tgt.getNumberOfRows(), tgt.getNumberOfColumns());
	cout<<"smoothing in horizontal\n";
	for (int i=0; i<src.getNumberOfRows(); i++){
		for (int j=0; j<src.getNumberOfColumns(); j++){
			if (roi.InROI(i,j)) {
				//do 1D horizontal avg; save to buffer image
				int value = 0;
				for(int ii = 0-winR; ii<=winR; ii++){
					value += src.getPixel(i+ii,j);
				}
				value = (int)round( (float)value/((float)(winS)) );
				buffer.setPixel(i,j,value);
			}else{	//not in ROI
				buffer.setPixel(i,j,src.getPixel(i,j));
			}
		}
	}
	cout<<"smoothing in vertical\n";
	//convolve result of 1d horizontal with 1D vertical
	for (int i=0; i<src.getNumberOfRows(); i++){
		for (int j=0; j<src.getNumberOfColumns(); j++){
			if (roi.InROI(i,j)) {
				//do 1D vertical avg
				int value = 0;
				for(int jj = 0-winR; jj<=winR; jj++){
					value += buffer.getPixel(i,j+jj);
				}
				value = (int)round( (float)value/((float)(winS)) );
				tgt.setPixel(i,j,value);
			}else{	//not in ROI
				tgt.setPixel(i,j,src.getPixel(i,j));
			}
		}
	}
	return 0;
}
