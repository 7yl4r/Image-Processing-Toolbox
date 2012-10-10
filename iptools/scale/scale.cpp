#include "scale.h"

/*-----------------------------------------------------------------------**/

//thesholding for grey images
int scale::scale2or4(image &src, image &tgt, ROI roi, int s){
	cout<<"scaling to "<<s<<'%'<<" of original size...\n";
	if(!(s==25||s==50||s==200||s==400)){
		cout<<"ERR: can only scale 25, 50, 200, or 400 percent!\n";
		return 1;
	} //implied else
	int nRows = ceil(((float)s/100)*src.getNumberOfRows());
	int nCols = ceil(((float)s/100)*src.getNumberOfColumns());
	cout<<"new image is "<<nRows<<"x"<<nCols<<".\n";
	tgt.resize(nRows,nCols);
	if(s<100){	//averaging reduction
		int wS = 0;	//window size
		if(s==25){
			wS = 4;
		}else if (s==50){
			wS = 2;
		}
		for (int ti=0; ti<tgt.getNumberOfRows(); ti++){
			for (int tj=0; tj<tgt.getNumberOfColumns(); tj++){
				int i = ti*wS;
				int j = tj*wS;
				//NOTE: ROI is ignored here (doesn't really make sense)
				int avg = 0;
				//get avg of pixel windows
				for(int ii = 0; ii<wS; ii++){
					for(int jj = 0; jj<wS; jj++)
						avg += src.getPixel(i+ii,j+jj);
				}
				avg = (int)round( ((float)avg)/(float)(wS*wS) );
				tgt.setPixel(ti,tj,avg);	//write new pixel
			}
		}
	}else if(s>100){	//replication
		int wS = 0;	//window size
		if(s==400){
			wS = 4;
		}else if (s==200){
			wS = 2;
		}
		for (int i=0; i<src.getNumberOfRows(); i++){
			for (int j=0; j<src.getNumberOfColumns(); j++){
				//NOTE: ROI is ignored here (doesn't really make sense)
				int pix = src.getPixel(i,j);
				int ti = i*wS;
				int tj = j*wS;
				//write multiple tgt pixels for each src pixel
				for(int ii = 0; ii<wS; ii++){
					for(int jj = 0; jj<wS; jj++)
						tgt.setPixel(ti+ii,tj+jj,pix);
				}
			}
		}
	}
}
