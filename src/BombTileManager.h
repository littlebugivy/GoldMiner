#pragma once
#include "tilemanager.h"
#include "JPGImage.h"
class BombTileManager :
	public TileManager
{
public:
	BombTileManager();
	~BombTileManager();

	// Draw a tile at a location on the screen determined by the tile
	// position and the base X and Y co-ordinates
	// OVERRIDE THIS TO DRAW YOUR TILE!!!
	// Draw a tile
	virtual void DrawTileAt(
		BaseEngine* pEngine,
		SDL_Surface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const;
private:
	ImageData bomb;
};

