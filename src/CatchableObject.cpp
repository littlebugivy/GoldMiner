#include "header.h"
#include "templates.h"
#include "CatchableObject.h"
#include "GoldenManEngine.h"
#include "HookObject.h"

// Objects which can be caught by the hook
CatchableObject::CatchableObject(GoldenManEngine* pEngine, int gx, int gy, int xsize, int ysize)
: DisplayableObject(pEngine),
m_pEngine(pEngine),
m_xsize(xsize),
m_ysize(ysize),
mode(0)
{
}


CatchableObject::~CatchableObject()
{
}

void CatchableObject::Draw(){
}

void CatchableObject::DoUpdate(int iCurrentTime){
}

// Detect the hook position
int CatchableObject::HookDetection(int s){
	DisplayableObject* pHook;
	pHook = m_pEngine->GetDisplayableObject(HOOKID);
	HookObject *hook = dynamic_cast<HookObject *>(pHook);
	int iXDiff = pHook->GetXCentre() - m_iCurrentScreenX - m_xsize / 2 ;
	int iYDiff = pHook->GetYCentre() - m_iCurrentScreenY - m_ysize / 2 ;
	// Pythagorus' theorum: when the hook get the object
	if (((iXDiff*iXDiff) + (iYDiff*iYDiff))
		< ((m_xsize / 2)*(m_ysize / 2)) && (HookObject::load) == 0)
	{
		HookObject::load = 1;
		hook->getGold();
		mode = 1;  // the hook get the object
	}
	
	switch (mode){
	case 1:				// get object	
		m_iCurrentScreenX -= hook->x_speed;
		m_iCurrentScreenY -= hook->y_speed;
		if (m_iCurrentScreenY < hook->root_y+20){  //The speed is between 0-20
			m_iCurrentScreenX = hook->root_x;
			m_iCurrentScreenY = hook->root_y;
			mode = 2;     // display the score;
			hook->load = 0; 
		}
		break;
	case 2: // show the score
		m_iCurrentScreenX += 10;
		if (m_iCurrentScreenY > 0){
			m_iCurrentScreenY -= 5;
		}
		if (m_iCurrentScreenX > 700){
			mode = 0; // the hook back to rotation
			switch (m_xsize){
			case 30:m_pEngine->score += 100; break;  // diamond
			case 40:m_pEngine->score += s;  break;  // pig			
			case 60:m_pEngine->score += 50; break; // gold
			case 100:m_pEngine->score += 10; break; // stone
			default: break;
			}
			SetVisible(false);
			mode = -1; // the detection end
		}
		break;
	default:break;
	}
	return mode;
}

