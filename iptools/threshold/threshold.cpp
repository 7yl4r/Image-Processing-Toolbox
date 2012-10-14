#include "threshold.h"

/*-----------------------------------------------------------------------**/

//thesholding for grey images
void threshold::thresh(image &src, image &tgt, ROI roi, int thresh){
	cout<<"threshold = "<<thresh<<". \n";
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++){
		for (int j=0; j<src.getNumberOfColumns(); j++){
			if (roi.InROI(i,j)) {
				if(src.getPixel(i,j) > thresh){
					tgt.setPixel(i,j,255); 
				}else   tgt.setPixel(i,j,0);
			}else{
				tgt.setPixel(i,j,src.getPixel(i,j));
			}
		}
	}
}

//thresholding in 3D color space
void threshold::thresh(image &src, image &tgt, ROI roi, int thresh,int R,int G,int B){
	cout<<"where";
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++){
		for (int j=0; j<src.getNumberOfColumns(); j++){
			if (roi.InROI(i,j)) {
				float d = sqrt(pow(src.getPixel(i,j,RED)-R,2)+pow(src.getPixel(i,j,BLUE)-B,2)+pow(src.getPixel(i,j,GREEN)-G,2));		//get distance from pixel color to desired color
				if(d > thresh){	// if distance < than threshold
					tgt.setPixel(i,j,RED,255); 
					tgt.setPixel(i,j,BLUE,255);
					tgt.setPixel(i,j,GREEN,255);
				}else{
					tgt.setPixel(i,j,RED,0);
					tgt.setPixel(i,j,BLUE,0);
					tgt.setPixel(i,j,GREEN,0);
				}
			}else{
				tgt.setPixel(i,j,RED,src.getPixel(i,j,RED));
				tgt.setPixel(i,j,BLUE,src.getPixel(i,j,BLUE));
				tgt.setPixel(i,j,GREEN,src.getPixel(i,j,GREEN));
			}
		}
	}
	cout<<"is";
	for (int i=0; i<src.getNumberOfRows(); i++){
		for (int j=0; j<src.getNumberOfColumns(); j++){
			if (roi.InROI(i,j)) {
				float d=sqrt(pow(R-src.getPixel(i,j,0),2) 
					+pow(G-src.getPixel(i,j,1),2)
					+pow(B-src.getPixel(i,j,2),2)); 
				if(d > thresh){
					tgt.setPixel(i,j,255); 
				}else   tgt.setPixel(i,j,0);	
			}else{
				tgt.setPixel(i,j,src.getPixel(i,j));
			}
		}
	}
	cout<<"error";
}

// threshold using adaptive given window size
//int wS = atoi(av[1]);	//window size
//int w  = atoi(av[2]);	//amount above mean
void threshold::adapThresh(image &src, image &tgt, ROI roi, int wS,int w){
	if ((wS-1)%2 || wS < 1){	//if window size is not odd
		cout<<"ERR: window size "<<wS<<" must be positive, odd int.\n";
	}
	int wR = (wS-1)/2;	//radius of window
	cout<<"adaptive thresholding; window size="<<wS<<", threshold above mean="<<w<<".\n";
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	for (int i=0; i<src.getNumberOfRows(); i++){
		for (int j=0; j<src.getNumberOfColumns(); j++){
			if (roi.InROI(i,j)) {
				//get mean of window
				int mean = 0;
				for(int ii=0-wR; ii<=wR; ii++){
					for(int jj=0-wR; jj<=wR; jj++){
						mean += src.getPixel(i+ii,j+jj);
					}
				}
				mean = (int)round( (float)mean/((float)(wS*wS)) );
				//compare to window mean
				int thresh = mean + w;
				if(src.getPixel(i,j) > thresh){
					tgt.setPixel(i,j,255); 
				}else   tgt.setPixel(i,j,0);
			}else{	//not in ROI
				tgt.setPixel(i,j,src.getPixel(i,j));
			}
		}
	}
}
