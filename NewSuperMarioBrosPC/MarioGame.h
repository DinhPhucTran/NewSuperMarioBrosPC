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


#define MAP_LEVEL 2;
#define DIRECT_LEFT 0;
#define DIRECT_RIGHT 1;

//#define MARIO_IMAGE_RIGHT L"mario3.bmp"
//#define MARIO_IMAGE_LEFT L"mario3.bmp"
#define BRICK L"brick.png"
#define MARIO_LARGE_IMAGE L"marioSprite32x32.png"
#define KOOPA_TROOPA_GOOMBA_IMAGE L"enemies4.png"
#define FOREGROUND_IMAGE L"foreground.png"
#define FOREGROUND_IMAGE_2 L"foreground2.png"
#define QBRICK_IMAGE L"qBrick.png"
#define SCROLLBG_IMAGE L"scrollBG3.png"
#define SCROLLBG_IMAGE_2 L"scrollBGHills.png"
#define GOLDBRICK_IMAGE_AND_BUTTON L"goldBrickAndButton.png"
#define PIRANHA_PLANT L"PiranhaPlant10x20x36.png"
#define PIPE_IMAGE L"pipe32.png"
#define PIPE_IMAGE_40 L"Pipe32x40.png"
#define PARA_GOOMBA L"paraGoomba.png"
#define SUPER_STAR L"SuperStar.png"
#define ITEMS_SPRITE L"items.png"
#define HORIZONTAL_PIPE L"HorizonPipe32.png"


#define GROUND_Y 45

#define BACKGROUND_FILE L"blocks.png"



#define GRAV_VELOCITY 0.00007f;//0.0001f original value

//#define VIEW_PORT_Y  600

class CMarioGame : public CGame
{
	static CMarioGame* sInstance;
public:
	static const float GRAVITY_VELOCOTY;
	CMarioGame(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullScreen, int FrameRate);
	static CMarioGame* getInstance();
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

	
	CSprite * marioSprite;
	CSprite * koopaTroopaGoombaSprite;
	CSprite * ground_middle;
	CSprite * brick;
	CSprite *mountain;
	CSprite *foregroundImage;
	CSprite *greenmushroomSprite;
	CSprite *pipe32x40Sprite;
	CSprite *goldBrickAndPButton;
	CSprite *pipeSprite;
	CSprite* piranhaSprite;
	CSprite * qbSprite;
	CSprite * paraGoombaSprite;
	CSprite * itemsSprite;
	CSprite* horizontalPipe;

	int score;
	int animationDelay=0;
protected:
	LPDIRECT3DSURFACE9 _Background;

	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int Delta)override;
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta)override;
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv)override;

	virtual void OnKeyDown(int KeyCode)override;
	virtual void OnKeyUp(int KeyCode)override;

	void RenderBackground(int view_port_x, int view_port_y);
	void LoadMap(ObjectManager * obManager, LPD3DXSPRITE _SpriteHandler, char* file);
};
#endif