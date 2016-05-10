#include "header.h"
#include "templates.h"
#include "Psyml5Object1.h"


Psyml5Object1::Psyml5Object1(BaseEngine* pEngine)
	: DisplayableObject(pEngine),
	ava_x(0),
	ava_y(0)

{
	// Current and previous coordinates for the object - set them the same initially
	m_iCurrentScreenX = m_iPreviousScreenX = rand()% 800;
	m_iCurrentScreenY = m_iPreviousScreenY = rand() % 600;
	// The object coordinate will be the top left of the object
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	// Record the ball size as both height and width
	m_iDrawWidth = 30;
	m_iDrawHeight = 30;

	// get the available screen for objects
	ava_x = GetEngine()->GetScreenWidth() - m_iDrawWidth;
	ava_y = GetEngine()->GetScreenHeight() - m_iDrawHeight;
	// And make it visible
	SetVisible(true);
}


Psyml5Object1::~Psyml5Object1()
{
}


void Psyml5Object1::DoUpdate(int iCurrentTime)
{
	// Change position if player presses a key
	if (GetEngine()->IsKeyPressed(SDLK_UP) || GetEngine()->IsKeyPressed(SDLK_w))
		m_iCurrentScreenY -= 5;
	if (GetEngine()->IsKeyPressed(SDLK_DOWN) || GetEngine()->IsKeyPressed(SDLK_s))
		m_iCurrentScreenY += 5;
	if (GetEngine()->IsKeyPressed(SDLK_LEFT) || GetEngine()->IsKeyPressed(SDLK_a))
		m_iCurrentScreenX -= 5;
	if (GetEngine()->IsKeyPressed(SDLK_RIGHT) || GetEngine()->IsKeyPressed(SDLK_d))
		m_iCurrentScreenX += 5;
	
	if (GetEngine()->IsKeyPressed(SDLK_q)){
		m_iCurrentScreenX -= 5;
		m_iCurrentScreenY -= 5;
	}
	if (GetEngine()->IsKeyPressed(SDLK_z)){
		m_iCurrentScreenX -= 5;
		m_iCurrentScreenY += 5;
	}
	if (GetEngine()->IsKeyPressed(SDLK_e)){
		m_iCurrentScreenX += 5;
		m_iCurrentScreenY -= 5;
	}
	if (GetEngine()->IsKeyPressed(SDLK_c)){
		m_iCurrentScreenX += 5;
		m_iCurrentScreenY += 5;
	}	

	if (m_iCurrentScreenX < 0)
		m_iCurrentScreenX = rand() % (ava_x);
	if (m_iCurrentScreenX >= ava_x)
		m_iCurrentScreenX = rand() % (ava_x);
	if (m_iCurrentScreenY >= ava_y)
		m_iCurrentScreenY = rand() % (ava_y);
	if (m_iCurrentScreenY < 0)
		m_iCurrentScreenY = rand() % (ava_y);


	if (GetEngine()->IsKeyPressed(SDLK_p))
		if (m_iCurrentScreenX >0 && m_iCurrentScreenX <ava_x && m_iCurrentScreenY >0 && m_iCurrentScreenY <ava_y)
		Draw();
	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();
}


void Psyml5Object1::Draw()
{

	GetEngine()->DrawScreenRectangle(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth/2 - 1,
		m_iCurrentScreenY + m_iDrawHeight/2 - 1,
		0x398564); // DARK GREEN VEGETABLE1

	GetEngine()->DrawScreenRectangle(
		m_iCurrentScreenX + m_iDrawWidth/2, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight/2 - 1,
		0x419873); // DARK GREEN VEGETABLE2

	GetEngine()->DrawScreenRectangle(
		m_iCurrentScreenX, m_iCurrentScreenY + m_iDrawWidth / 2,
		m_iCurrentScreenX + m_iDrawWidth/2 - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		0x49ab81); // GREEN VEGETABLE3

	GetEngine()->DrawScreenRectangle(
		m_iCurrentScreenX + m_iDrawWidth / 2, m_iCurrentScreenY + m_iDrawHeight / 2,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		0x52bf90); // DARK GREEN VEGETABLE4

	GetEngine()->DrawBackgroundString(50, 50, "Button", 0xffffff, NULL);
	// This will store the position at which the object was drawn
	// so that the background can be drawn over the top.
	// This will then remove the object from the screen.
	StoreLastScreenPositionForUndraw();
}
