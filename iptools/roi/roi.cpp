// ROI.cpp: implementation of the ROI class.
//
//////////////////////////////////////////////////////////////////////

#include "roi.h"
#include "stdio.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


ROI::ROI(){
	this->list=0;	//list of ROIs
	this->numBaseROI=0;	//number of ROIs
}

ROI::~ROI(){	//destructor
}

//////////////////////////////////////////////////////////////////////
// BaseROI Public Methods
//////////////////////////////////////////////////////////////////////

//returns true if pixel at px,py is in the base ROI
bool BaseROI::InROI(int px, int py){
	int x,y,sx,sy;
	x =this->x;
	y =this->y;
	sx=this->sx;
	sy=this->sy;
	if (px>x && py>y && px<(x+sx) && py<(y+sy)){
		return true;
	}else return false;
}
//returns true if frame f is in this ROIs (for video)
bool BaseROI::InROI(int pf){
	int f,sf;
	f =this->f;
	sf=this->sf;
	if (pf>f && pf<f+sf){
		return true;
	}//else
	return false;
}

//returns true if pixel at px,py, frame f is in this ROIs (for video)
bool BaseROI::InROI(int px, int py, int pf){
	int x,y,sx,sy,f,sf;
	x =this->x;
	sx=this->sx;
	y =this->y;
	sy=this->sy;
	f =this->f;
	sf=this->sf;
	if (px>x && py>y && pf>f && px<x+sx && py<y+sy && pf<f+sf){
		return true;
	}//else
	return false;
}

//////////////////////////////////////////////////////////////////////
// ROI (full list) Public Methods
//////////////////////////////////////////////////////////////////////

//returns true if pixel at px,py is in any ROIs
bool ROI::InROI(int px, int py){
	int x,y,sx,sy;
	for (int i=0;i<this->numBaseROI;i++){
		x =list[i].x;
		y =list[i].y;
		sx=list[i].sx;
		sy=list[i].sy;
		if (px>x && py>y && px<x+sx && py<y+sy){
			return true;
		}
	}
	return false;
}

//returns true if frame f is in any ROIs (for video)
bool ROI::InROI(int pf){
	int f,sf;
	for (int i=0;i<this->numBaseROI;i++){
		f =list[i].f;
		sf=list[i].sf;
		if (pf>f && pf<f+sf){
			return true;
		}
	}
	return false;
}

//returns true if pixel at px,py, frame f is in any ROIs (for video)
bool ROI::InROI(int px, int py, int pf){
	int x,y,sx,sy,f,sf;
	for (int i=0;i<this->numBaseROI;i++){
		x =list[i].x;
		sx=list[i].sx;
		y =list[i].y;
		sy=list[i].sy;
		f =list[i].f;
		sf=list[i].sf;
		if (px>x && py>y && pf>f && px<x+sx && py<y+sy && pf<f+sf){
			return true;
		}
	}
	return false;
}

void ROI::ReleaseROIList(){
}

void ROI::CreateFOIList(char *fileName){	//construct from file
	FILE* file=fopen(fileName,"rt+");	//open script
	fscanf(file,"%d",&this->numBaseROI);	//read # of ROIs
	this->list=new BaseROI[numBaseROI];	//create list of appropriate length
	for (int i=0;i<numBaseROI;i++){		//populate list with ROIs
		fscanf(file,"%d %d %d %d %d %d\n",&list[i].x,&list[i].y,&list[i].sx,&list[i].sy,&list[i].f,&list[i].sf);
	}
}

void ROI::CreateList(char *fileName){	//construct from file
	FILE* file=fopen(fileName,"rt+");	//open script
	fscanf(file,"%d",&this->numBaseROI);	//read # of ROIs
	this->list=new BaseROI[numBaseROI];	//create list of appropriate length
	for (int i=0;i<numBaseROI;i++){		//populate list with ROIs
		fscanf(file,"%d %d %d %d\n",&list[i].x,&list[i].y,&list[i].sx,&list[i].sy);
	}
}

void ROI::CreateList(int X, int Y, int SX, int SY){	//construct with 1 ROI
	this->numBaseROI=1;
	this->list=new BaseROI[numBaseROI];
	list[0].x = X;
	list[0].y = Y;
	list[0].sx = SX;
	list[0].sy = SY;
}

void ROI::CreateList(int X, int Y, int SX, int SY, int F, int SF){	//construct with 1 FOI (video)
	this->numBaseROI=1;
	this->list=new BaseROI[numBaseROI];
	list[0].x  = X;
	list[0].y  = Y;
	list[0].sx = SX;
	list[0].sy = SY;
	list[0].f  = F;
	list[0].sf = SF;
}
