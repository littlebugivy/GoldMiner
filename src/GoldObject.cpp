#include "header.h"
#include "templates.h"
#include "GoldObject.h"
#include "RunningPig.h"
#include "GoldenManEngine.h"


GoldObject::GoldObject(GoldenManEngine* pEngine, int gx, int gy) :
StableObject(pEngine,gx,gy,60,54),
g_xsize(60),
g_ysize(54),
m_pMainEngine(pEngine),
gmode(0) // stay still
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

	gold.LoadImage("./psyml5_src/gold.png");
	SetVisible(true);
}


GoldObject::~GoldObject()
{
}



void GoldObject::Draw(){
	// Do not draw if it should not be visible
	if (!IsVisible())
		return;
	
	switch (gmode)
	{
	case 0: // stay still
	case 1: // caught, move with hook
		gold.RenderImageWithMask(m_pMainEngine->GetSDLSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, gold.GetWidth(), gold.GetHeight());
		break;
	case 2: // display score
		GetEngine()->DrawScreenString(m_iCurrentScreenX, m_iCurrentScreenY, "$50", 0x0000000); 
		break;
	default:
		break;
	}
	// This will store the position at which the object was drawn
	// so that the background can be drawn over the top.
	// This will then remove the object from the screen.
	StoreLastScreenPositionForUndraw();
}

void  GoldObject::DoUpdate(int iCurrentTime){
	StableObject::DoUpdate(iCurrentTime);
	gmode = GetGMode();
}
