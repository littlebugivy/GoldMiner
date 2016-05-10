#include "header.h"
#include "Psyml5TileManager.h"


Psyml5TileManager::Psyml5TileManager()
	:TileManager(50,50)
{
}


Psyml5TileManager::~Psyml5TileManager()
{
}

void Psyml5TileManager::DrawTileAt(
	BaseEngine* pEngine,
	SDL_Surface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const{

	// Base class implementation just draws some grey tiles
	pEngine->DrawRectangle(
		iStartPositionScreenX,
		iStartPositionScreenY,
		iStartPositionScreenX + GetTileWidth() - 1,
		iStartPositionScreenY + GetTileHeight() - 1,
		pEngine->GetColour(GetValue(iMapX, iMapY)),
		pSurface);
}

