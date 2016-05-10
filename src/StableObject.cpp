#include "header.h"
#include "templates.h"
#include "HookObject.h"
#include "RunningPig.h"
#include "GoldenManEngine.h"
#include "StableObject.h"
#include "RunningPig.h"

/* Objects do not move, have consant value
Can be catched by the hook, be bombed by the bomb */
StableObject::StableObject(GoldenManEngine* pEngine, int gx, int gy, int xsize, int ysize) :
CatchableObject(pEngine, gx, gy, xsize, ysize),
m_pMainEngine(pEngine),
g_xsize(xsize),
g_ysize(ysize),
gmode(0) // stay still
{
}


StableObject::~StableObject()
{
}



void StableObject::Draw(){
}



void StableObject::DoUpdate(int iCurrentTime){
	// Do not do update if it should not be visible
	if (!IsVisible())
		return;
	BombDetection();
	gmode = HookDetection(0);
	RedrawObjects();
}


void StableObject::BombDetection(){
	// collision detection with hook
	DisplayableObject* pHook;
	pHook = m_pMainEngine->GetDisplayableObject(HOOKID);

	// If you need to cast to the sub-class type, you must use dynamic_cast, see lecture 19
	// We are just using base class parts

	HookObject *hook = dynamic_cast<HookObject *>(pHook);   // use dynamic cast to get the sub class function
	int drop_angle = hook->getAngle();

	// detect for exploration
	if (hook->explode == 1){
		int t_XDiff = hook->mloc_x - m_iCurrentScreenX - g_xsize / 2;
		int t_YDiff = hook->mloc_y - m_iCurrentScreenY - g_ysize / 2;
		if (t_XDiff * t_XDiff + t_YDiff* t_YDiff < (g_xsize / 2 + 120)*(g_ysize / 2 + 120)){  //set to be sensitive
			SetVisible(false);
		}
	}
}


int StableObject::GetGMode(){
	return gmode;
}

int StableObject::GetX(){
	return m_iCurrentScreenX;
}

int StableObject::GetY(){
	return m_iCurrentScreenY;
}

bool StableObject::IsExist(){
	bool result = IsVisible();
	return result;
}