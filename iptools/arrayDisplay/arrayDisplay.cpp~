#include "arrayDisplay.h"

/*-----------------------------------------------------------------------**/
void arrayDisplay::floorAndCeiling(int a[][], int n1, int n2, image &tgt, int floor, int ceiling){
	//BEGIN writeAdjustedGradValues
	int pixOnFloor = 0,pixOnCeil = 0;	//count of pixels outside set dynamic range
	//BEGIN getArrayRange
 	float max = floor;	//max pixel value
	float min = ceiling;	//min pixel value
	for(int i = 0; i < n1; i++){//for each pixel in roi
		for(int j = 0; j<n2; j++){
			if(roi.inROI(i,j){
				// skip outliers
				if ( a[i][j]>ceiling||a[i][j]<floor){
					if( a[i][j] > ceiling){
						pixOnCeil++;
					}else   pixOnFloor++; 
				}else{ //check for max/mins
					if ( a[i][j] > max) max = a[i][j];
					if ( a[i][j] < min) min = a[i][j];
				}
			}
		}
	}
	//END getArrrayRange
	cout<<"max="<<max<<" onCeiling="<<pixOnCeil<<", min="<<min<<" onFloor="<<pixOnFloor<<'\n';
	for(int i = 0; i < n1; i++){//for each pixel in roi
		for(int j = 0; j<n2; j++){
			if(roi.inROI(i,j){
				// write (adjusted) grad value to tgt image
				tgt.setPixel(i,j,round(a[i][j]*max/255.0f - min));
			}
		}
	}
	//END writeAdjustedGradValues
}

