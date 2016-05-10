#pragma once
#include "CatchableObject.h"
class StableObject :
	public CatchableObject
{
public:
	StableObject(GoldenManEngine* pEngine, int gx, int gy, int xsize, int ysize);
	~StableObject();
	void Draw();
	void DoUpdate(int iCurrentTime);
	int g_xsize;
	int g_ysize;
	int gmode;
	int end_x;
	int end_y;
	int ifOnTheWay(int pig_x, int pig_y);
	void BombDetection();
	int GetGMode();
	int GetX();
	int GetY();
	bool IsExist();
private:
	GoldenManEngine* m_pMainEngine;
	int pig_id;
	int pig_width;
	int pig_height;
};

