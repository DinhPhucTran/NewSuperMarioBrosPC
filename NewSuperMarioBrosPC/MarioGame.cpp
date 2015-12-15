#include <time.h>
#include <d3dx9.h>
#include "MarioGame.h"
#include "utils.h"
#include "MarioAnimationFactory.h"
#include "BrickGround.h"
#include "Physics.h"
#include"MarioState.h"
//#include "physics.h"


const float CMarioGame::GRAVITY_VELOCOTY = GRAV_VELOCITY;
DWORD last = 0;

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


	_Background = CreateSurfaceFromFile(_d3ddv, BACKGROUND_FILE);

	HRESULT res = D3DXCreateSprite(_d3ddv, &_SpriteHandler);

	//khởi tạo mario
	mario_x = 20;
	mario_y = 500;

	_IsOnGround = true;

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
		new RedKoopa(500, GROUND_Y+200, 17, 28, KoopaTroopa::KOOPA_VELOCITY_X, 0, KoopaTroopa::KOOPA_VELOCITY_X, 0, 0, NULL, koopaTroopaSprite);
	//redKoopa->setAnimationFactory(new RedKoopaAnimationFactory(redKoopa));
	mObjectManager->addObject(redKoopa);

	Gooba* gooba = new Gooba(400, GROUND_Y+200, 32, 32, -0.15f, 0, -0.5f, 0, 0, NULL, goobaSprite);
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






	

	CSprite* nen = new CSprite(_SpriteHandler, L"nen.png", 48, 16, 1, 1);
	Animation *nenAnim = new Animation(0, 0);

	for (int i = 0; i < 20; ++i){
		BrickGround* brickGround = new BrickGround(i*(nen->_Width), GROUND_Y,48,16, nenAnim, nen);
		mObjectManager->addObject(brickGround);
	}
	mObjectManager->addObject(new BrickGround(20, GROUND_Y + 16, 48, 16, nenAnim, nen));
	mObjectManager->addObject(new BrickGround(500, GROUND_Y + 16, 48, 16, nenAnim, nen));
	BrickGround* brickGround = new BrickGround(100, GROUND_Y + 54, 48, 16, nenAnim, nen);
	mObjectManager->addObject(brickGround);


	brick = new CSprite(_SpriteHandler, BRICK, 32, 32, 1, 1);

	fallDown = new CSprite(_SpriteHandler, CHECK_FALL, 4, 619, 1, 1);
	//fallBox = new Object(600, 0, 4, 619, 0, 0, fallDown);
	//_CollisionBox = new Object(mario_x, mario_y, 32, 32, mario_vx, mario_vy, mario_right);
	_IsFallOfGround = false;


}

int xc = 0;

void CMarioGame::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t)
{
	// TO-DO: should enhance CGame to put a separate virtual method for updating game status


	mObjectManager->update(t);
	//
	// Update all object status
	mario->ay -= GRAV_VELOCITY*t;
	if (mario->y <= GROUND_Y){
		mario->y = GROUND_Y;
		mario->vy = 0;
		mario->ay = 0;
	}
	


	
	
	mObjectManager->checkCollition();

	


	// Background
	d3ddv->StretchRect(
	_Background,			// from
	NULL,				// which portion?
	_BackBuffer,		// to
	NULL,				// which portion?
	D3DTEXF_NONE);

	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	int vpx = mario->x - 400;
	int VIEW_PORT_Y = 480;
	//int vpx = xc;
	if (vpx <= 0) vpx = 0;
	xc += 1;
	/*for (int i = 0; i < 32 * 50; i += 32)
		ground_middle->Render(0, 0, 0, 16 + i, 16, vpx, VIEW_PORT_Y);*/

	/*for (int i = 0; i < 32 * 10; i += 32)
		ground_middle->Render(0, 0, 0, 16 + i, 16, vpx, VIEW_PORT_Y);*/

	int j = 0;
	brick->Render(0, 0, 0, 0, 0, vpx, VIEW_PORT_Y);
	fallDown->Render(0, 0, 0, 600, 0, vpx, VIEW_PORT_Y);
	

	//render all object in game
	mObjectManager->render(vpx,VIEW_PORT_Y);
	//mario->render(vpx, VIEW_PORT_Y);
	brick->Render(0, 0, 0, 100, 47, vpx, VIEW_PORT_Y);

	_SpriteHandler->End();
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
			if (GetTickCount()- last_time <=100)
				mario->ay = Mario::ACCELERATION_Y;
			else{
				mario->ay = Mario::ACCELERATION_Y;
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


