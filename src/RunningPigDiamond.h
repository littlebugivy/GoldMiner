#pragma once
#include "RunningPig.h"
#include "GoldenManEngine.h"
class RunningPigDiamond :
	public RunningPig
{
public:
	RunningPigDiamond(GoldenManEngine* pEngine, int px, int py);
	~RunningPigDiamond();
	void Draw();
	void DoUpdate(int iCurrentTime);
	void DiamondSearchAndStamp();
	GoldenManEngine* m_pEngine;
	int updown;
	int diamond_loc[2];

private: 
	int pig_x;
	int pig_y;
	int direct;
	int dia_num;
	int dia_help_c;
	int soffset;
	int mini;
};

