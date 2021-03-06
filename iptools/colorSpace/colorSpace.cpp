#include "colorSpace.h"

#include <math.h>	//for pow & round & pi

/*-----------------------------------------------------------------------**/
void colorSpace::RGBtoHSI(image &src, image &tgt){
	//cout<<"RGB->HSI\n";
	tgt.resize(src.getNumberOfRows(),src.getNumberOfColumns());
	float pi = 3.14159265358979f;
	for (int i=0; i<src.getNumberOfRows(); i++){	//for each pixel
		for (int j=0; j<src.getNumberOfColumns(); j++){
			//normalize RGB values
			float sum = (float)(src.getPixel(i,j,RED) + src.getPixel(i,j,GREEN) + src.getPixel(i,j,BLUE));
			if(sum!=0){	//make sure not to div0
				float r = (float)src.getPixel(i,j,RED)/sum;
				float g = (float)src.getPixel(i,j,GREEN)/sum;
				float b = (float)src.getPixel(i,j,BLUE)/sum;
				float h;
				if(b<=g){	//0<h<2pi
					h = acos( ( .5f*((r-g)+(r-b)) ) / pow((r-g)*(r-g)+(r-b)*(g-b),.5f) );
				}else{	//b > g
					h = 2.0f*pi - acos( .5f*((r-g)+(r-b)) / pow((r-g)*(r-g)+(r-b)*(g-b),.5f) );
				}
				float s = 1.0f-3.0f*min(min(r,g),b);	//0<s<1
				float in = sum/(3.0f*255.0f);		//0<in<1
				//convert h,s,i to appropriate ranges for storage in image
				int hue = round(h*255.0f/(2.0f*pi));	//255/2 instead of 180 (Intead of 360)
				int sat = round(s*255.0f);	//255 instead of 100
				int inten = round(in*255.0f);
				tgt.setPixel(i,j,H,hue);
				tgt.setPixel(i,j,S,sat);
				tgt.setPixel(i,j,I,inten);
			}else{
				tgt.setPixel(i,j,H,0);
				tgt.setPixel(i,j,S,0);
				tgt.setPixel(i,j,I,0);
			}
		}
	}
}

void colorSpace::HSItoRGB(image &src, image &tgt){
	//cout<<"HSI->RGB\n";
	tgt.resize(src.getNumberOfRows(),src.getNumberOfColumns());
	float pi = 3.14159265358979f;
	for (int i=0; i<src.getNumberOfRows(); i++){	//for each pixel
		for (int j=0; j<src.getNumberOfColumns(); j++){
			//re-normalize h,s,i
			float h = ((float)src.getPixel(i,j,H))*pi*2.0f/255.0f;//255/2 instead of 180
			float s = ((float)src.getPixel(i,j,S))/255.0f;//255 instead of 100
			float in= ((float)src.getPixel(i,j,I))/255.0f;
			/*
			//compute x y z
			float x = in*(1.0f-s);
			float y = in*( 1.0f + (s*cos(h) / cos(pi/3.0f-h)) );
			float z = 3.0f*in-(x+y);
			float r,g,b;	//set rgb
			if(h<(2.0f*pi/3.0f)){
				b = x;
				r = y;
				g = z;
			}else if(h<(4.0f*pi/3.0f)){//&&2pi/3<=h
				r = x; 
				g = y;
				b = z;
			}else{	//less than 2pi && 4pi/3<=h
				g = x;
				b = y;
				r = z;
			}*/
			float x = in*(1.0f-s);
			float y,z,r,g,b;
			if(h<(2.0f*pi/3.0f)){
				y = in*( 1.0f + (s*cos(h) / cos(pi/3.0f-h)) );
				z = 3.0f*in-(x+y);
				b = x;
				r = y;
				g = z;
			}else if(h<(4.0f*pi/3.0f)){//&&2pi/3<=h
				h -= 2*pi/3;
				y = in*( 1.0f + (s*cos(h) / cos(pi/3.0f-h)) );
				z = 3.0f*in-(x+y);
				r = x; 
				g = y;
				b = z;
			}else{  //less than 2pi && 4pi/3<=h
				h -= 4*pi/3;
				y = in*( 1.0f + (s*cos(h) / cos(pi/3.0f-h)) );
				z = 3.0f*in-(x+y);
				g = x;
				b = y;
				r = z;
			}
			//convert normalized rgb to 0-255 range
			int rr = (int)round(r*255.0f);
			int gg = (int)round(g*255.0f);
			int bb = (int)round(b*255.0f);
			tgt.setPixel(i,j,RED,rr);
			tgt.setPixel(i,j,GREEN,gg);
			tgt.setPixel(i,j,BLUE,bb);
		}
	}
}	

