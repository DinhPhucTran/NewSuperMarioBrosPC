#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <d3d9.h>
#include <d3dx9.h>
#include "animation.h"

class CSprite {
public:
	LPDIRECT3DTEXTURE9 _Image;				// The container of all the sprites
	LPD3DXSPRITE _SpriteHandler;

	int _Index;								// Current sprite index
	int _Width;								// Sprite width
	int _Height;							// Sprite height
	int _Count;								// Number of sprites
	int _SpritePerRow;						// Number of sprites per row

	CSprite::CSprite(LPD3DXSPRITE SpriteHandler, LPWSTR FilePath, int Width, int Height, int Count, int SpritePerRow);
	void Next();
	void Reset();
	void SetIndex(int index);
	void NextLeft();
	void ResetLeft();

	// Render current sprite at location (X,Y)
	void Render(int firstSpriteX, int firstSpriteY, int distanceBetweenSprites, int X, int Y, int vpx, int vpy);
	void Render(int X, int Y, int vpx, int vpy);
	void Render(Animation *anim, int x, int y, int vpx, int vpy);
	void Render(int X, int Y);
	~CSprite();
};

#endif