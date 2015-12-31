#include <time.h>
#include <d3dx9.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

#include "MarioGame.h"
#include "utils.h"
#include "MarioAnimationFactory.h"
#include "BrickGround.h"
#include "Physics.h"
#include "MarioState.h"
#include "Pipe.h"
#include "MetalBlock.h"
#include "Qbrick.h"
#include "Mushroom.h"
#include "Coin.h"
#include "Leaf.h"
#include "GoldBrick.h"
#include "MarioPowerBar.h"
#include "FirePiranha.h"
#include "KoopaTroopaState.h"
#include "RedFirePiranha.h"
using namespace std;

const float CMarioGame::GRAVITY_VELOCOTY = GRAV_VELOCITY;
DWORD lastTimeAPress, nowTimeAPress;
LPD3DXFONT fontArial;
RECT rect;
Object *scrollBG;
int marioXlast=0;
Animation *coinAnim = new Animation(0, 2);
Coin *coin;

CMarioGame* CMarioGame::sInstance;
CMarioGame* CMarioGame::getInstance(){
	return sInstance;
}
void LoadMap(ObjectManager * obManager, LPD3DXSPRITE _SpriteHandler, char * file);

CMarioGame::CMarioGame(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullScreen, int FrameRate) :
CGame(hInstance, Name, Mode, IsFullScreen, FrameRate)
{
	sInstance = this;
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
	//D3DXCreateFont(d3ddv, 30, 30, FW_BOLD, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, TEXT("Arial"), &fontArial);
	
	//end

	//_Background = CreateSurfaceFromFile(_d3ddv, BACKGROUND_FILE);

	HRESULT res = D3DXCreateSprite(_d3ddv, &_SpriteHandler);

	

	//khởi tạo mario
	mario_x = 20;
	mario_y = GROUND_Y + 100;;

	
	mario_vx = 0;
	mario_vx_last = 1.0f;
	mario_vy = 0;


	marioLargeSprite = new CSprite(_SpriteHandler, MARIO_LARGE_IMAGE, 32, 32, 195, 10);
	piranhaSprite = new CSprite(_SpriteHandler, PIRANHA_PLANT, 20, 36, 100, 10);
	pipeSprite = new CSprite(_SpriteHandler, PIPE_IMAGE, 32, 32, 1, 1);
	pipe32x40Sprite = new CSprite(_SpriteHandler, PIPE_IMAGE_40, 32, 40, 1, 1);
	koopaTroopaSprite = new CSprite(_SpriteHandler, KOOPA_TROOPA_GOOMBA_IMAGE, 18, 32, 48, 16);
	goobaSprite = new CSprite(_SpriteHandler, KOOPA_TROOPA_GOOMBA_IMAGE, 18, 32, 48, 16);
	mushroomSprite = new CSprite(_SpriteHandler, MUSHROOM_IMAGE, 16, 16, 1, 1);
	greenmushroomSprite = new CSprite(_SpriteHandler, GREEN_MUSHROOM, 16, 16, 1, 1);
	leafSprite = new CSprite(_SpriteHandler, LEAF, 16, 16, 1, 1);
	goldBrickAndPButton = new CSprite(_SpriteHandler, GOLDBRICK_IMAGE_AND_BUTTON, 16, 16, 1, 8);
	coinSprite = new CSprite(_SpriteHandler, COIN, 16, 16, 3, 3);
	qbSprite = new CSprite(_SpriteHandler, QBRICK_IMAGE, 16, 16, 5, 5);
	



	PiranhaPlant* piranhaPlant = new PiranhaPlant(1808, 31 + 28, piranhaSprite, pipeSprite);
	FirePiranha* firePiranha = new FirePiranha(1871 + 1, 39 + 24 + FirePiranha::HEIGHT / 2, piranhaSprite, pipeSprite);///x+1 do sai số
	RedFirePiranha* redFirePiranha = new RedFirePiranha(367 + 1, 39 + 24 + RedFirePiranha::HEIGHT / 2, piranhaSprite, pipe32x40Sprite);///x+1 do sai số
	
	
	/*KoopaTroopa* koopa2 =
		new KoopaTroopa(200, GROUND_Y + 200, 16, 28, -KoopaTroopa::KOOPA_VELOCITY_X, 0, -KoopaTroopa::KOOPA_VELOCITY_X, 0, 0, NULL, koopaTroopaSprite);
	
	KoopaTroopa* koopa = 
		new KoopaTroopa(450, GROUND_Y+200, 16, 28, -KoopaTroopa::KOOPA_VELOCITY_X, 0, -KoopaTroopa::KOOPA_VELOCITY_X, 0, 0, NULL, koopaTroopaSprite);
	koopa->setState(new KoopaNomalState(koopa));
	

	
	KoopaTroopa* redKoopa = 
		new RedKoopa(500, GROUND_Y+50, 16, 28,-KoopaTroopa::KOOPA_VELOCITY_X, 0, -KoopaTroopa::KOOPA_VELOCITY_X, 0, 0, NULL, koopaTroopaSprite);
	redKoopa->setState(new KoopaVulnerableState(redKoopa));
	
	KoopaTroopa* paraKoopa = new KoopaTroopa(130, 100, KoopaTroopa::PARA_SPEED_X, NULL, koopaTroopaSprite);
	paraKoopa->setState(new KoopaParaState(paraKoopa));*/


	//Gooba* gooba = new Gooba(400, GROUND_Y+200, Gooba::WIDTH, Gooba::HEIGHT, -Gooba::SPEED_X, 0, -Gooba::SPEED_X, 0, 0, NULL, goobaSprite);
	

	
	Mario* marioObject = new Mario(mario_x, mario_y, 32, 32, mario_vx, 0, 0, 0, 0, NULL, marioLargeSprite, NULL, NULL);
	
	
	//marioObject->setAnimationFactory(SmallMarioAnimationFactory::getInstance(marioObject));
	//marioObject->setState(new MarioStateSmall(marioObject));
	marioObject->setAnimationFactory(RaccoonMarioAnimationFactory::getInstance(marioObject));
	marioObject->setState(new MarioStateRaccoon(marioObject));

	//marioObject->setAnimationFactory(LargeMarioAnimationFactory::getInstance(marioObject));
	//marioObject->setState(new MarioStateLarge(marioObject));
	
	mObjectManager->addObject(marioObject);
	//mObjectManager->addObject(piranhaPlant);
	//mObjectManager->addObject(firePiranha);
	//mObjectManager->addObject(redFirePiranha);
	/*mObjectManager->addObject(koopa);	
	mObjectManager->addObject(gooba);
	mObjectManager->addObject(koopa2);
	mObjectManager->addObject(redKoopa);
	mObjectManager->addObject(paraKoopa);*/



	foregroundImage = new CSprite(_SpriteHandler, FOREGROUND_IMAGE, 2848, 720, 1, 1);

	D3DXCreateFont(d3ddv, 30, 0, FW_BOLD, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, TEXT("Arial"), &fontArial);

	//CSprite* nen = new CSprite(_SpriteHandler, L"nen.png", 48, 16, 1, 1);
	//Animation *nenAnim = new Animation(0, 0);

	/*for (int i = 0; i < 20; ++i){
		BrickGround* brickGround = new BrickGround(i*(nen->_Width), 16,48,16, nenAnim, nen);
		mObjectManager->addObject(brickGround);
	}*/
	/*mObjectManager->addObject(new BrickGround(300, GROUND_Y + 16, 48, 16, nenAnim, nen));
	mObjectManager->addObject(new BrickGround(500, GROUND_Y + 16, 48, 16, nenAnim, nen));
	BrickGround* brickGround = new BrickGround(100, GROUND_Y + 54, 48, 16, nenAnim, nen);
	mObjectManager->addObject(brickGround);*/

	
	/*BrickGround * ground1 = new BrickGround(315, 8, 624, 16);
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
	mObjectManager->addObject(ground6);*/
	LoadMap(mObjectManager, _SpriteHandler, "map1-1.txt");

	/*Pipe * pipe1 = new Pipe(367, 40, 32, 48);
	mObjectManager->addObject(pipe1);
	MetalBlock *mb1 = new MetalBlock(263, 40, 48, 48);
	mObjectManager->addObject(mb1);
	MetalBlock *mb2 = new MetalBlock(295, 56, 48, 80);
	mObjectManager->addObject(mb2);*/

	
	/*qbSprite = new CSprite(_SpriteHandler, QBRICK_IMAGE, 16, 16, 5, 5);
	Gooba* hiddenGoomba = new Gooba(0, 0, Gooba::WIDTH, Gooba::HEIGHT, Gooba::SPEED_X,0,Gooba::SPEED_X,0,0,NULL,goobaSprite);
	Gooba* hiddenGoomba1 = new Gooba(0, 0, Gooba::WIDTH, Gooba::HEIGHT, Gooba::SPEED_X, 0, Gooba::SPEED_X, 0, 0, NULL, goobaSprite);

	RedMushroom * mushroom1 = new RedMushroom(0, 0, 16, 16, 0, 0, 0, 0, 0, mushroomSprite);
	GreenMushroom * mushroom2 = new GreenMushroom(0, 0, 16, 16, 0, 0, 0, 0, 0, greenmushroomSprite);

	qb1 = new QBrick(184, 73, 16, 16, mushroom1, qbAnim1, qbSprite);
	mObjectManager->addObject(qb1);
	qb2 = new QBrick(184 + 16, 73, 16, 16, mushroom2, qbAnim2, qbSprite);
	mObjectManager->addObject(qb2);*/
	
	CSprite *backgroundImage = new CSprite(_SpriteHandler, SCROLLBG_IMAGE, 4096, 432, 1, 1);
	Animation *bgAnim = new Animation(0, 0);
	scrollBG = new Object(1000, 216, 4096, 432, 0, 0, 0, 0, 0, bgAnim, backgroundImage);

	/*coinSprite = new CSprite(_SpriteHandler, COIN, 16, 16, 3, 3);
	coin = new Coin(150, 73, 18, 18, coinAnim, coinSprite);
	mObjectManager->addObject(coin);*/

	
	

	
	
	mario = mObjectManager->getMario();

}

int xc = 0;

void CMarioGame::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t)
{
	mObjectManager->update(t);
	
	mObjectManager->checkCollition();

	////paralaxBackground
	scrollBG->update(t);
	scrollBG->ay = 0;
	if (mario->x < 100)
		scrollBG->vx = 0;
	else
	{
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
	}
	
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
	int vpy;
	if (mario->y > 120)
		vpy = mario->y + 120;
	else vpy = 240;
	
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
	rect.right = 640;//240
	rect.bottom = 100;
	char buffer[64] = { 0 };
	//sprintf_s(buffer, "%d %d" , mario->isAButtonPressed, mario->isBButtonPressed);//Mx: %d / My: %d
	MarioPowerBar* powerBar = mario->getPowerBar();
	sprintf_s(buffer, "%f %d", mario->getPowerBar()->getState(), mario->getPowerBar()->isPower());
	fontArial->DrawTextA(NULL, buffer, 20, &rect, DT_LEFT, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CMarioGame::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int t)
{
	if (IsKeyDown(DIK_X)){
		if (mario->isAButtonPressed == 1){
			if (GetTickCount() - lastTimeAPress >= 250 && GetTickCount() - lastTimeAPress<350)
			{
				mario->ay += Mario::ACCELERATION_Y_PLUS - Mario::ACCELERATION_Y;
				lastTimeAPress = 0;//để chặn việc liên tục tăng ay, chỉ cộng vào ay 1 lần
			}
		}
			
			
	}
	
	//if (IsKeyDown(DIK_Z)){
	//	mario->isBButtonPressed = 1;
	//}
	//else{
	//	mario->isBButtonPressed = 0;
	//}

	if (IsKeyDown(DIK_RIGHT))
	{
		mario->isRightButtonPressed = 1;
		mario->ax = Mario::ACCELERATION_X;
		mario->vx_last = mario->vx;//lưu lại vx để biết hướng của mario
	}
	else{
		mario->isRightButtonPressed = 0;
	}

	if (IsKeyDown(DIK_LEFT))
	{
		
		mario->isLeftButtonPressed = 1;
		mario->ax = -Mario::ACCELERATION_X;
		mario->vx_last = mario->vx;
		
	}
	else{
		mario->isLeftButtonPressed = 0;
	}
	if(mario->isLeftButtonPressed==0&&mario->isRightButtonPressed==0)//all key release
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
	
	
}

void CMarioGame::OnKeyDown(int KeyCode)
{
	MarioState* marioState = mario->getState();
	switch (KeyCode)
	{
	case DIK_X:
		mario->isAButtonPressed = 1;
		lastTimeAPress = GetTickCount();
		mario->onAPress();
		break;
	case DIK_Z:
		mario->isBButtonPressed = 1;
		mario->onBPress();
		break;
	}
	
}


void CMarioGame::OnKeyUp(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_X:
		mario->isAButtonPressed = 0;
		break;
	case DIK_Z:
		mario->isBButtonPressed = 0;
	}
}

void CMarioGame::LoadMap(ObjectManager * obManager, LPD3DXSPRITE _SpriteHandler, char* file)
{
	ifstream infile(file);
	string line;
	while (getline(infile, line))
	{
		stringstream ss(line);
		int i;
		vector<int> v;
		while (ss >> i)
			v.push_back(i);	
		/*switch (v[0])
		{
		case 1:
			BrickGround * brickGround = new BrickGround(v[1], v[2], v[3], v[4]);
			obManager->addObject(brickGround);
			break;
		case 2:
			Pipe *pipe = new Pipe(v[1], v[2], v[3], v[4]);
			obManager->addObject(pipe);
			break;
		case 3:
			MetalBlock * metal = new MetalBlock(v[1], v[2], v[3], v[4]);
			obManager->addObject(metal);
			break;
		}*/

		if (v[0] == 1)
		{
			BrickGround * brickGround = new BrickGround(v[1], v[2], v[3], v[4]);
			obManager->addObject(brickGround);
		}
		else if (v[0] == 2)
		{
			Pipe *pipe = new Pipe(v[1], v[2], v[3], v[4]);
			obManager->addObject(pipe);
		}
		else if (v[0] == 3)
		{
			MetalBlock * metal = new MetalBlock(v[1], v[2], v[3], v[4]);
			obManager->addObject(metal);
		}
		else if (v[0] == 4)
		{
			
			Animation *qbAnim = new Animation(0, 3);
			
			if (v[5] == 100)
			{
				RedMushroom * mushroom = new RedMushroom(0, 0, 16, 16, 0, 0, 0, 0, 0, mushroomSprite);
				QBrick *qBrick = new QBrick(v[1], v[2], v[3], v[4], mushroom, qbAnim, qbSprite);
				obManager->addObject(qBrick);
			}
			else
			{
				QBrick *qBrick = new QBrick(v[1], v[2], v[3], v[4], NULL, qbAnim, qbSprite);
				obManager->addObject(qBrick);
			}			
		}
		else if (v[0] == 5)
		{
			
			Animation * goldAnim = new Animation(0, 4);
			GoldBrick * goldBrick = new GoldBrick(v[1], v[2], v[3], v[4], goldAnim, goldBrickAndPButton,v[5]);
			obManager->addObject(goldBrick);
		}
		else if (v[0] == 6)
		{
			
			Coin *coin = new Coin(v[1], v[2], 16, 16, coinAnim, coinSprite);
			obManager->addObject(coin);
		}

		else if (v[0] == 10)
		{
			
			Gooba* gooba = new Gooba(v[1], v[2], Gooba::WIDTH, Gooba::HEIGHT, -Gooba::SPEED_X, 0, -Gooba::SPEED_X, 0, 0, NULL, goobaSprite);
			obManager->addObject(gooba);
		}
		else if (v[0] == 11)
		{
			//CSprite * koopaTroopaSprite = new CSprite(_SpriteHandler, KOOPA_TROOPA_GOOMBA_IMAGE, 18, 32, 48, 16);			
			if (v[3] == 1)
			{
				KoopaTroopa* koopa =
					new KoopaTroopa(v[1], v[2], 16, 28, -KoopaTroopa::KOOPA_VELOCITY_X, 0, -KoopaTroopa::KOOPA_VELOCITY_X, 0, 0, NULL, koopaTroopaSprite);
				koopa->setState(new KoopaNomalState(koopa));
				obManager->addObject(koopa);
			}
			else if (v[3] == 2)
			{
				KoopaTroopa* paraKoopa = new KoopaTroopa(v[1], v[2], KoopaTroopa::PARA_SPEED_X, NULL, koopaTroopaSprite);
				paraKoopa->setState(new KoopaParaState(paraKoopa));
				obManager->addObject(paraKoopa);
			}
			else if (v[3] == 3)
			{
				KoopaTroopa* vulnerableKoopa =
					new RedKoopa(v[1], v[2], 16, 28, -KoopaTroopa::KOOPA_VELOCITY_X, 0, -KoopaTroopa::KOOPA_VELOCITY_X, 0, 0, NULL, koopaTroopaSprite);
				vulnerableKoopa->setState(new KoopaVulnerableState(vulnerableKoopa));
				obManager->addObject(vulnerableKoopa);
			}
		}


	}
}