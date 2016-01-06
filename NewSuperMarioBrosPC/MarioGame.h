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


#define MAP_LEVEL 1;
#define DIRECT_LEFT 0;
#define DIRECT_RIGHT 1;

#define MARIO_LARGE_IMAGE L"Images\\marioSprite32x32.png"
#define KOOPA_TROOPA_GOOMBA_IMAGE L"Images\\enemies4.png"
#define FOREGROUND_IMAGE L"Images\\foreground1.png"
#define FOREGROUND_IMAGE_2 L"Images\\foreground2.png"
#define QBRICK_IMAGE L"Images\\qBrick.png"
#define SCROLLBG_IMAGE L"Images\\scrollBG3.png"
#define SCROLLBG_IMAGE_2 L"Images\\scrollBGHills.png"
#define GOLDBRICK_IMAGE_AND_BUTTON L"Images\\goldBrickAndButton.png"
#define PIRANHA_PLANT L"Images\\PiranhaPlant10x20x36.png"
#define PIPE_IMAGE L"Images\\pipe32.png"
#define PIPE_IMAGE_40 L"Images\\Pipe32x40.png"
#define PARA_GOOMBA L"Images\\paraGoomba.png"
#define SUPER_STAR L"Images\\SuperStar.png"
#define ITEMS_SPRITE L"Images\\items.png"
#define HORIZONTAL_PIPE L"Images\\HorizonPipe32.png"
#define PIPEDOOR_IMAGE L"Images\\pipeDoor.png"
#define TITLE_BACKGROUND_IMAGE L"Images\\title.png"
#define PAUSE_BACKGROUND_IMAGE L"Images\\pause.png"
#define GAMEOVER_BACKGROUND_IMAGE L"Images\\gameover.png"
#define CURSOR_IMAGE L"Images\\cursor.png"

#define GAME_TITLE 1
#define GAME_RUN 2
#define GAME_PAUSE 3
#define GAME_END 4


#define GRAV_VELOCITY 0.00007f;

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
	MarioState *lastState;
	DWORD last_time;		// this is to control the animate rate of kitty

	//LPDIRECT3DSURFACE9 Background;

	Mario* marioObject;
	CSprite * marioSprite;
	CSprite * koopaTroopaGoombaSprite;
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
	CSprite * doorPipeSprite;
	CSprite *cursorSprite;
	CSprite *backgroundImage;
	Object *scrollBG;

	int vpx;
	int vpy;
	int score;
	int animationDelay=0;
	int mapLevel = MAP_LEVEL;
	int gameStatus=GAME_TITLE;
	int lastLives;

	int titleSelector = 1;
	int pauseSelector = 1;
	int gameoverSelector = 1;
protected:
	LPDIRECT3DSURFACE9 titleBackground;
	LPDIRECT3DSURFACE9 pauseBackground;
	LPDIRECT3DSURFACE9 gameoverBackground;

	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int Delta)override;
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta)override;
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv)override;

	virtual void OnKeyDown(int KeyCode)override;
	virtual void OnKeyUp(int KeyCode)override;

	void RenderBackground(int view_port_x, int view_port_y);
	void LoadMap(ObjectManager * obManager, LPD3DXSPRITE _SpriteHandler, char* file);
	void ResetMario();
	void SetBackground();
};
#endif