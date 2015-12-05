#include <time.h>
#include <d3dx9.h>
#include "MarioGame.h"
#include "utils.h"
#include "MarioAnimationFactory.h"

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

	Mario* marioObject = new Mario(mario_x, mario_y, 36, 34, mario_vx, 0, 0, MARIO_ACCELERATION_X , 0, NULL, marioLargeSprite, NULL, NULL);
	//SmallMarioAnimationFactory* smallAnimationFactory = new SmallMarioAnimationFactory(mario);
	//mario->setAnimationFactory(smallAnimationFactory);
	ObjectManager* obManager = ObjectManager::getInstance();
	obManager->addObject(marioObject);
	mario = obManager->getMario();
	MarioAnimationFactory* largeAnimFactory =  LargeMarioAnimationFactory::getInstance(mario);
	mario->setAnimationFactory(largeAnimFactory);

	MarioAnimationFactory* raccoonAnimFactory = RaccoonMarioAnimationFactory::getInstance(mario);
	mario->setAnimationFactory(raccoonAnimFactory);

	// One sprite only :)
	ground_middle = new CSprite(_SpriteHandler, GROUND_MIDDLE, 32, 32, 1, 1);
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


	// NOTES: If there is a class for mario, this should be mario->Update(t);
	// Putting mario update here is NOT a good place


	//
	// Update mario status
	//
	mario->update(t);

	//
	// Animate mario if he is running
	//
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		////anim = rightWalkAnim;

		//if (mario_vx > 0) anim = rightWalkAnim;
		//if (mario_vx < 0) anim = leftWalkAnim;
		//if (mario_vx == 0)
		//{
		//	if (this->direction == 0)
		//		anim = leftStandAnim;
		//	else
		//		anim = rightStandAnim;
		//}
		//if (!_IsOnGround)
		//{
		//	if (direction == 0)
		//		anim = leftJumpAnim;
		//	else
		//		anim = rightJumpAnim;
		//}
		//anim->Update();
		
		mario->setAnimation(mario->mAnimationFactory->createAnimation());
		last_time = now;
	}

	//
	// Simulate fall down
	//
	if (mario->y > GROUND_Y) 
		mario->vy -= FALLDOWN_VELOCITY_DECREASE;
	else
	{
		mario->y = GROUND_Y;
		mario->vy = 0;
	}


	////
	////Mô phỏng gia tốc trọng trường 
	///TO-DO thay isOnGround bằng cách xử lý va chạm với gạch dưới đất
	///
	if (_IsOnGround == false)
	{
		mario_vy -= GRAV_VELOCITY;//mô phỏng trọng lực
		//mario_y = GROUND_Y;
		/*if (mario_vy < MAX_GRAV)
		mario_vy = -MAX_GRAV;*/
	}
	else
	{
		mario_vy = 0;
	}

	if (mario_y <= GROUND_Y && _IsFallOfGround == false)
		_IsOnGround = true;

	if (_IsOnGround)
		mario_y = GROUND_Y;
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
	for (int i = 0; i < 32 * 50; i += 32)
		ground_middle->Render(0, 0, 0, 16 + i, 16, vpx, VIEW_PORT_Y);

	for (int i = 0; i < 32 * 10; i += 32)
		ground_middle->Render(0, 0, 0, 16 + i, 16, vpx, VIEW_PORT_Y);

	int j = 0;
	brick->Render(0, 0, 0, 165 + j, 200, vpx, VIEW_PORT_Y);
	fallDown->Render(0, 0, 0, 600, 0, vpx, VIEW_PORT_Y);

	//
	//  Select correct sprite to render depends on which direction mario is facing
	//
	/*if (mario_vx > 0)			marioSprite->Render(anim, mario_x, mario_y, vpx, VIEW_PORT_Y);//mario_right->Render(496, 0, 28, mario_x, mario_y, vpx, VIEW_PORT_Y);
	else if (mario_vx < 0)		marioSprite->Render(194, 0, 26, mario_x, mario_y, vpx, VIEW_PORT_Y);
	else if (mario_vx_last < 0) marioSprite->Render(194, 0, 26, mario_x, mario_y, vpx, VIEW_PORT_Y);
	else						marioSprite->Render(anim, mario_x, mario_y, vpx, VIEW_PORT_Y);
	*/

	//marioSprite->Render(anim, mario_x, mario_y, vpx, VIEW_PORT_Y);
	mario->mSprite->Render(mario->getAnimation(), mario->x, mario->y, vpx, VIEW_PORT_Y);
	brick->Render(0, 0, 0, 100, 47, vpx, VIEW_PORT_Y);

	_SpriteHandler->End();
}

void CMarioGame::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int t)
{
	DWORD now = GetTickCount();
	if (IsKeyDown(DIK_RIGHT))
	{
		mario->vx = MARIO_MAX_SPEED;//mario đi phải
		mario->vx_last = mario->vx;//lưu lại vx để biết hướng của mario
		if (now - last > 1000 / ANIMATE_RATE)
		{
			if (mario->vx > MARIO_MAX_SPEED)
				mario->ax=0;
			//mario_vx += 0.05f;
			last = now;
			//mario_vx_last = mario_vx;
		}
	}
	else
	if (IsKeyDown(DIK_LEFT))
	{
		mario->vx = -MARIO_MAX_SPEED;
		mario->vx_last = mario->vx;
		if (now - last > 1000 / ANIMATE_RATE)
		{
			if (mario_vx < -MARIO_MAX_SPEED)
				mario->ax=0;
			//mario_vx -= 0.05f;
			last = now;
			//mario_vx_last = mario_vx;
		}
		

		//mario_vx_last = mario_vx;
	}
	else
	{
		/*mario_vx = 0;
		mario_left->ResetLeft();
		mario_right->Reset();*/

		if (now - last > 1000 / ANIMATE_RATE)
		{
			if (mario->vx > 0)
			{
				mario->vx -= 0.05f;
				if (mario->vx < 0)
					mario->vx = 0;
			}
				
			if (mario->vx < 0)
			{
				mario->vx += 0.05f;
				if (mario->vx > 0)
					mario->vx = 0;
			}
				
			last = now;
		}

		/*if (mario_vx > 0)
		{
			mario_vx -= 0.0000003f;
			if (mario_vx < 0 || mario_vx < 0.00005f)
				mario_vx = 0;
		}
		if (mario_vx < 0)
		{
			mario_vx += 0.0000003f;
			if (mario_vx > 0 || mario_vx > -0.0000005f)
				mario_vx = 0;
		}*/

		//mario_left->ResetLeft();
		//mario_right->Reset();
		//anim = standAnim;
	}
}

void CMarioGame::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_SPACE:
		if (mario->y <= GROUND_Y)
			mario->vy += JUMP_VELOCITY_BOOST;			// start jump if is not "on-air"
		_IsOnGround = false;
		break;

	}
}


