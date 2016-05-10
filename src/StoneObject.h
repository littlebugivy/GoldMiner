#pragma once
#include "StableObject.h"
#include "JPGImage.h"
class GoldenManEngine;
class StoneObject :
	public StableObject
{
public:
	StoneObject(GoldenManEngine* pEngine, int gx, int gy);
	~StoneObject();
	void Draw();
	void DoUpdate(int iCurrentTime);
	int g_xsize;
	int g_ysize;
	int gmode;
	int end_x;
	int end_y;

private:
	GoldenManEngine* m_pMainEngine;
	ImageData stone;


};
