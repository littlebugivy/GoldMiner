#pragma once
#include "DisplayableObject.h"
class Psyml5Object1 :
	public DisplayableObject
{
public:
	Psyml5Object1(BaseEngine* pEngine);
	~Psyml5Object1();
	void DoUpdate(int iCurrentTime);
	void Draw();
protected:
	// available screen size for the objects
	int ava_x;
	int ava_y;
};

