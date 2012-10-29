#include "circleDetect.h"

// adjust array values to be in the range 0-255 by spreading equally into bins
//TODO:NOTE: will spread into as many bins as possible up to 255, if < 255 unique values in the array, then the number of unique values will be used. Thus, if a binary image array is passed, a binary spread will be returned
void circleDetect::normalizeArray(float **buffer,int nRows,int nCols){
//BEGIN normalizeArray
	//get boundary values to adjust range of values to 0-255
	int nPix = nRows*nCols;	//count of pixels
	int pixPerBin = round((float)nPix/256.0f);//don't worry about preciseness here, bins will still fill up acceptably
	float sorted[nPix];	//create sorted array of all values
	//copy values into sortArray
	for(int i = 0; i < nRows; i++){//for each pixel
		for(int j = 0; j<nCols; j++){
			sorted[i*nRows+j] = buffer[i][j];
		}
	}
	float* first(&sorted[0]);
	float* last(first + 4);
	sort(first,last, std::greater<float>());//sort the array
	int bins[256] = {0};	//create array of bin edges (top of each bin)
	bins[0] = sorted[pixPerBin];
	int pixDone = 0;	//pixel offset used to shift bin count start location
	for(int b = 1; b<256; b++){	//for each bin
		//binMax = sortedArry[ bin# * numpixPerBin]
		bins[b] = sorted[pixPerBin+pixDone];
		pixDone += pixPerBin;
//		cout<<pixDone<<'\n';
		/*
		while(bins[b]==bins[b-1]&&pixDone<nPix){//check for bin redundancy
			int pixLeft = nPix-pixDone;
			int binsLeft = 256-b;
			pixPerBin = round((float)pixLeft/(float)binsLeft)+1;//change pixPerBin for future bins (+1 to ensure that always at least 1 pixel)
			bins[b] = (int)round(sorted[pixDone+pixPerBin]); //get new bin max
			pixDone += pixPerBin;
//			cout<<pixLeft<<'\n';
		}
		*/





	}
	for(int i = 0; i < nRows; i++){//for each pixel 
		for(int j = 0; j<nCols; j++){
			//find pixel bin (compare to bin maxes until <=)
			for(int b = 0; b<256; b++){	//for each bin
				//set pixel value to corresponding bin
				if(buffer[i][j]<=bins[b]){
					buffer[i][j]=(float)b;
					break;
				}
			}
		}
	}
	//END normalizeArray
}



/*-----------------------------------------------------------------------**/
void circleDetect::hough(image &edgeImg, image &tgt, ROI roi){
	int desiredR = 25;
	// parameter space for circle: x,y,R
	int rMin = 20;	//radius (in pix?)
	int rMax = 30;
	int rDelta = 5;
	int rSize = rMax-rMin+1;
	int aMin = 0;	//possible x
	int aMax = edgeImg.getNumberOfColumns()/2;
	int aDelta = 20;
	int aSize = aMax-aMin+1;
	int bMin = 0;	//possible y
	int bMax = edgeImg.getNumberOfRows()/2;
	int bDelta = 20;
	int bSize = bMax-bMin+1;

	float ***acc = new float**[rSize];// = {0};	//accumulator array
	for(int r = 0; r < rSize; ++r) {
		acc[r] = new float*[aSize];
		for(int a = 0; a < aSize; ++a){
			acc[r][a] = new float[bSize];
		}
	}
//	int acc[rMax-rMin][aMax-aMin][bMax-bMin];	// set up accumulator array
//	memset(acc,0,sizeof(acc));	//initialize to 0

	for (int i=0; i<edgeImg.getNumberOfRows(); i++){	// for each edge point
		for (int j=0; j<edgeImg.getNumberOfColumns(); j++){
			if(j%100==0&&i%100==0) cout<<"("<<i<<","<<j<<")\n";
			int G = edgeImg.getPixel(i,j);// get gradient magnitude
			if (roi.InROI(i,j)&&G>0){//skip pixels not in roi & if G!>0
				// calculate the possible circle equations (cone?)
				for(int a=aMin; a<aMax; a+=aDelta){ // for all x
					for(int b=bMin; b<bMax; b+=bDelta){ // for all x// for all y
						for(int r=rMin; r<rMax; r+=rDelta){
//							if(j%50==0&&i%50==0) cout<<"["<<r<<"]["<<a<<"]["<<b<<"]\n";
							acc[r-rMin][a-aMin][b-bMin] += G; // increment accumulator array
						}
					}
				}
			//}else{	
				//ignore the pixel
			}
		}
	}

	int nRows = aSize/aDelta;
	int nCols = bSize/bDelta;
	normalizeArray(acc[desiredR-rMin],nRows,nCols);//adjust range of accumulator to 0-255 for display
	tgt.resize(nRows,nCols);
	for(int i = 0; i < nRows; i++){//for each pixel in roi
		for(int j = 0; j<nCols; j++){
			tgt.setPixel(i,j,acc[desiredR-rMin][i][j]);
		}
	}



	// display hough transform (2D projection?, at a set radius?)
	//what size? tgt.resize()


	//BEGIN cleanupAccumulator
	for(int r = 0; r < rSize; ++r) {
		for(int a=0; a<aSize; ++a)
			delete [] acc[r][a];	//deletes all 'b's
		delete [] acc[r];		//deletes all 'a's
	}
	delete [] acc;				//deletes all 'r's
	//END cleanupAccumulator
}
