#include "header.h"
#include "templates.h"
#include "DiamondObject.h"
#include "RunningPig.h"
#include "GoldenManEngine.h"


DiamondObject::DiamondObject(GoldenManEngine* pEngine, int gx, int gy) :
StableObject(pEngine, gx, gy, 30, 25),
g_xsize(30),
g_ysize(25),
d_x(gx),
d_y(gy),
m_pMainEngine(pEngine),
gmode(0) // stay still
, arrived(0)
, pig_leave(false)
, pigt(20)
{
	// Current and previous coordinates for the object - set them the same initially
	m_iCurrentScreenX = m_iPreviousScreenX = gx;
	m_iCurrentScreenY = m_iPreviousScreenY = gy;
	// The object coordinate will be the top left of the object
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	// Record the ball size as both height and width
	m_iDrawWidth = g_xsize+30;
	m_iDrawHeight = g_ysize+15; // consider string
	// And make it visible
	SetVisible(true);

	diamond.LoadImage("./psyml5_src/diamond.png");
}


DiamondObject::~DiamondObject()
{
}



void DiamondObject::Draw(){
	// Do not draw if it should not be visible
	if (!IsVisible())
		return;

	switch (gmode)
	{
	case 0:  // stay still
	case 1:	 // caught, move with hook
		diamond.RenderImageWithMask(m_pMainEngine->GetSDLSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, diamond.GetWidth(), diamond.GetHeight());
		break;
	case 2:  // get to the end
		GetEngine()->DrawScreenString(m_iCurrentScreenX, m_iCurrentScreenY, "$100", 0x0000000);
		break;
	default:
		break;
	}
	// This will store the position at which the object was drawn
	// so that the background can be drawn over the top.
	// This will then remove the object from the screen.
	StoreLastScreenPositionForUndraw();
}

void DiamondObject::DoUpdate(int iCurrentTime){
	if (!IsVisible())
		return;
	// the pig be here for 20s then the diamond disappear
	if (pigt <= 0){
			SetVisible(false);
			return;
	}
	StableObject::DoUpdate(iCurrentTime);
	gmode = GetGMode();
}


int DiamondObject::GetDimondX(){
	return d_x;
}

int DiamondObject::GetDimondY(){
	return d_y;
}

// Diamond Pig come
void DiamondObject::PigArrive(){
	printf("Pig is Here!\n");
	arrived = 1;
}

// Diamond Pig go
void DiamondObject::PigLeave(){
	printf("Pig Gone!\n");
	arrived = -1;
}

// Detect pig stamp
void DiamondObject::PigUpDown(){
	printf("%d\n", pigt);
	if (pigt>0)
	pigt--;

	if (pigt == 0){
		printf("One diamond is gone :<\n");
	}
}
