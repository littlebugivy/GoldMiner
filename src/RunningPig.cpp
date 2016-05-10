#include "header.h"
#include "templates.h"
#include "GoldenManEngine.h"
#include "RunningPig.h"
#include "StableObject.h"

/*Automated moving objects which can be blocked by the stable objects and
can be bombed up by the user bomb, the values of them are depend on the luck*/
RunningPig::RunningPig(GoldenManEngine* pEngine, int px, int py)
	:CatchableObject(pEngine,px,py,40,70) // consider string size
	, direct(0) // run right
	, m_pEngine(pEngine)
	, pig_height(40)
	, pig_width(35)
	, pmode(0)
	, pix(0)
	, lpix(0)
	, p_score(2)
	, isBombed(false)
{
	// Current and previous coordinates for the object - set them the same initially
	m_iCurrentScreenX = m_iPreviousScreenX = lpix = px;
	m_iCurrentScreenY = m_iPreviousScreenY = py;
	// The object coordinate will be the top left of the object
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	// Record the ball size as both height and width
	m_iDrawWidth = pig_height + 20;
	m_iDrawHeight = pig_width + 30; // for string 
	// And make it visible

	ls.LoadImage("./psyml5_src/ls.png");
	rs.LoadImage("./psyml5_src/rs.png");
	lw.LoadImage("./psyml5_src/lw.png");
	rw.LoadImage("./psyml5_src/rw.png");
	lc.LoadImage("./psyml5_src/lc.png");
	rc.LoadImage("./psyml5_src/rc.png");
	boom.LoadImage("./psyml5_src/boom.png");

	SetVisible(true);
}

// class for diamond stamp pig, which does not need to consider string size
RunningPig::RunningPig(GoldenManEngine* pEngine, int px, int py, int dp)
	:CatchableObject(pEngine, px, py, 40, 35)
	, direct(0) // run right
	, m_pEngine(pEngine)
	, pig_height(40)
	, pig_width(35)
	, pmode(0)
	, pix(0)
	, lpix(0)
	, p_score(2)
	, isBombed(false)
{
}


RunningPig::~RunningPig()
{
}


void RunningPig::Draw()
{	
	// Do not draw if it should not be visible
	if (!IsVisible())
		return;

	char buf[10];
	switch (pmode)
	{
	case 0: // not caught 
		// changable values of the pig from -99 to 99
		p_score = rand() % 198-99;
		sprintf(buf, "%d", p_score);
		// display the changable value of the pig
		GetEngine()->DrawScreenString(m_iCurrentScreenX, m_iCurrentScreenY, buf, 0xffffff);

		pix = abs(m_iCurrentScreenX - lpix);
		switch (direct)
		{
		case 0: // go right	, have diffirent look when it moves around	
			if (pix <= 20){
				rw.RenderImageWithMask(m_pEngine->GetSDLSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY + 30, rw.GetWidth(), rw.GetHeight());
			}
			else{
				rs.RenderImageWithMask(m_pEngine->GetSDLSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY + 30, rs.GetWidth(), rs.GetHeight());
			}
			break;
		case 1: // go left
			if (pix <= 20){
				lw.RenderImageWithMask(m_pEngine->GetSDLSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY + 30, lw.GetWidth(), lw.GetHeight());
			}
			else{
				ls.RenderImageWithMask(m_pEngine->GetSDLSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY + 30, ls.GetWidth(), ls.GetHeight());
			}
			break;
		default:
			break;
		}
		if (pix > 40){
			pix = 0;
			lpix = m_iCurrentScreenX;
		}
		break;
	case 1: // be caught
		if (!isBombed){   // if is not bombed by user "up"
			sprintf(buf, "%d", p_score);
			/* the value of the pig is settled and can be viewed when it 
			is moving with hook*/
			m_pEngine->DrawScreenString(m_iCurrentScreenX, m_iCurrentScreenY, buf, 0xffffff);
			switch (direct)
			{
			case 0: rc.RenderImageWithMask(m_pEngine->GetSDLSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY + 30, rc.GetWidth(), rc.GetHeight()); break;
			case 1: lc.RenderImageWithMask(m_pEngine->GetSDLSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY + 30, lc.GetWidth(), lc.GetHeight()); break;
			default:
				break;
			}
		}
		else{   // bombed by user "up"
			if (m_pEngine->GetTime() < l_time +1000){  // keep the boom for some time
				boom.RenderImageWithMask(m_pEngine->GetSDLSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, boom.GetWidth(), boom.GetHeight()); 
			}
			else{
				SetVisible(false);
			}
		}
		break;
	case 2: // get to the end
		sprintf(buf, "$%d", p_score);
		m_pEngine->DrawScreenString(m_iCurrentScreenX, m_iCurrentScreenY, buf, 0x000000); break;
		break;
	default:
		break;
	}
	
	StoreLastScreenPositionForUndraw();
}

void RunningPig::DoUpdate(int iCurrentTime){

	// Do not do update if it should not be visible
	if (!IsVisible())
		return;

	/* Detect if bombed by the user or if the user want to bomb it
	User can choose to bomb the pig if the value of the pig is negative*/
	if (isBombed || (pmode == 1 && m_pEngine->IsKeyPressed(SDLK_UP))){
		if (!isBombed){
			l_time = m_pEngine->GetTime();
		}
		isBombed = true;
		return;
	}

	pmode = HookDetection(p_score);
	StoneDetection();

	if (pmode == 0){ // if the pig is not caught
		ExplodeDetection();
		switch (direct)
		{
		case 0: // go right
			m_iCurrentScreenX += 1;
			break;
		case 1: // go left
			m_iCurrentScreenX -= 1;
			break;
		default:
			break;
		}

		if (m_iCurrentScreenX > 700){
			direct = 1;
		}
		if (m_iCurrentScreenX < 40){
			direct = 0;
		}
		RedrawObjects();
	}

}


/* Detect stone, which will block pig's movement*/
void RunningPig::StoneDetection(){	
	// collision detection with 
	int ob_x;
	int ob_y;
	int g_ysize;
	int g_xsize;
	int iObjectId; 
	int num = m_pEngine->gs_num;
	
	DisplayableObject* pstable;
	StableObject *sta_ob;
	for (iObjectId = 0; iObjectId < num; iObjectId++)
	{			
		pstable = m_pEngine->GetDisplayableObject(iObjectId);
		sta_ob = dynamic_cast<StableObject *>(pstable);
		if (sta_ob->IsExist()){
		//	printf("Y %d\n", iObjectId);
		
			ob_x = sta_ob->GetX();
			ob_y = sta_ob->GetY();
			g_ysize = sta_ob->g_ysize;
			g_xsize = sta_ob->g_xsize;
		
			if (ob_y < (m_iCurrentScreenY +35+ pig_height) && (ob_y + g_ysize) > (m_iCurrentScreenY+35)){
				if (direct == 0 && (m_iCurrentScreenX + pig_width >= ob_x) && (m_iCurrentScreenX < ob_x)){
					ChangeDirection(1); //  change the direction of pig
				}
				else if (direct == 1 && (m_iCurrentScreenX <= ob_x + g_xsize) && (m_iCurrentScreenX > ob_x)){
					ChangeDirection(1);
				}
			}
		}
	}
	pstable = NULL;
}

/* When the red bomb bombed, scared to run the other way opposite the 
direction of the red bomb*/
void RunningPig::ExplodeDetection(){
	// collision detection with hook
	DisplayableObject* pHook;
	pHook = m_pEngine->GetDisplayableObject(HOOKID);

	// If you need to cast to the sub-class type, you must use dynamic_cast, see lecture 19
	// We are just using base class parts

	HookObject *hook = dynamic_cast<HookObject *>(pHook);   // use dynamic cast to get the sub class function

	// detect for exploration
	if (hook->explode == 1){
		if (hook->explode_x < m_iCurrentScreenX){
			direct = 0;
			int speed = (rand() % 5) + 2;
			m_iCurrentScreenX += speed;
		}
		else{
			direct = 1;
			int speed = (rand() % 5) + 2;
			m_iCurrentScreenX -= speed;
		}
	}
}

void RunningPig::ChangeDirection(int time){ // change the direction of the pig
	if (direct == 1){
		direct = 0;
	}
	else{
		direct = 1;
	}
}

int RunningPig::GetDirection(){
	return direct;
}

int RunningPig::GetPigX(){
	return m_iCurrentScreenX;
}


int RunningPig::GetPigY(){
	return m_iCurrentScreenY;
}
