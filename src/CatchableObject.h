#pragma once
#include "DisplayableObject.h"
#include "JPGImage.h"
class GoldenManEngine;
class CatchableObject :
	public DisplayableObject
{
public:
	CatchableObject(GoldenManEngine* pEngine, int gx, int gy, int xsize, int ysize);
	~CatchableObject();

	void Draw();
	void DoUpdate(int iCurrentTime);
	GoldenManEngine* m_pEngine;
	ImageData boom;

    int HookDetection(int s);
private:
		 int m_xsize;
		 int m_ysize;
		 int mode;
		 
		
};

