#pragma once
#include "StableObject.h"
#include "JPGImage.h"
class GoldenManEngine;
class GoldObject :
	public StableObject
{
public:
	GoldObject(GoldenManEngine* pEngine, int gx, int gy);
	~GoldObject();
	void Draw();
	void DoUpdate(int iCurrentTime);
	int g_xsize;
	int g_ysize;
	int gmode;
	int end_x;
	int end_y;

private:
	GoldenManEngine* m_pMainEngine;
	ImageData gold;


};
