#include "header.h"
#include "templates.h"
#include "GoldenManEngine.h"
#include "HookObject.h"

/* static value, is set to 1 when the hook have got something, avoid multiple loading*/
int HookObject::load = 0; 

/*Hook is used to get catchable objects, it rotates into different angles so
the user can choose direct to drop the hook, can also trigger the bomb*/
HookObject::HookObject(GoldenManEngine* pEngine, int loc_x, int loc_y)
	:DisplayableObject(pEngine)
	, angle(-50)
	, move_direc(0)
	, hook_len1(20)
	, hook_len2(10)
	, mode(0)
	, m_pMainEngine(pEngine)
	, mloc_x(loc_x)
	, mloc_y(loc_y)
	, t_value(20)  // use this to control
	, explode(0) //  not explode
	, explode_x(0)
	, explode_y(0)
{
	// Current and previous coordinates for the object - set them the same initially
	m_iCurrentScreenX = m_iPreviousScreenX = root_x = GetEngine()->GetScreenWidth() / 2;
	m_iCurrentScreenY = m_iPreviousScreenY = root_y = 110;
	// The object coordinate will be the top left of the object
	m_iStartDrawPosX = -30;
	m_iStartDrawPosY = -30;
	// Record the ball size as both height and width
	m_iDrawWidth = 60;
	m_iDrawHeight = 60;

	// character image
	rotation.LoadImage("./psyml5_src/rotation.png");	
	up.LoadImage("./psyml5_src/up.png");
	down.LoadImage("./psyml5_src/down.png");

	// And make it visible
	SetVisible(true);
}


HookObject::~HookObject()
{
}

// use to draw a hook
void HookObject::HookDraw(int t_angle){
	rota_length = SDL_sqrt(SDL_pow((hook_len1 / SDL_sqrt(2) + hook_len2), 2.0) + SDL_pow(hook_len2, 2.0));
	hook_right_sx = m_iCurrentScreenX + hook_len1*SDL_cos(t_angle*M_PI / 180);
	hook_right_sy = m_iCurrentScreenY + hook_len1*SDL_sin(t_angle*M_PI / 180);
	hook_left_sx = m_iCurrentScreenX + hook_len1*SDL_cos((t_angle + 120)*M_PI / 180);
	hook_left_sy = m_iCurrentScreenY + hook_len1*SDL_sin((t_angle + 120)*M_PI / 180);
	GetEngine()->DrawScreenThickLine(m_iCurrentScreenX, m_iCurrentScreenY, hook_right_sx, hook_right_sy, 0xffffff, 3);
	GetEngine()->DrawScreenThickLine(hook_right_sx, hook_right_sy, m_iCurrentScreenX + rota_length*SDL_cos((t_angle + 15)*M_PI / 180), m_iCurrentScreenY + rota_length*SDL_sin((t_angle + 15)*M_PI / 180), 0xffffff, 3);
	GetEngine()->DrawScreenThickLine(m_iCurrentScreenX, m_iCurrentScreenY, hook_left_sx, hook_left_sy, 0xffffff, 3);
	GetEngine()->DrawScreenThickLine(hook_left_sx, hook_left_sy, m_iCurrentScreenX + rota_length*SDL_cos((t_angle + 105)*M_PI / 180), m_iCurrentScreenY + rota_length*SDL_sin((t_angle + 105)*M_PI / 180), 0xffffff, 3);
}

void HookObject::Draw()
{
	switch (mode)
	{
	case 0:  // rotation
		rotation.RenderImageWithMask(m_pMainEngine->GetForeground(),
			0, 0,
			388, 15,
			rotation.GetWidth(), rotation.GetHeight());
		HookObject::load = 0;
		HookDraw(angle);		
		break;
	case 1:		// drop	
		up.RenderImageWithMask(m_pMainEngine->GetForeground(),
			0, 0,
			388, 3,
			up.GetWidth(), up.GetHeight());
		HookDraw(drop_angle);
		GetEngine()->DrawLine(root_x, root_y, m_iCurrentScreenX, m_iCurrentScreenY, 0xffffff);	
		break;
	case 2:		// back hitting wall
	case 3:     // back with gold
		down.RenderImageWithMask(m_pMainEngine->GetForeground(),
			0, 0,
			388, 20,
			down.GetWidth(), down.GetHeight());
		HookObject::load = 1;
		HookDraw(drop_angle);
		GetEngine()->DrawLine(root_x, root_y, m_iCurrentScreenX, m_iCurrentScreenY, 0xffffff);
		break;
	default:
		break;
	}

	// Bomb detection
	BombTileManager& tm = m_pMainEngine->GetTileManager();
	int itsize = tm.GetTileHeight();
	int xDiff = abs(m_iCurrentScreenX - mloc_x);
	int yDiff = abs(m_iCurrentScreenY - mloc_y);

	if (explode == 0 && (xDiff*xDiff + yDiff*yDiff < (itsize / 2 + 20)*(itsize / 2 + 20))){
		explode = 1;
		mode = 2;
		explode_x = m_iCurrentScreenX;
		explode_y = m_iCurrentScreenY;
	}

	// tile animation
	if (explode == 1 && t_value > 5){
		t_value -= 1;
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++){
				tm.UpdateTile(m_pMainEngine, i, j, t_value);
			}
		}
	}

	if (t_value == 5){
			for (int i = 0; i < 3; i++){
				for (int j = 0; j < 3; j++){
					tm.UpdateTile(m_pMainEngine, i, j, -1);
				}
			}
			t_value = -1;
			explode = -1;
	}

	StoreLastScreenPositionForUndraw();
}



void HookObject::DoUpdate(int iCurrentTime)
{
	if (mode ==0 && GetEngine()->IsKeyPressed(SDLK_DOWN)){
		mode = 1;     // drop the hook
		RedrawWholeScreen();
		drop_angle = angle;

		x_ini_speed = (int)(10 * SDL_cos((drop_angle + 60)*M_PI / 180));
		y_ini_speed = (int)(10 * SDL_sin((drop_angle + 60)*M_PI / 180));
	}


	switch (mode)
	{
	case 0: Rotation(); break;   //  rotation
	case 1: Drop(); break;		//  drop
	case 2: HookBack(0); break;  // back hitting the wall
	case 3: HookBack(1); break;  // back with gold
	default:
		break;
	}
	RedrawObjects();
}

// Hook rotation
void HookObject::Rotation(){
	switch (move_direc)
	{
	case 0: angle += 5;
		if (angle == 110){
			move_direc = 1;		// left
		}
		break;
	case 1: angle -= 5;
		if (angle == -50){
			move_direc = 0;		// right
		}
		break;
	default:
		break;
	}

}

// Hook drop
void HookObject::Drop(){
	m_iCurrentScreenX += x_ini_speed;
	m_iCurrentScreenY += y_ini_speed;

	if (m_iCurrentScreenX < 40 || m_iCurrentScreenX > 760 || m_iCurrentScreenY> 550){
		mode = 2;
		HookBack(0);
		RedrawWholeScreen();
	}
}


// Hook back
void HookObject::HookBack(int condition){
	switch (condition)
	{
	case 0 :// touch the wall back
		x_speed = x_ini_speed*2;
		y_speed = y_ini_speed*2;
		break;
	case 1: // get the gold back
		x_speed = x_ini_speed;
		y_speed = y_ini_speed;
		break;
	default:
		break;
	}

	m_iCurrentScreenX -= x_speed;
	m_iCurrentScreenY -= y_speed;

	// when the hook back close to the end
	if ((m_iCurrentScreenX > root_x - 5 || m_iCurrentScreenX < root_x + 5) && m_iCurrentScreenY < root_y + 5){
		m_iCurrentScreenX = root_x;
		m_iCurrentScreenY = root_y;
		mode = 0;
		angle = drop_angle;
	}



}

void HookObject::getGold(){
	mode = 3;
	RedrawWholeScreen();
	HookBack(1);
}


int HookObject::getAngle(){
	return drop_angle;
}

