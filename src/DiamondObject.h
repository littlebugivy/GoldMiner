#pragma once
#include "StableObject.h"
#include "JPGImage.h"
class GoldenManEngine;
class DiamondObject :
	public StableObject
{
public:
	DiamondObject(GoldenManEngine* pEngine, int gx, int gy);
	~DiamondObject();
	void Draw();
	void DoUpdate(int iCurrentTime);

	int GetDimondX();
	int GetDimondY();
	void PigArrive();
	void PigLeave();
	int pigt;
	void PigUpDown();
	int arrived;
private:
	GoldenManEngine* m_pMainEngine;
	ImageData diamond;
	int g_xsize;
	int g_ysize;
	int gmode;
	int end_x;
	int end_y;
	int d_x;
	int d_y;
	
	bool pig_leave;

};
