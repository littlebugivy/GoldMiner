#include "header.h"
#include "templates.h"
#include "RunningPigDiamond.h"
#include "DiamondObject.h"

/*A special running pig which can move around, detect and stamp diamonds
to make it disappear. The value of this pig is 2, it will not be blocked or
bombed when it is searching for diamond, but is catchable and also become
a normal running pig when the diamonds are all gone*/
RunningPigDiamond::RunningPigDiamond(GoldenManEngine* pEngine, int px, int py)
	:RunningPig(pEngine, px, py, 0)
	, m_pEngine(pEngine)
	, pig_x(px)
	, pig_y(py)
	, direct(1)  // start go left
	, dia_help_c(0)
	, mini(1000000)
	, updown(0)
{
	diamond_loc[0] = 0;
	diamond_loc[1] = 0;
	// Current and previous coordinates for the object - set them the same initially
	m_iCurrentScreenX = m_iPreviousScreenX = lpix = px;
	m_iCurrentScreenY = m_iPreviousScreenY = py;
	// The object coordinate will be the top left of the object
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	// Record the ball size as both height and width
	m_iDrawWidth = pig_height;
	m_iDrawHeight = pig_width;
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


RunningPigDiamond::~RunningPigDiamond()
{
}

void RunningPigDiamond::Draw(){
	// Do not draw if it should not be visible
	if (!IsVisible())
		return;

	switch (pmode)
	{
	case 0: // not caught 
		pix = abs(m_iCurrentScreenX - lpix);
		switch (direct)
		{
		case 0: // go right			
			if (pix <= 20){
				rw.RenderImageWithMask(m_pEngine->GetSDLSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, rw.GetWidth(), rw.GetHeight());
			}
			else{
				rs.RenderImageWithMask(m_pEngine->GetSDLSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, rs.GetWidth(), rs.GetHeight());
			}
			break;
		case 1: // go left
			if (pix <= 20){
				lw.RenderImageWithMask(m_pEngine->GetSDLSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, lw.GetWidth(), lw.GetHeight());
			}
			else{
				ls.RenderImageWithMask(m_pEngine->GetSDLSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, ls.GetWidth(), ls.GetHeight());
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
		if (!isBombed){   // if is not bombed
			switch (direct)
			{
			case 0: rc.RenderImageWithMask(m_pEngine->GetSDLSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY + 30, rc.GetWidth(), rc.GetHeight()); break;
			case 1: lc.RenderImageWithMask(m_pEngine->GetSDLSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY + 30, lc.GetWidth(), lc.GetHeight()); break;
			default:
				break;
			}
		}
		else{   // bombed
			if (m_pEngine->GetTime() < l_time + 1000){  // keep the boom for some time
				boom.RenderImageWithMask(m_pEngine->GetSDLSurface(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, boom.GetWidth(), boom.GetHeight());
			}
			else{
				SetVisible(false);
			}
		}
		break;
	case 2: // get to the end
		m_pEngine->DrawScreenString(m_iCurrentScreenX, m_iCurrentScreenY, "$2", 0x000000); break;
		break;
	default:
		break;
	}

	StoreLastScreenPositionForUndraw();
}


void RunningPigDiamond::DoUpdate(int iCurrentTime){

	if (!IsVisible())
		return;
	// Do not do update if it should not be visible

	if (dia_help_c != -1){  // pig is caught or the diamond are not exist, cancel detection
		DiamondSearchAndStamp();
	}

	if (diamond_loc[0] != 0){  // behave like a diamond searching pig
		pmode = CatchableObject::HookDetection(2);
		if (dia_help_c == 0){  // pig has not arrived
			// move towards the nearest diamond
			if (m_iCurrentScreenX < diamond_loc[0]){
				m_iCurrentScreenX += 1;
				direct = 0;
				if (m_iCurrentScreenY + 40 < diamond_loc[1]){
					m_iCurrentScreenY += 1;
				}
				else if(m_iCurrentScreenY + 30 > diamond_loc[1]){
					m_iCurrentScreenY -= 1;
				}
			}
			else{
				m_iCurrentScreenX -= 1;
				direct = 1;
				if (m_iCurrentScreenY + 40 < diamond_loc[1]){
					m_iCurrentScreenY += 1;
				}
				else{
					m_iCurrentScreenY -= 1;
				}
			}
		}
		else{
			// start stamping on the diamond
			updown++;
			if ((int)(iCurrentTime/500) %2  == 0){  // make some animation when pig is here
				m_iCurrentScreenY += 1;
			}
			else{
				m_iCurrentScreenY -= 1;
			}
		}
		RedrawObjects();
	}
	else{ // behave like a normal running pig
		RunningPig::DoUpdate(iCurrentTime);
		pmode = RunningPig::pmode;
		direct = GetDirection();
		isBombed = RunningPig::isBombed;
	}
}




// Collect the closest diamond location 
void RunningPigDiamond::DiamondSearchAndStamp(){
	dia_num = m_pEngine->diamond_num;
	int d_e = m_pEngine->sob_num;
	int d_s = m_pEngine->gs_num;
	int diamond_counter = 0;
	int dia_visi = 0;
	DisplayableObject* pd;

	for (int i = d_s; i < d_e; i++){
		pd = m_pEngine->GetDisplayableObject(i);
		DiamondObject* p_dia = dynamic_cast<DiamondObject*>(pd);

		if (p_dia == NULL){
			return;
		}

		int dx = p_dia->GetDimondX();
		int dy = p_dia->GetDimondY();
		if (p_dia->IsVisible()){
			// if the pig is caught, then the diamond won't disappear
			if (pmode != 0){
				p_dia->PigLeave();
				diamond_loc[0] = 0;
				dia_help_c = -1; // pig gone, cancel detection 
				return;
			}

			// when pig come very close, tell the diamond that pig is coming
			if (dia_help_c == 0){
				if (m_iCurrentScreenX <dx + 2 && m_iCurrentScreenY + 40 < dy + 2 && m_iCurrentScreenY + 40 > dy - 2 && m_iCurrentScreenX >dx - 2){
					dia_help_c = 1; // pig arrived
					p_dia->PigArrive();
				}
				diamond_counter = 0;
				int dist = (m_iCurrentScreenX - dx)*(m_iCurrentScreenX - dx) + (m_iCurrentScreenY - dy)*(m_iCurrentScreenY - dy);
				// get the coordinates of the closest diamond
				if (dist < mini){
					mini = dist;
					diamond_loc[diamond_counter] = dx;
					diamond_counter++;
					diamond_loc[diamond_counter] = dy;			
				}
			}
			else{
				// count down 20s before the diamond disappear
				if (updown > 40 && p_dia->arrived == 1){
					p_dia->PigUpDown();
					updown = 0;
				}
			}
		}
		else{
			// if the diamond pig with is not visible
			dia_visi++;
			if (p_dia->arrived == 1){
				p_dia->PigLeave();
				dia_help_c = 0;
			}
			/* if the diamond is no longer exists, but the last nearest
			is this one, then reset it and let the pig search for the next
			nearest diamond */
			if (dx == diamond_loc[0] && dy == diamond_loc[1]){
				diamond_loc[0] = 0;
				diamond_loc[1] = 0;
				mini = 1000000;
				dia_help_c = 0;
			}
		}
	}

	if (dia_visi == dia_num){  // no diamond exists
		dia_help_c = -1;
	}
}