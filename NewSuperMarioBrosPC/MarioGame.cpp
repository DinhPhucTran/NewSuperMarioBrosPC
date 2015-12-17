﻿#include <time.h>
#include <d3dx9.h>
#include "MarioGame.h"
#include "utils.h"
#include "MarioAnimationFactory.h"
#include "BrickGround.h"
#include "Physics.h"
#include "MarioState.h"
#include "Pipe.h"
//#include "physics.h"


const float CMarioGame::GRAVITY_VELOCOTY = GRAV_VELOCITY;
DWORD last = 0;
LPD3DXFONT fontArial;
RECT rect;

CMarioGame::CMarioGame(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullScreen, int FrameRate) :
CGame(hInstance, Name, Mode, IsFullScreen, FrameRate)
{
	
}

CMarioGame::~CMarioGame()
{
	delete mObjectManager;
	delete marioSmallSprite;
	delete marioLargeSprite;
}

void CMarioGame::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	srand((unsigned)time(NULL));

	// TO-DO: not a very good place to initial sprite handler
	D3DXCreateSprite(d3ddv, &_SpriteHandler);

	///font debug
	D3DXCreateFont(d3ddv, 30, 30, FW_BOLD, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, TEXT("Arial"), &fontArial);
	
	//end

	_Background = CreateSurfaceFromFile(_d3ddv, BACKGROUND_FILE);

	HRESULT res = D3DXCreateSprite(_d3ddv, &_SpriteHandler);

	//khởi tạo mario
	mario_x = 20;
	mario_y = GROUND_Y + 100;;

	
	mario_vx = 0;
	mario_vx_last = 1.0f;
	mario_vy = 0;

	marioSmallSprite = new CSprite(_SpriteHandler, MARIO_SMALL_IMAGE, 16, 16, 50, 18);
	marioLargeSprite = new CSprite(_SpriteHandler, MARIO_LARGE_IMAGE, 32, 32, 195, 10);

	koopaTroopaSprite = new CSprite(_SpriteHandler, KOOPA_TROOPA_IMAGE, 17, 28, 48, 16);
	goobaSprite = new CSprite(_SpriteHandler, GOOBA, 32, 32, 12, 4);

	KoopaTroopa* koopa = 
		new KoopaTroopa(450, GROUND_Y+200, 17, 28, -KoopaTroopa::KOOPA_VELOCITY_X, 0, -KoopaTroopa::KOOPA_VELOCITY_X, 0, 0, NULL, koopaTroopaSprite);
	koopa->setAnimationFactory(new KoopaAnimationFactory(koopa));
	koopa->setState(new KoopaNomalState(koopa));
	
	KoopaTroopa* redKoopa = 
		new RedKoopa(500, GROUND_Y+50, 17, 28,-KoopaTroopa::KOOPA_VELOCITY_X, 0, -KoopaTroopa::KOOPA_VELOCITY_X, 0, 0, NULL, koopaTroopaSprite);
	redKoopa->setState(new KoopaVulnerableState(redKoopa));
	mObjectManager->addObject(redKoopa);


	Gooba* gooba = new Gooba(400, GROUND_Y+200, 32, 32, -Gooba::SPEED_X, 0, -Gooba::SPEED_X, 0, 0, NULL, goobaSprite);
	gooba->setAnimationFactory(new GoobaAnimationFactory(gooba));
	gooba->setAnimation(gooba->mAnimationFactory->createAnimation());

	
	Mario* marioObject = new Mario(mario_x, mario_y, 32, 32, mario_vx, 0, 0, 0 , 0, NULL, marioLargeSprite, NULL, NULL);
	
	
	//marioObject->setAnimationFactory(SmallMarioAnimationFactory::getInstance(marioObject));
	//marioObject->setState(new MarioStateSmall(marioObject));
	marioObject->setAnimationFactory(RaccoonMarioAnimationFactory::getInstance(marioObject));
	marioObject->setState(new MarioStateRaccoon(marioObject));

	//marioObject->setAnimationFactory(LargeMarioAnimationFactory::getInstance(marioObject));
	//marioObject->setState(new MarioStateLarge(marioObject));
	
	mObjectManager->addObject(marioObject);
	mObjectManager->addObject(koopa);
	mObjectManager->addObject(gooba);
	mario = mObjectManager->getMario();




	foregroundImage = new CSprite(_SpriteHandler, FOREGROUND_IMAGE, 2848, 720, 1, 1);

	D3DXCreateFont(d3ddv, 30, 0, FW_BOLD, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, TEXT("Arial"), &fontArial);

	CSprite* nen = new CSprite(_SpriteHandler, L"nen.png", 48, 16, 1, 1);
	Animation *nenAnim = new Animation(0, 0);

	/*for (int i = 0; i < 20; ++i){
		BrickGround* brickGround = new BrickGround(i*(nen->_Width), 16,48,16, nenAnim, nen);
		mObjectManager->addObject(brickGround);
	}*/
	/*mObjectManager->addObject(new BrickGround(300, GROUND_Y + 16, 48, 16, nenAnim, nen));
	mObjectManager->addObject(new BrickGround(500, GROUND_Y + 16, 48, 16, nenAnim, nen));
	BrickGround* brickGround = new BrickGround(100, GROUND_Y + 54, 48, 16, nenAnim, nen);
	mObjectManager->addObject(brickGround);*/

	
	BrickGround * ground1 = new BrickGround(315, 8, 624, 16);
	mObjectManager->addObject(ground1);
	BrickGround * ground2 = new BrickGround(620 + 230, 16, 464, 32);
	mObjectManager->addObject(ground2);
	BrickGround * ground3 = new BrickGround(1153 + 176, 8, 352, 16);
	mObjectManager->addObject(ground3);
	BrickGround * ground4 = new BrickGround(1537 + 40, 8, 80, 16);
	mObjectManager->addObject(ground4);
	BrickGround * ground5 = new BrickGround(1666 + 288, 8, 576, 16);
	mObjectManager->addObject(ground5);
	BrickGround * ground6 = new BrickGround(2257 + 280, 8, 560, 16);
	mObjectManager->addObject(ground6);

	Pipe * pipe1 = new Pipe(348 + 16, 32, 32, 64);
	mObjectManager->addObject(pipe1);

}

int xc = 0;

void CMarioGame::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t)
{
	// TO-DO: should enhance CGame to put a separate virtual method for updating game status


	mObjectManager->update(t);
	//
	// Update all object status
	mario->ay -= GRAV_VELOCITY*t;
	/*if (mario->y <= GROUND_Y){
		mario->y = GROUND_Y;
		mario->vy = 0;
		mario->ay = 0;
	}*/
	


	
	
	mObjectManager->checkCollition();

	


	// Background
	d3ddv->StretchRect(
	_Background,			// from
	NULL,				// which portion?
	_BackBuffer,		// to
	NULL,				// which portion?
	D3DTEXF_NONE);

	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	int vpx = mario->x - 100;
	int vpy = 240;
	//int vpx = xc;
	if (vpx <= 0) vpx = 0;
	xc += 1;
	
	foregroundImage->Render(1417, 360 - 288, vpx, vpy);


	//render all object in game
	mObjectManager->render(vpx,vpy);
	//mario->render(vpx, vpy);
	

	_SpriteHandler->End();

	rect.top = 0;
	rect.left = 20;
	rect.right = 240;
	rect.bottom = 100;
	char buffer[32] = { 0 };
	sprintf_s(buffer, "%d/%d", mario->x, mario->y);
	fontArial->DrawTextA(NULL, buffer, 20, &rect, DT_LEFT, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CMarioGame::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int t)
{
	
	//DWORD now = GetTickCount();
	if (IsKeyDown(DIK_RIGHT))
	{
		mario->isLeftButtonPress = 0;
		mario->isRightButtonPress = 1;
		mario->ax = Mario::ACCELERATION_X;
		mario->vx_last = mario->vx;//lưu lại vx để biết hướng của mario
	}
	else
	if (IsKeyDown(DIK_LEFT))
	{
		mario->isRightButtonPress = 0;
		mario->isLeftButtonPress = 1;
		mario->ax = -Mario::ACCELERATION_X;
		mario->vx_last = mario->vx;
	}
	else//all key release
	{
		mario->isLeftButtonPress = 0;
		mario->isRightButtonPress = 0;
		if (mario->vx_last > 0)
		{
			//mario->vx -= 0.00000015f;
			mario->ax = -Mario::ACCELERATION_X;
			if (mario->vx <= 0){
				mario->vx = 0;
				mario->ax = 0;
			}
		}else
		if (mario->vx_last < 0)
		{
			//mario->vx += 0.00000015f;
			mario->ax = Mario::ACCELERATION_X;
			if (mario->vx >= 0){
				mario->vx = 0;
				mario->ax = 0;
			}
		}
	}
	
	

	if (IsKeyDown(DIK_SPACE)){
		last_time = GetTickCount();
		if (mario->vy == 0){
			if (GetTickCount() - last_time <= 100)
				mario->jumpUp();
			else{
				mario->jumpUp();
			}
		}
	}
}

void CMarioGame::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_SPACE:
				
		
		break;
	}
	
}


