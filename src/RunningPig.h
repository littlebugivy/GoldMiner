#pragma once
#include "CatchableObject.h"
#include "JPGImage.h"
#include "HookObject.h"
class GoldenManEngine;
class RunningPig :
	public CatchableObject
{
public:
	RunningPig(GoldenManEngine* pEngine, int px, int py);
	RunningPig(GoldenManEngine* pEngine, int px, int py, int dp);  // for diamond pig

	~RunningPig();
	void Draw();
	void DoUpdate(int iCurrentTime);
	int direct;

	void ChangeDirection(int time);
	int GetPigX();
	int GetPigY();
	int GetDirection();
	GoldenManEngine* m_pEngine;
	void StoneDetection();
	void ExplodeDetection();
	bool isBombed;
	int pmode;
	ImageData lw;
	ImageData ls;
	ImageData rw;
	ImageData rs;
	ImageData lc;
	ImageData rc;
	ImageData boom;
	int l_time;
	int lpix;
	int pix;
	int pig_height;
	int pig_width;
	int p_score;

private:
	

	
};

