#include "edgeDetect.h"

//return sobel x-direction grad estimate
int edgeDetect::sobelX(image &src, int chan, int x, int y){
	int S[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};	//horizontal sobel operator
	//apply sobel at x,y in src image
	int G = 0;	//value of estimated gradient

	// convolution of S & src kernel.
	for(int i = 0; i < 3; i++){	//for each pixel in the kernel
		for(int j = 0; j < 3; j++){
			G += S[i][j] * src.getPixel(x-i,y-j,chan);
		}
	}
//	if(x%10==0&&y%10==0) cout<<"X grad @("<<x<<','<<y<<"):"<<G<<"\n";
	return G;//return gradient value
}

//return sobel y-direction grad estimate
int edgeDetect::sobelY(image &src, int chan, int x, int y){
	int S[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};	//vertical sobel operator
	//apply sobel at x,y in src image
	int G = 0;	//value of estimated gradient
	for(int i = 0; i < 3; i++){	//for each pixel in the kernel
		for(int j = 0; j < 3; j++){
			G += S[i][j] * src.getPixel(x-i,y-j,chan);
		}
	}
	//if(x%10==0&&y%10==0) cout<<"Y grad @("<<x<<','<<y<<"):"<<G<<"\n";
	return G;//return gradient value
}

//returns grad magnitude from image src at point (x,y)
float edgeDetect::sobelMagnitude(image &src, int chan, int x, int y){
	float G = sqrt(pow((float)sobelX(src,chan,x,y),2.0f)+pow((float)sobelY(src,chan,x,y),2.0f));
//	if(x%10==0&&y%10==0) cout<<"grad magnitude@("<<x<<','<<y<<"):"<<G<<"\n";	//debug output
//	if(G>1000.0f) cout<<"grad magnitude@("<<x<<','<<y<<"):"<<G<<"\n";	//debug output
	return G;
}

// this following method can used in place of the thresholding approach to provide a quantized grad image (instead of binary)
//writes gradient value to image
void edgeDetect::sobel(image &src, image &tgt, ROI roi, int chan){
	tgt.copyImage(src);	//copy image to tgt (for areas not in ROI)
	float buffer[src.getNumberOfRows()][src.getNumberOfColumns()];// = {0};	//buffer to temporarily store grad values
	for(int i = 0; i < src.getNumberOfRows(); i++){//for each pixel in roi
		for(int j = 0; j<src.getNumberOfColumns(); j++){
			buffer[i][j] = sobelMagnitude(src,chan,i,j);//get gradient magnitudes
		}
	}
	//BEGIN writeAdjustedGradValues
	//get boundary values to adjust range of values to 0-255
	float upperOutlierLimit = 200.0f;
	float lowerOutlierLimit = 0.0f;
	int pixOnFloor = 0,pixOnCeil = 0;	//count of pixels outside set dynamic range
 	float max = lowerOutlierLimit;	//max pixel value
	float min = upperOutlierLimit;	//min pixel value
	for(int i = 0; i < src.getNumberOfRows(); i++){//for each pixel in roi
		for(int j = 0; j<src.getNumberOfColumns(); j++){
			// skip outliers
			if ( buffer[i][j] > upperOutlierLimit||buffer[i][j] < lowerOutlierLimit){
				if( buffer[i][j] > upperOutlierLimit){
					pixOnCeil++;
				}else   pixOnFloor++; 
			}else{ //check for max/mins
				if ( buffer[i][j] > max) max = buffer[i][j];
				if ( buffer[i][j] < min) min = buffer[i][j];
			}
		}
	}
	cout<<"max="<<max<<" onCeiling="<<pixOnCeil<<", min="<<min<<" onFloor="<<pixOnFloor<<'\n';
	for(int i = 0; i < src.getNumberOfRows(); i++){//for each pixel in roi
		for(int j = 0; j<src.getNumberOfColumns(); j++){
			if (roi.InROI(i,j)){
				// write (adjusted) grad value to tgt image
				tgt.setPixel(i,j,chan,round(buffer[i][j]*max/255.0f - min));
			}else{
				tgt.setPixel(i,j,chan,src.getPixel(i,j,chan));
			}
		}
	}
	//END writeAdjustedGradValues
}

void edgeDetect::sobel(image &src, image &tgt, ROI roi, int chan, int thresh){
	tgt.copyImage(src);
	float buffer[src.getNumberOfRows()][src.getNumberOfColumns()];// = {0};	//buffer to temporarily store grad values
	for(int i = 0; i < src.getNumberOfRows(); i++){//for each pixel in roi
		for(int j = 0; j<src.getNumberOfColumns(); j++){
			if (roi.InROI(i,j)){
				buffer[i][j] = sobelMagnitude(src,chan,i,j);//get gradient magnitudes
			}else{
				buffer[i][j] = 0;
			}
		}
	}
	//BEGIN thresholdGrad
	for(int i = 0; i < src.getNumberOfRows(); i++){//for each pixel in roi
		for(int j = 0; j<src.getNumberOfColumns(); j++){
			if (roi.InROI(i,j)){
				if(buffer[i][j] < thresh){
					tgt.setPixel(i,j,chan,0);
				}else{	//buffer[i][j] >= thresh
					tgt.setPixel(i,j,chan,255);
				}
			}else{//copy pixel
				tgt.setPixel(i,j,chan,src.getPixel(i,j,chan));
			}
		}
	}
	//END thresholdGrad
}

//display only horizonal edges or 45 degree +/- 10 degree edges etc
//angle is between 0 (horizontal) and PI (vertical)
void edgeDetect::directional(image &src, image &tgt, ROI roi, int chan, int thresh, float angle1, float angle2){
	tgt.copyImage(src);
	for(int i = 0; i < src.getNumberOfRows(); i++){//for each pixel in roi
		for(int j = 0; j<src.getNumberOfColumns(); j++){
			if (roi.InROI(i,j)){
				float Gx= sobelX(src,chan,i,j);	//x component
				float Gy= sobelY(src,chan,i,j);	//y component
				float G = sqrt(pow(Gx,2.0f)+pow(Gy,2.0f));// gradient magnitude
				float theta = atan(Gy/Gx);//gradient direction. theta is 0 for a vertical edge which is darker on the right side
				if(G < thresh){	//compare magnitude to threshold
					tgt.setPixel(i,j,chan,0);
				}else{	//G >= thresh
					float pi = 3.141592653589793238462643383279502884;
					float angle3 = fmod((angle1+pi),(2*pi));
					float angle4 = fmod((angle2+pi),(2*pi));
					//BEGIN check direction of detected edge
					if( (theta>angle1)&&(theta<angle2) ){	//if within angle) 
						tgt.setPixel(i,j,chan,255);
					}else if( (theta>angle3)&&(theta<angle4) ){ //or within angle of vector opposite direction
						tgt.setPixel(i,j,chan,255);
					}else{ //direction not right, floor it
						tgt.setPixel(i,j,chan,0);
					}
				}

			}else{//copy pixel
				tgt.setPixel(i,j,chan,src.getPixel(i,j,chan));
			}
		}
	}
}