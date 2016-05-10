#include "header.h"
#include "templates.h"
#include "Psyml5Object2.h"
#include "Psyml5Engine.h"


Psyml5Object2::Psyml5Object2(BaseEngine* pEngine)
	: DisplayableObject(pEngine),
	m_dX(5),
	m_dY(5),
	m_dSX(0),
	m_dSY(0),
	color(0x000000),
	color_count(0),
	ball_beat(0)
{
	Psyml5Engine e1;
	// Current and previous coordinates for the object - set them the same initially
	m_iCurrentScreenX = m_iPreviousScreenX = 0;
	m_iCurrentScreenY = m_iPreviousScreenY = 0;
	// The object coordinate will be the top left of the object
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	// Record the ball size as both height and width
	m_iDrawWidth = 50;
	m_iDrawHeight = 50;
	// And make it visible
	SetVisible(true);
	
}


Psyml5Object2::~Psyml5Object2()
{
}


void Psyml5Object2::SetMovement(int iStartTime, int iEndTime, int iCurrentTime,
	int iStartX, int iStartY, int iEndX, int iEndY)
{
	m_oMovement.Setup(iStartX, iStartY, iEndX, iEndY, iStartTime, iEndTime);
	m_oMovement.Calculate(iCurrentTime);
	m_iCurrentScreenX = m_oMovement.GetX();
	m_iCurrentScreenY = m_oMovement.GetY();

}


void Psyml5Object2::SetPosition(double dX, double dY)
{
	m_dX = dX;
	m_dY = dY;
}

void Psyml5Object2::SetSpeed(double dSX, double dSY)
{
	m_dSX = dSX;
	m_dSY = dSY;
}


void Psyml5Object2::DoUpdate(int iCurrentTime)
{	
	m_dX += m_dSX;
	m_dY += m_dSY;

	if ((m_dX) < 0)
	{
		m_dX =0;
		if (m_dSX < 0)
			m_dSX = -m_dSX;
			//printf("1  %d", m_dSY);
	}

	if ((m_dX + m_iDrawWidth) >(GetEngine()->GetScreenWidth() - 1))
	{
		m_dX = GetEngine()->GetScreenWidth() - 1 - m_iDrawWidth;
		if (m_dSX > 0)
			m_dSX = -m_dSX;
			
	}

	if ((m_dY) < 0)
	{
		m_dY =0;
		if (m_dSY < 0)
			m_dSY = -m_dSY;
			//printf("2  %d", m_dSY);
	}

	if ((m_dY + m_iDrawHeight) >(GetEngine()->GetScreenHeight() - 1 ))
	{
		m_dY = GetEngine()->GetScreenHeight() - 1 - m_iDrawHeight;
		if (m_dSY > 0)
			m_dSY = -m_dSY;
			//printf("3  %d", m_dSY);
	}
	printf("%f,%f ", m_dX,m_dY);
	if (m_dY == 400 && m_dX >= 100 && m_dX <= 650){	
		ball_beat ++ ;
		m_dSY = -m_dSY;
	}

	if (m_dY == 499 && m_dX >= 100 && m_dX <= 650){
		ball_beat ++;
		m_dSY = -m_dSY;
	}

    if (m_dX == 100 && m_dY >= 400 && m_dY <= 500 ){
		ball_beat ++;
		m_dSX = -m_dSX;
	}
	if (m_dX == 650 && m_dY >= 400 && m_dY <= 500){
		ball_beat ++;
		m_dSX = -m_dSX;
	}
	


	// Work out current position
	m_iCurrentScreenX = (int)(m_dX+0.5);
	m_iCurrentScreenY = (int)(m_dY+0.5);
	RedrawObjects();
	//RedrawBackground();

}

void Psyml5Object2::Draw(){
	color = SetColor();
	color_count +=1;
	GetEngine()->DrawScreenOval(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		color); //BLUE BALL

	StoreLastScreenPositionForUndraw();
}


int Psyml5Object2::SetColor(){
	switch (color_count% 2)
	{
	case 0: return 0xee4035; break;
	//case 1: return 0xf37736; break;
	//case 2: return 0xfdf498; break;
	//case 3: return 0x7bc043; break;
	case 1: return 0x000000; break;
	default:return 0x7bc043;
		break;
	}
}


