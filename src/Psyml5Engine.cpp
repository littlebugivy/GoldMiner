#include "header.h"
#include "templates.h"
#include "BaseEngine.h"
#include "Psyml5Engine.h"
#include "JPGImage.h"
#include "Psyml5Object1.h"
#include "Psyml5Object2.h"
#include "Psyml5TileManager.h"


Psyml5Engine::Psyml5Engine()
	: BaseEngine(6) // Pass 6 to superclass constructor
	, ball(NULL)
	// Initialise pointers to NULL
{	
}

Psyml5Engine::~Psyml5Engine()
{
}


void Psyml5Engine::SetupBackgroundBuffer()
{
	FillBackground(0);
	int width = GetScreenWidth();
	int height = GetScreenHeight();


	//BACKGROUNG SHAPES
	DrawBackgroundPolygon(200, 100, 220, 160, 280, 180, 220, 200, 200, 280, 180, 200, 120, 180, 180, 160, 0xedc951); // YELLOW STAR
	DrawBackgroundPolygon(400, 0, 420, 0, 800, 370, 800, 390, 0xcc2a36); //RED BAND
	DrawBackgroundOval(520, 110, 680, 270, 0xcc2a36); // RED EYE
	// BUTTTON
	DrawBackgroundRectangle(10, 10, 120, 50, 0xcc2a36);
	

	DrawBackgroundString(200, 550, "SUCH A BEAUTIFUL DAY", 0xffffff, NULL);

	// Specify how many tiles wide and high
	m_oTiles.SetSize(10, 1);
	// Set up the tiles
	for (int x = 0; x < 10; x++)
			m_oTiles.SetValue(x, 0, rand() % 20);
	// Specify the screen x,y of top left corner
	m_oTiles.SetBaseTilesPositionOnScreen(150, 450);
	// Tell it to draw tiles from x1,y1 to x2,y2 in tile array,
	// to the background of this screen
	m_oTiles.DrawAllTiles(this, this->GetBackground(), 0, 0, 9, 0);

	//IMAGE -NOSE
	// Draw an image loaded from a file.
	ImageData im, im2;
	// Load the image file into an image object - at the normal size
	im2.LoadImage("nose.png");
	// Create a second image from the first, by halving the size
	im.ShrinkFrom(&im2, 3);
	im.RenderImage(this->GetBackground(),
		0, 0,
		400 - im.GetWidth() / 2, 350 - im.GetHeight() / 2,
		im.GetWidth(), im.GetHeight());
	nose_start_X = 400 - im.GetWidth() / 2;
	nose_start_Y = 350 - im.GetHeight() / 2;
	nose_X = im.GetWidth();
	nose_Y = im.GetHeight();


}

void Psyml5Engine::MouseDown(int iButton, int iX, int iY)
{
	if (iX > 10 && iY > 10 && iX < 120 && iY < 50){
		if (iButton == SDL_BUTTON_LEFT)
		{
				Redraw(true);
		}
	}
	printf("%d %d\n", iX, iY);
}



int Psyml5Engine::InitialiseObjects()
{

	
	// Record the fact that we are about to change the array - so it doesn't get
	//used elsewhere without reloading it
	DrawableObjectsChanged();
	// Destroy any existing objects
	DestroyOldObjects();

	
	// Creates an array to store the objects
	// Needs to have room for the NULL at the end
	CreateObjectArray(7);
	// You MUST set the array entry after the last one that you create to NULL, so
	//that the system knows when to stop.
	// i.e. The LAST entry has to be NULL. The fact that it is NULL is used in
	//order to work out where the end of the array is.
	for (int i = 0; i < 5; i++){
		StoreObjectInArray(i, new Psyml5Object1(this));
	}		

	ball = new Psyml5Object2(this);
	ball->SetPosition(100, 100);
	ball->SetSpeed(10.0, 10.0);
	
	StoreObjectInArray(5, ball);
	StoreObjectInArray(6, NULL);
	return 0;
}


void Psyml5Engine::DrawStringsOnTop(){
	char buf[128];
	sprintf(buf, "BallBeat: %d", ball->ball_beat);
	DrawScreenString(150, 40, buf, 0xff00ff, NULL);
}

void Psyml5Engine::DrawStringsUnderneath()
{
	DrawScreenString(15, 15, "Button", 0x000000, NULL);	
}

void Psyml5Engine::UnDrawStrings()
{
	// Clear the top of the screen, since we about to draw text on it.
	CopyBackgroundPixels(0, 0, GetScreenWidth(), 70);
}



