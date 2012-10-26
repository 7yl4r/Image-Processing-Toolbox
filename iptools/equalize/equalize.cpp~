#include "equalize.h"

//TODO: separate mapping functions out from the mapping application to allow for less repetetive code.

// === draw a box around the image ==========================
void equalize::box(image &im){
	int v = 200;	//value for box edge
	for(int x = 0; x < im.getNumberOfRows(); x++){
		for(int y = 0; y < im.getNumberOfColumns(); y++){
			im.setPixel(0,y,v);
			im.setPixel(im.getNumberOfRows()-1,y,v);
		}
		im.setPixel(x,0,v);
		im.setPixel(x,im.getNumberOfColumns()-1,v);
	}
}

// === produce histogram image for given channel histogram ==================
void equalize::drawHist(int histH[256], image &tgt){	//histogram array,image width, maximum value in histH 
	int hMax = histH[0];	//find max histogram height value
	for(int x = 1; x<256; x++) hMax = max(histH[x],hMax);

	int edge = 5;	// width of edge around histogram (pix)
	int sX = 256 + 2*edge;	// # intensity values (x size)
	int sY = hMax + 2*edge;
	tgt.resize(sY,sX);

	box(tgt);	//draw box around image

	for(int v = 0; v<255; v++){	//for each value in histogram (x axis)
		for(int h = 1; h<histH[v]; h++){	//for each pixel under value height
			tgt.setPixel(sY-h,v+edge,255);	//fill in pixel
		}
	}
}

// === produce histogram image for given 3color histogram ==================
void equalize::drawColorHist(int histH[256][3], image &tgt){	//histogram array,image width, maximum value in histH 
	int hMax = histH[0][0];	//find max histogram height value
	for(int x = 0; x<256; x++) 
		for(int ch = 0; ch<3; ch++) hMax = max(histH[x][ch],hMax);

	int edge = 5;	// width of edge around histogram (pix)
	int sX = 256 + 2*edge;	// # intensity values (x size)
	int sY = hMax + 2*edge;
	tgt.resize(sY,sX);	

	box(tgt);	//draw box around image

	for(int v = 0; v<255; v++){	//for each value in histogram (x axis)
		for(int ch = 0;ch<3;ch++){	//for each (enum) channel
			for(int h = 1; h<histH[v][ch]; h++)	//for each pixel under value height
				tgt.setPixel(sY-h,v+edge,ch,255);	//fill in pixel
		}
	}
}

// === 1channel Equalize ============================================
//equalize specified channel
void equalize::channel(image &src, image &tgt, ROI roi, int chan){
	for(int r=0; r<roi.numBaseROI; r++){	//for each sub-ROI in list
		//cout<<"processing ROI #"<<r<<"; ";
		image rImage;	//image of ROI region
		rImage.resize(roi.list[r].sx,roi.list[r].sy);
		//cout<<"w="<<roi.list[r].sx<<", h="<<roi.list[r].sy<<", x="<<roi.list[r].x<<", y="<<roi.list[r].y<<"\n";
		int nPixels = rImage.getNumberOfRows()*rImage.getNumberOfColumns();	//number of pixels in the ROI


//		//BEGIN getHistogram
		int histH[256] = {0};	//histogram array
		addHist(src, roi.list[r], chan, histH); 
		int ri = 0;	//for each pixel in the ROI
		for(int i=roi.list[r].x; i<(roi.list[r].x+roi.list[r].sx); i++){
			int rj = 0;
			for(int j=roi.list[r].y; j<(roi.list[r].y+roi.list[r].sy);j++){
				if(!src.isInbounds(i,j)) {
					rj++;
					nPixels--;	//reduce pixel count
				}else{	//skip pixels outside src image
					int value = src.getPixel(i,j,chan);
					rImage.setPixel(ri,rj,value);	//copy pixels to roi image
//					histH[value]++;
					rj++;
				}
			}
			ri++;
		}
//		//END getHistogram


		image hImage;
		drawHist(histH, hImage);//draw histogram image
		//save images
		string fname = "ROIs/roi"+utility::intToString(r);
		//cout<<"saving "<<fname<<" & histogram\n";
		rImage.save((fname+"_chan"+utility::intToString(chan)+".pgm").c_str());
		hImage.save( (fname+"_chan"+utility::intToString(chan)+"hist"+".pgm").c_str() );
		// BEGIN CreateMappingFromHist
		float hist[256];	//normalized histogram
		float cdf[256];		//cumulative distrobution function of normalized histogram
		int map[256]; 	//mapping table for image pixels
		int max = 255, min = 0;	//color value limits
		for(int v = 0; v<256; v++){	//for each value in histogram (x axis)
			hist[v] = ((float)histH[v])/((float)nPixels);
			cdf[v] = 0;	//init 0
			for(int vv = 0; vv<=v; vv++) cdf[v] += hist[vv];	//add up to get cdf
			map[v] = round(cdf[v]*(max-min)+min);
		}
		//END CreateMappingFromHist


		//BEGIN mapPixels //MAP PIXELS IN SOURCE ROI
		fromMap(src,tgt,roi.list[r],map,chan);

		int endHist[256] = {0};//resulting histogram
		for(int i=roi.list[r].x; i<(roi.list[r].x+roi.list[r].sx); i++){	//for each pixel in the ROI
			for(int j=roi.list[r].y; j<(roi.list[r].y+roi.list[r].sy);j++){
				if(!src.isInbounds(i,j)) {
					continue;	//skip pixels outside src image
				}//implied else
				//set pixel using map
				int value = map[src.getPixel(i,j,chan)];
//				tgt.setPixel(i,j,chan,value);
				//CALCULATE RESULTING HISTOGRAM
				endHist[value]++;
			}
		}
		//END mapPixels



		image resultHImage;
		drawHist(endHist,resultHImage);
		resultHImage.save( (fname+"_chan"+utility::intToString(chan)+"ResultHist"+".pgm").c_str() );
	}
}

// === greyscale Equalize ============================================
//equalize only one channel (for greyscale images)
void equalize::grey(image &src, image &tgt, ROI roi){
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	system("mkdir ROIs");
	tgt.copyImage(src);	//COPY SRC IMAGE TO TGT
	channel(src,tgt,roi,RED);
}

// === RGB Equalize using 1 unified mapping ============================================
void equalize::colorAvg(image &src, image &tgt, ROI roi){
	system("mkdir ROIs");
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	tgt.copyImage(src);	//COPY SRC IMAGE TO TGT
	for(int r=0; r<roi.numBaseROI; r++){	//for each sub-ROI in list
		//cout<<"processing ROI #"<<r<<"; ";
		int histH[256] = {0};	//histogram array
		int histos[256][3] = {0}; //histogram for each color
		// FIND HISTOGRAM
		image rImage;
		rImage.resize(roi.list[r].sx,roi.list[r].sy);
		//cout<<"w="<<roi.list[r].sx<<", h="<<roi.list[r].sy<<", x="<<roi.list[r].x<<", y="<<roi.list[r].y<<"\n";
		int nPixels = rImage.getNumberOfRows()*rImage.getNumberOfColumns();	//number of pixels in the ROI
		//get histogram from pixels
		int ri = 0;	//for each pixel in the ROI
		for(int i=roi.list[r].x; i<(roi.list[r].x+roi.list[r].sx); i++){
			int rj = 0;
			for(int j=roi.list[r].y; j<(roi.list[r].y+roi.list[r].sy);j++){
				if(!src.isInbounds(i,j)) {
					rj++;
					nPixels--;	//reduce pixel count
					continue;	//skip pixels outside src image
				}//implied else
				int r = src.getPixel(i,j,RED);
				int g = src.getPixel(i,j,GREEN);
				int b = src.getPixel(i,j,BLUE);
				//copy pixels to roi image
				rImage.setPixel(ri,rj,RED,r);
				rImage.setPixel(ri,rj,GREEN,g);
				rImage.setPixel(ri,rj,BLUE,b);
				//set histogram values (using enum types)
				histos[r][RED]++;
				histos[g][GREEN]++;
				histos[b][BLUE]++;
				//set histogram value using average
				int avg = (int)round((float)(r+g+b)/3.0f);
				histH[avg]++;
				rj++;
			}
			ri++;
		}
		//create histogram image for display
		image hImage;
		drawHist(histH,hImage);
		//create color histogram image for display
		image cHist;
		drawColorHist(histos,cHist);
		//save images
		string fname = "ROIs/roi"+utility::intToString(r);
		//cout<<"saving "<<fname<<" & histogram\n";
		rImage.save((fname+".ppm").c_str());
		hImage.save((fname+"_avgHist.pgm").c_str());
		cHist.save((fname+"_colorHist.ppm").c_str());

		// BEGIN createMap
		float hist[256];	//normalized histogram
		float cdf[256];		//cumulative distrobution function of normalized histogram
		int map[256]; 	//mapping table for image pixels
		int max = 255, min = 0;	//color value limits
		for(int v = 0; v<256; v++){	//for each value in histogram (x axis)
			hist[v] = ((float)histH[v])/((float)nPixels);
			cdf[v] = 0;	//init 0
			for(int vv = 0; vv<=v; vv++) cdf[v] += hist[vv];	//add up to get cdf
			map[v] = round(cdf[v]*(max-min)+min);
		}
		// END createMap
		int endHist[256][3] = {0};	//resulting histogram
		int endAvgHist[256] = {0};
		//MAP PIXELS IN SOURCE ROI

		//for each pixel in the ROI
		for(int i=roi.list[r].x; i<(roi.list[r].x+roi.list[r].sx); i++){
			for(int j=roi.list[r].y; j<(roi.list[r].y+roi.list[r].sy);j++){
				if(!src.isInbounds(i,j)) {
					continue;	//skip pixels outside src image
				}//implied else
				//set pixel using map
				int r = map[src.getPixel(i,j,RED)];
				int g = map[src.getPixel(i,j,GREEN)];
				int b = map[src.getPixel(i,j,BLUE)];
				tgt.setPixel(i,j,RED,r);
				tgt.setPixel(i,j,GREEN,g);
				tgt.setPixel(i,j,BLUE,b);
				//CALCULATE RESULTING HISTOGRAMS
				endAvgHist[(int)round((float)(r+g+b)/3.0f)]++;
				endHist[r][RED]++;
				endHist[g][GREEN]++;
				endHist[b][BLUE]++;
			}
		}

		image resultH, resultColorH;
		drawHist(endAvgHist,resultH);
		resultH.save( (fname+"avgHistResult.pgm").c_str() );
		drawColorHist(endHist,resultColorH);
		resultColorH.save((fname+"colorHistResult.ppm").c_str() );


	}

}

// === Equalization using HSI conversion ============================================
void equalize::intensity(image &src, image &tgt, ROI roi){
	//convert to HSI
	image HSIsrc;
	colorSpace::RGBtoHSI(src,HSIsrc);
//	HSIsrc.save("HSIsrc.ppm");
	//equalize intensity channel
	image equalizedHSI;
	equalizedHSI.resize(HSIsrc.getNumberOfRows(), HSIsrc.getNumberOfColumns());
	equalizedHSI.copyImage(HSIsrc);	//COPY SRC IMAGE TO TGT
	channel(HSIsrc,equalizedHSI,roi,BLUE);	//equalize the intensity channel	
//	equalizedHSI.save("HSIequalized.ppm");
	//convert back to RGB
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	colorSpace::HSItoRGB(equalizedHSI,tgt);
}

// === RGB Separate Equalization ============================================
//equalize all colors separately
void equalize::colors(image &src, image &tgt, ROI roi){
	tgt.resize(src.getNumberOfRows(), src.getNumberOfColumns());
	system("mkdir ROIs");
	tgt.copyImage(src);	//COPY SRC IMAGE TO TGT
	channel(src,tgt,roi,RED);
	channel(src,tgt,roi,BLUE);
	channel(src,tgt,roi,GREEN);
}

// === equalize one image using given mapping ===
void equalize::fromMap(image &src, image &tgt, BaseROI roi, int map[], int chan){
	//equalize I channel using given mapping
	for(int i=roi.x; i<(roi.x+roi.sx); i++){	//for each pixel
		for(int j=roi.y; j<(roi.y+roi.sy);j++){
			if(!src.isInbounds(i,j)) {
				continue;	//skip pixels outside src image
			}//implied else
			//set pixel using map
			int value = map[src.getPixel(i,j,chan)];
			tgt.setPixel(i,j,chan,value);
		}
	}

}

// == return histogram from given image 
int *equalize::getHist(image &src, BaseROI roi, int chan){
	int *h = new int[256];
	std::fill_n(h,256,0);
	addHist(src,roi,chan,h);
	return h;
}

// === add image pixel values to given histogram
void equalize::addHist(image &src, BaseROI roi, int chan, int hist[256]){
	//BEGIN getImageHistogram
	for(int i=roi.x; i<(roi.x+roi.sx); i++){	//for each pixel in the roi
		for(int j=roi.y; j<(roi.y+roi.sy);j++){
			if(src.isInbounds(i,j)) {//skip pixels outside src image
				int value = src.getPixel(i,j,chan);
				hist[value]++;
			}else{
				//cout<<"roi pixel skipped: not in src image.\n";
			}
		}
	}
	//END getImageHistogram
}

// === return mapping created from all images in given directory & FOI ===
//void equalize::getMap(string srcDir, BaseROI foi, int nFrames, int map[]){
void equalize::getMap(string srcDir, BaseROI foi, int map[]){
	int max = 255, min = 0;		//color value limits
	int nPixels = 0;	//total number of pixels	
	//BEGIN getVideoHist
	int frame = 1;	//current frame being processed
	int H[256] = {0}; //cumulative histogram
	while(true){	//for each frame
		cout<<"frame "<<frame;
		//BEGIN imageExists
		string filename = srcDir+utility::intToString(frame)+".ppm";
		std::ifstream ifile(filename.c_str());
		if(!ifile) {
			cout<<"file "<<filename<<" not found; assumed end of frames\n";
			break;	//exit loop when out of files
		}
		ifile.close();
		//END imageExists

//	for(frame = 0; frame<nFrames; 
		if (foi.InROI(frame)) {	//if frame in roi
			image s;	//source image
			char *fname;
			strcpy(fname, filename.c_str());
			s.read(fname);	//load image
			image src;	//source image in HSI
			colorSpace::RGBtoHSI(s,src);
//			src.save("blaaaahhhh.ppm");
			addHist(src,foi,BLUE,H);
			
			//BEGIN getNPixels
			for(int i=foi.x; i<(foi.x+foi.sx); i++){	//for each pixel in the foi
				for(int j=foi.y; j<(foi.y+foi.sy);j++){
					if(src.isInbounds(i,j)) {//skip pixels outside src image
						nPixels++;	//add total # pixels
					}else{
//						cout<<"roi pixel skipped: not in src image.\n";
					}
				}
			}
			//END getNPixels
			cout<<" counted";
		} else  cout<<" skipped";
		frame++;
		cout<<".\n";
	}
	//END videoHist
	//BEGIN calcMap
	float hist[max+1], cdf[max+1];
	for(int v = 0; v<256; v++){	//for each value in histogram (x axis)
		hist[v] = ((float)H[v])/((float)nPixels);
		cdf[v] = 0;	//init 0
		for(int vv = 0; vv<=v; vv++) cdf[v] += hist[vv];	//add up to get cdf
		map[v] = round(cdf[v]*((float)max-(float)min)+(float)min);
	}
	//END calcMap
	image histI;
	drawHist(H,histI);
	histI.save("ehhhh.pgm");
}
