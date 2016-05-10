#include "header.h"
#include "templates.h"
#include "StoneObject.h"
#include "RunningPig.h"
#include "GoldenManEngine.h"

StoneObject::StoneObject(GoldenManEngine* pEngine, int gx, int gy) :
StableObject(pEngine, gx, gy, 100, 75)
, m_pMainEngine(pEngine)
, gmode(0) // stay still
, g_xsize(100)
, g_ysize(75)
{
	// Current and previous coordinates for the object - set them the same initially
	m_iCurrentScreenX = m_iPreviousScreenX = gx;
	m_iCurrentScreenY = m_iPreviousScreenY = gy;
	// The object coordinate will be the top left of the object
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	// Record the ball size as both height and width
	m_iDrawWidth = g_xsize;
	m_iDrawHeight = g_ysize;
	// And make it visible
	SetVisible(true);

	stone.LoadImage("./psyml5_src/stone.png");
}


StoneObject::~StoneObject()
{
}


void StoneObject::Draw(){
	// Do not draw if it should not be visible
	if (!IsVisible())
		return;

	switch (gmode)
	{
	case 0: // stay still
	case 1: // caught, move with hook
		stone.RenderImageWithMask(m_pMainEngine->GetSDLSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, stone.GetWidth(), stone.GetHeight());
		break;
	case 2: // display the score
		GetEngine()->DrawScreenString(m_iCurrentScreenX, m_iCurrentScreenY, "$10", 0x0000000);
		break;
	default:
		break;
	}
	StoreLastScreenPositionForUndraw();
}

void StoneObject::DoUpdate(int iCurrentTime){
	StableObject::DoUpdate(iCurrentTime);
	gmode = GetGMode();
}