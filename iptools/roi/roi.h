// ROI.h: interface for the ROI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROI_H__8438A090_F2DD_446B_99A9_8C03BAF40432__INCLUDED_)
#define AFX_ROI_H__8438A090_F2DD_446B_99A9_8C03BAF40432__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class BaseROI{	//ROI public values for each ROI
	public:
		// === vars ===
		int x;	//left corner of ROI
		int y;	//uppper corner of ROI
		int sx;	//horiz size of ROI
		int sy;	//vert size of ROI
		int f;	//starting frame of ROI (for video)
		int sf;	//length of frame sequence (in frames) ((for video)) 
		// === methods ===
		bool InROI(int px,int py);
		bool InROI(int px, int py, int pf);
		bool InROI(int pf);
};

class ROI{	//Full list of ROIs
	public:
		// === constructor&destructor ===
		ROI();
		virtual ~ROI();
		// === vars ===
		int numBaseROI;		//number of ROIs
		BaseROI* list;	//list of BaseROI objects
		// === methods ===
		void ReleaseROIList();
		bool InROI(int pf);
		bool InROI(int px,int py);
		bool InROI(int px,int py,int pf);
		void CreateFOIList(char *fileName);
		void CreateList(char* filename);
		void CreateList(int X, int Y, int SX, int SY);
		void CreateList(int X, int Y, int SX, int SY, int F, int SF);
};

#endif // !defined(AFX_ROI_H__8438A090_F2DD_446B_99A9_8C03BAF40432__INCLUDED_)
