#ifndef _RECTANGLES_H_
#define _RECTANGLES_H_

#include <d3dx9.h>

#include "game.h"
#include "sprite.h"
#include "MarioObject.h"
#include "ObjectManager.h"
//#include "KoopaTroopa.h"
#include "MarioAnimationFactory.h"
#include "RedKoopa.h"
#include "gooba.h"



#define DIRECT_LEFT 0;
#define DIRECT_RIGHT 1;

//#define MARIO_IMAGE_RIGHT L"mario3.bmp"
//#define MARIO_IMAGE_LEFT L"mario3.bmp"
#define BRICK L"brick.png"
#define MARIO_SMALL_IMAGE L"marioSmall.png"
#define MARIO_LARGE_IMAGE L"marioSprite32x32.png"
#define KOOPA_TROOPA_GOOMBA_IMAGE L"enemies4.png"
#define FOREGROUND_IMAGE L"foreground.png"
#define QBRICK_IMAGE L"qBrick.png"
#define SCROLLBG_IMAGE L"scrollBG3.png"
#define MUSHROOM_IMAGE L"redMushroom.png"
#define GOLDBRICK_IMAGE L"goldBrick.png"
#define COIN L"coin.png"
#define LEAF L"leaf.png"
#define GREEN_MUSHROOM L"greenMushroom.png"
#define RED_MUSHROOM L"redMushroom.png"
#define PIRANHA_PLANT L"PiranhaPlant10x20x36.png"
#define PIPE_IMAGE L"pipe32.png"


#define GROUND_Y 45

#define BACKGROUND_FILE L"blocks.png"



#define GRAV_VELOCITY 0.00007f;//0.0001f original value

//#define VIEW_PORT_Y  600

class CMarioGame : public CGame
{
public:
	static const float GRAVITY_VELOCOTY;
	CMarioGame(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullScreen, int FrameRate);
	~CMarioGame();

	LPD3DXSPRITE _SpriteHandler;
	

	int mario_x;			// position of mario
	int mario_y;

	float mario_vx;			// velocity of mario
	float mario_vy;

	float mario_vx_last;	// last vx of mario before stop ( to determine the direction of mario )
	LPD3DXFONT fontArial;
	ObjectManager* mObjectManager = ObjectManager::getInstance();
	Mario* mario;

	DWORD last_time;		// this is to control the animate rate of kitty

	//LPDIRECT3DSURFACE9 Background;

	CSprite * marioSmallSprite;
	CSprite * marioLargeSprite;
	CSprite * goobaSprite;
	CSprite * koopaTroopaSprite;
	CSprite * ground_middle;
	CSprite * brick;
	CSprite * mountain;
	CSprite *foregroundImage;
	CSprite * mushroomSprite;
	CSprite *coinSprite;
	CSprite *leafSprite;
	CSprite *greenmushroomSprite;
	CSprite *redmushroomSprite;

	int animationDelay=0;
	//Object * fallBox;
protected:
	LPDIRECT3DSURFACE9 _Background;

	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int Delta)override;
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta)override;
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv)override;

	virtual void OnKeyDown(int KeyCode)override;
	virtual void OnKeyUp(int KeyCode)override;

	void RenderBackground(int view_port_x, int view_port_y);
};
#endif