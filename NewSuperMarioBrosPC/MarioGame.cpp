#include <time.h>
#include <d3dx9.h>
#include "MarioGame.h"
#include "utils.h"
#include "MarioAnimationFactory.h"
#include "BrickGround.h"
#include "Physics.h"
#include "MarioState.h"
#include "Pipe.h"
#include "MetalBlock.h"
#include "Qbrick.h"
#include "Coin.h"
#include "Leaf.h"
#include "GreenMushroom.h"
#include "RedMushroom.h"
//#include "physics.h"


const float CMarioGame::GRAVITY_VELOCOTY = GRAV_VELOCITY;
DWORD last = 0;
LPD3DXFONT fontArial;
RECT rect;
Animation *qbAnim1 = new Animation(0, 3);
Animation *qbAnim2 = new Animation(0, 3);
CSprite *qbSprite;
QBrick *qb1;
QBrick *qb2;
Object *scrollBG;
int marioXlast=0;
Animation *coinAnim = new Animation(0, 2);
Coin *coin;
Leaf *leaf;
GreenMushroom * greenmushroom;
RedMushroom * redmushroom;

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

	koopaTroopaSprite = new CSprite(_SpriteHandler, KOOPA_TROOPA_GOOMBA_IMAGE, 17, 28, 48, 16);
	goobaSprite = new CSprite(_SpriteHandler, KOOPA_TROOPA_GOOMBA_IMAGE, 17, 28, 48, 16);

	KoopaTroopa* koopa2 =
		new KoopaTroopa(200, GROUND_Y + 200, 17, 28, -KoopaTroopa::KOOPA_VELOCITY_X, 0, -KoopaTroopa::KOOPA_VELOCITY_X, 0, 0, NULL, koopaTroopaSprite);
	
	KoopaTroopa* koopa = 
		new KoopaTroopa(450, GROUND_Y+200, 17, 28, -KoopaTroopa::KOOPA_VELOCITY_X, 0, -KoopaTroopa::KOOPA_VELOCITY_X, 0, 0, NULL, koopaTroopaSprite);
	koopa->setState(new KoopaNomalState(koopa));
	

	
	KoopaTroopa* redKoopa = 
		new RedKoopa(500, GROUND_Y+50, 17, 28,-KoopaTroopa::KOOPA_VELOCITY_X, 0, -KoopaTroopa::KOOPA_VELOCITY_X, 0, 0, NULL, koopaTroopaSprite);
	redKoopa->setState(new KoopaVulnerableState(redKoopa));
	


	Gooba* gooba = new Gooba(400, GROUND_Y+200, Gooba::WIDTH, Gooba::HEIGHT, -Gooba::SPEED_X, 0, -Gooba::SPEED_X, 0, 0, NULL, goobaSprite);
	;

	
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
	mObjectManager->addObject(koopa2);
	mObjectManager->addObject(redKoopa);



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
	//mObjectManager->addObject(ground4);
	BrickGround * ground5 = new BrickGround(1666 + 288, 8, 576, 16);
	//mObjectManager->addObject(ground5);
	BrickGround * ground6 = new BrickGround(2257 + 280, 8, 560, 16);
	//mObjectManager->addObject(ground6);

	Pipe * pipe1 = new Pipe(367, 40, 32, 48);
	mObjectManager->addObject(pipe1);
	MetalBlock *mb1 = new MetalBlock(263, 40, 48, 48);
	mObjectManager->addObject(mb1);
	MetalBlock *mb2 = new MetalBlock(295, 56, 48, 80);
	mObjectManager->addObject(mb2);

	
	qbSprite = new CSprite(_SpriteHandler, QBRICK_IMAGE, 16, 16, 5, 5);
	Gooba* hiddenGoomba = new Gooba(0, 0, Gooba::WIDTH, Gooba::HEIGHT, Gooba::SPEED_X,0,Gooba::SPEED_X,0,0,NULL,goobaSprite);
	Gooba* hiddenGoomba1 = new Gooba(0, 0, Gooba::WIDTH, Gooba::HEIGHT, Gooba::SPEED_X, 0, Gooba::SPEED_X, 0, 0, NULL, goobaSprite);
	qb1 = new QBrick(184, 73, 16, 16,hiddenGoomba, qbAnim1, qbSprite);
	mObjectManager->addObject(qb1);
	qb2 = new QBrick(184 + 16, 73, 16, 16, hiddenGoomba1, qbAnim2, qbSprite);
	mObjectManager->addObject(qb2);
	
	CSprite *backgroundImage = new CSprite(_SpriteHandler, SCROLLBG_IMAGE, 4096, 432, 1, 1);
	Animation *bgAnim = new Animation(0, 0);
	scrollBG = new Object(1000, 216, 4096, 432, 0, 0, 0, 0, 0, bgAnim, backgroundImage);

	/*coinSprite = new CSprite(_SpriteHandler, COIN, 16, 16, 3, 3);
	coin = new Coin(150, 73, 16, 16, coinAnim, coinSprite);
	mObjectManager->addObject(coin);

	leafSprite = new CSprite(_SpriteHandler, LEAF, 16, 16, 1, 1);
	leaf = new Leaf(100, 73, 16, 16, leafSprite);
	mObjectManager->addObject(leaf);

	greenmushroomSprite = new CSprite(_SpriteHandler, GREEN_MUSHROOM, 16, 16, 1, 1);
	greenmushroom = new GreenMushroom(1447, 300, 16, 16, greenmushroomSprite);
	mObjectManager->addObject(greenmushroom);

	redmushroomSprite = new CSprite(_SpriteHandler, RED_MUSHROOM, 16, 16, 1, 1);
	redmushroom = new RedMushroom(50, 50, 16, 16, redmushroomSprite);
	mObjectManager->addObject(redmushroom);*/
	
	
	mario = mObjectManager->getMario();

}

int xc = 0;

void CMarioGame::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t)
{
	// TO-DO: should enhance CGame to put a separate virtual method for updating game status


	mObjectManager->update(t);
	
	
	
	mario->ay -= GRAV_VELOCITY*t;
	
	qbAnim1->Update();
	if (Physics::ContainsPoint(qb1, mario->x, mario->top()))
	{
		qbAnim1->startFrame = 4;
		qbAnim1->endFrame = 4;
	}

	qbAnim2->Update();
	if (Physics::ContainsPoint(qb2, mario->x, mario->top()))
	{
		qbAnim2->startFrame = 4;
		qbAnim2->endFrame = 4;
	}
	
	mObjectManager->checkCollition();

	////paralaxBackground
	scrollBG->update(t);
	scrollBG->ay = 0;
	if (marioXlast < mario->x) // kiểm tra mario có thay đổi vị trí không
		scrollBG->ax = 0.001f;
	else if (marioXlast > mario->x)
		scrollBG->ax = -0.001f;
	else
		scrollBG->vx = 0;

	if (scrollBG->vx >= 0.1f)
		scrollBG->vx = 0.1f;
	else if (scrollBG->vx <= -0.1f)
		scrollBG->vx = -0.1f;
	marioXlast = mario->x;
	////////

	// Background
	/*d3ddv->StretchRect(
	_Background,			// from
	NULL,				// which portion?
	_BackBuffer,		// to
	NULL,				// which portion?
	D3DTEXF_NONE);*/

	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	int vpx = mario->x - 100;
	int vpy = 240;
	//int vpx = xc;
	if (vpx <= 0) vpx = 0;
	if (vpx >= 2485) vpx = 2485;
	xc += 1;
	
	
	
	scrollBG->render(vpx, vpy);

	foregroundImage->Render(1424, 360 - 288, vpx, vpy);
	
	//render all object in game
	mObjectManager->render(vpx,vpy);
	//mario->render(vpx, vpy);
	

	_SpriteHandler->End();

	rect.top = 0;
	rect.left = 20;
	rect.right = 240;
	rect.bottom = 100;
	char buffer[32] = { 0 };
	sprintf_s(buffer, "Mx: %d / My: %d       ", mario->x, mario->y);
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


