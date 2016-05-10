#include "header.h"
#include "BombTileManager.h"
#include "GoldenManEngine.h"


BombTileManager::BombTileManager()
	:TileManager(60,60)
{
	bomb.LoadImage("./psyml5_src/bomb.png");
}


BombTileManager::~BombTileManager()
{
}


void BombTileManager::DrawTileAt(
	BaseEngine* pEngine,
	SDL_Surface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	// New implementation draws things of different sizes
	switch (GetValue(iMapX, iMapY))
	{
	case 0:
		break;
	case 1:
		// Display the bomb
		bomb.RenderImageWithMask(pEngine->GetBackground(),
			0,0,
			iStartPositionScreenX,
			iStartPositionScreenY,
			bomb.GetWidth(),
			bomb.GetHeight());
		break;
	case -1:
		pEngine->DrawBackgroundRectangle(
			iStartPositionScreenX,
			iStartPositionScreenY,
			iStartPositionScreenX + GetTileWidth() - 1,
			iStartPositionScreenY + GetTileHeight() - 1,
			0x854e1f);
		break;
	default:
		// Random size and color explosion
		int size = rand() % 40;
		int start = rand() % 20;
		pEngine->DrawBackgroundRectangle(
			iStartPositionScreenX,
			iStartPositionScreenY,
			iStartPositionScreenX + GetTileWidth() - 1,
			iStartPositionScreenY + GetTileHeight() - 1,
			0x854e1f);
		pEngine->DrawBackgroundOval(
			iStartPositionScreenX + start,
			iStartPositionScreenY + start,
			iStartPositionScreenX + start +size - 1,
			iStartPositionScreenY + start +size - 1,
			pEngine->GetColour(GetValue(iMapX, iMapY)));
		break;
	}
}
