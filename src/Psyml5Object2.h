#pragma once
#include "DisplayableObject.h"
#include "TileManager.h"
#include "MovementPosition.h"
#include "Psyml5Engine.h"

class Psyml5Object2 :
	public DisplayableObject
{
public:
	Psyml5Object2(BaseEngine* pEngine);
	~Psyml5Object2(); // Have inner sub class,  so need to be virtual
	void DoUpdate(int iCurrentTime);
	void Draw();
	void SetMovement(int iStartTime, int iEndTime, int iCurrentTime,
		int iStartX, int iStartY, int iEndX, int iEndY);
	void SetPosition(double dX, double dY);
	void SetSpeed(double dSX, double dSY);
	int SetColor();
	int ball_beat;

protected:	
	MovementPosition m_oMovement;
	double m_dX;
	double m_dY;
	double m_dSX;
	double m_dSY;
	int color;
	int color_count;

	//TileManager m_pTileManager;
};

