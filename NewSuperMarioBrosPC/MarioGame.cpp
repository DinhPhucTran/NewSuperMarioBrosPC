#include <time.h>
#include <d3dx9.h>
#include "MarioGame.h"
#include "utils.h"
#include "MarioAnimationFactory.h"
#include "BrickGround.h"
#include "Physics.h"
#include"MarioState.h"
//#include "physics.h"


DWORD last = 0;
//Animation *rightWalkAnim = new Animation(14, 16);
//Animation *leftWalkAnim = new Animation(1, 3);
//Animation *rightStandAnim = new Animation(17, 17);
//Animation *leftStandAnim = new Animation(0, 0);
//Animation *leftJumpAnim = new Animation(4, 4);
//Animation *rightJumpAnim = new Animation(13, 13);
CMarioGame::CMarioGame(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullScreen, int FrameRate) :
CGame(hInstance, Name, Mode, IsFullScreen, FrameRate)
{
	marioSmallSprite = NULL;
}

CMarioGame::~CMarioGame()
{
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
	mario_y = GROUND_Y;

	_IsOnGround = true;

	mario_vx = 0;
	mario_vx_last = 1.0f;
	mario_vy = 0;

	marioSmallSprite = new CSprite(_SpriteHandler, MARIO_SMALL_IMAGE, 36, 34, 50, 18);
	marioLargeSprite = new CSprite(_SpriteHandler, MARIO_LARGE_IMAGE, 60, 60, 195, 15);
	koopaTroopaSprite = new CSprite(_SpriteHandler, KOOPA_TROOPA_IMAGE, 17, 28, 48, 16);
	goobaSprite = new CSprite(_SpriteHandler, GOOBA, 32, 32, 12, 4);

	KoopaTroopa* koopa = 
		new KoopaTroopa(450, GROUND_Y, 17, 28, -KoopaTroopa::KOOPA_VELOCITY_X, 0, -KoopaTroopa::KOOPA_VELOCITY_X, 0, 0, NULL, koopaTroopaSprite);
	koopa->setAnimationFactory(new KoopaAnimationFactory(koopa));
	koopa->setState(new KoopaSlidingState());
	
	KoopaTroopa* redKoopa = 
		new RedKoopa(500, GROUND_Y, 17, 28, KoopaTroopa::KOOPA_VELOCITY_X, 0, KoopaTroopa::KOOPA_VELOCITY_X, 0, 0, NULL, koopaTroopaSprite);
	//redKoopa->setAnimationFactory(new RedKoopaAnimationFactory(redKoopa));
	Gooba* gooba = new Gooba(400, GROUND_Y, 32, 32, -0.15f, 0, -0.5f, 0, 0, NULL, goobaSprite);
	gooba->setAnimationFactory(new GoobaAnimationFactory(gooba));
	gooba->setAnimation(gooba->mAnimationFactory->createAnimation());

	mObjectManager->addObject(redKoopa);
	Mario* marioObject = new Mario(mario_x, mario_y, 36, 34, mario_vx, 0, 0, 0 , 0, NULL, marioLargeSprite, NULL, NULL);
	//SmallMarioAnimationFactory* smallAnimationFactory = new SmallMarioAnimationFactory(mario);
	//mario->setAnimationFactory(smallAnimationFactory);
	marioObject->setAnimationFactory(LargeMarioAnimationFactory::getInstance(marioObject));
	marioObject->setState(new MarioStateLarge(marioObject));
	
	mObjectManager->addObject(marioObject);
	mObjectManager->addObject(koopa);
	mObjectManager->addObject(gooba);
	mario = mObjectManager->getMario();


	AnimationFactory* largeAnimFactory =  LargeMarioAnimationFactory::getInstance(mario);
	mario->setAnimationFactory(largeAnimFactory);




	

	CSprite* nen = new CSprite(_SpriteHandler, L"nen.png", 72, 18, 1, 1);
	Animation *nenAnim = new Animation(0, 0);

	for (int i = 0; i < 20; ++i){
		BrickGround* brickGround = new BrickGround(i*(nen->_Width), GROUND_Y-37,72,18, nenAnim, nen);
		mObjectManager->addObject(brickGround);
	}

	BrickGround* brickGround = new BrickGround(100, GROUND_Y + 80, 72, 18, nenAnim, nen);
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


	//
	// Update all object status
	//
	mObjectManager->update(t);
	mObjectManager->checkCollition();


	//trọng trường
	/*mario->vy -= GRAV_VELOCITY;
	if (mario->y <= GROUND_Y){
		mario->y = GROUND_Y;
		mario->vy = 0;
	}*/
	
	mario->ay -= GRAV_VELOCITY;
	if (mario->y <= GROUND_Y){
		mario->y = GROUND_Y;
		mario->vy = 0;
		mario->ay = 0;
	}

	////
	////Mô phỏng gia tốc trọng trường 
	///TO-DO thay isOnGround bằng cách xử lý va chạm với gạch dưới đất
	///
	//if (_IsOnGround == false)
	//{
	//	mario->vy -= GRAV_VELOCITY;//mô phỏng trọng lực
	//	//mario_y = GROUND_Y;
	//	if (mario->vy < MAX_GRAV)
	//	mario_vy = -MAX_GRAV;
	//}
	//else
	//{
	//	mario->vy = 0;
	//}

	//if (mario->y <= GROUND_Y && _IsFallOfGround == false)
	//	_IsOnGround = true;

	//if (_IsOnGround)
	//	mario_y = GROUND_Y;
	
	////////////////////////////////////////////////////
	////////////////////////////////////////////////////

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
	brick->Render(0, 0, 0, 165 + j, 200, vpx, VIEW_PORT_Y);
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
		//mario->vx = MARIO_MAX_SPEED;//mario đi phải
		mario->ax = Mario::ACCELERATION_X;
		mario->vx_last = mario->vx;//lưu lại vx để biết hướng của mario
	}
	else
	if (IsKeyDown(DIK_LEFT))
	{
		//mario->vx = -MARIO_MAX_SPEED;
		mario->ax = -Mario::ACCELERATION_X;
		mario->vx_last = mario->vx;
	}
	else//all key release
	{
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
		if (mario->ay == 0){
			mario->ay = 0.015f;
		}
	}
}

void CMarioGame::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_SPACE:
		if (mario->ay == 0){
			mario->ay = 0.012f;
			last_time = GetTickCount();
			
		}
		
		
		break;
	}
	
}


