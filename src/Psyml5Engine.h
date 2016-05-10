#pragma once
#include "BaseEngine.h"
#include "Psyml5TileManager.h"
class Psyml5Object2;
class Psyml5Engine :
	public BaseEngine
{
protected:
	int nose_X;
	int nose_Y;
	int nose_start_X;
	int nose_start_Y;
	
	Psyml5TileManager m_oTiles;
	Psyml5Object2* ball;
	void DrawStringsOnTop();
	void UnDrawStrings();
	void DrawStringsUnderneath();
public:
	/**
	Constructor
	The : here refers to an initialisation list
	*/	
	Psyml5Engine();
    ~Psyml5Engine();
	void SetupBackgroundBuffer();
	int InitialiseObjects();
	void MouseDown(int iButton, int iX, int iY);
	void MouseMove(int iX, int iY);
	int ball_beat;

};

