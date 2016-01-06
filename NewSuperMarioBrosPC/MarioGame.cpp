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
#include "SuperStar.h"
#include "GoobaFactory.h"
#include "Door.h"
#include "DoorPipe.h"
#include "Hole.h"
using namespace std;

const float CMarioGame::GRAVITY_VELOCOTY = GRAV_VELOCITY;
DWORD lastTimeAPress, nowTimeAPress;
LPD3DXFONT fontArial;
RECT rect;

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
}

void CMarioGame::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	srand((unsigned)time(NULL));
	D3DXCreateSprite(d3ddv, &_SpriteHandler);

	HRESULT res = D3DXCreateSprite(_d3ddv, &_SpriteHandler);
	
	//khởi tạo mario
	mario_x = 20;
	mario_y = 100;	
	mario_vx = 0;
	mario_vx_last = 1.0f;
	mario_vy = 0;

	//Remove old sprite
	if (marioSprite != NULL)
		delete marioSprite;
	if (piranhaSprite != NULL)
		delete piranhaSprite;
	if (pipeSprite != NULL)
		delete pipeSprite;
	if (pipe32x40Sprite != NULL)
		delete pipe32x40Sprite;
	if (koopaTroopaGoombaSprite != NULL)
		delete koopaTroopaGoombaSprite;
	if (goldBrickAndPButton != NULL)
		delete goldBrickAndPButton;
	if (qbSprite != NULL)
		delete qbSprite;
	if (paraGoombaSprite != NULL)
		delete paraGoombaSprite;
	if (itemsSprite != NULL)
		delete itemsSprite;
	if (horizontalPipe != NULL)
		delete horizontalPipe;
	if (doorPipeSprite != NULL)
		delete doorPipeSprite;
	if (cursorSprite != NULL)
		delete cursorSprite;

	////init sprites
	marioSprite = new CSprite(_SpriteHandler, MARIO_LARGE_IMAGE, 32, 32, 195, 10);
	piranhaSprite = new CSprite(_SpriteHandler, PIRANHA_PLANT, 20, 36, 100, 10);
	pipeSprite = new CSprite(_SpriteHandler, PIPE_IMAGE, 32, 32, 1, 1);
	pipe32x40Sprite = new CSprite(_SpriteHandler, PIPE_IMAGE_40, 32, 40, 1, 1);
	koopaTroopaGoombaSprite = new CSprite(_SpriteHandler, KOOPA_TROOPA_GOOMBA_IMAGE, 22, 32, 48, 16);
	goldBrickAndPButton = new CSprite(_SpriteHandler, GOLDBRICK_IMAGE_AND_BUTTON, 16, 16, 1, 8);
	qbSprite = new CSprite(_SpriteHandler, QBRICK_IMAGE, 16, 16, 5, 5);
	paraGoombaSprite = new CSprite(_SpriteHandler, PARA_GOOMBA, 32, 32, 4, 4);
	itemsSprite = new CSprite(_SpriteHandler, ITEMS_SPRITE, 16, 16, 8, 8);
	horizontalPipe = new CSprite(_SpriteHandler, HORIZONTAL_PIPE, 34, 34, 8, 2);
	doorPipeSprite = new CSprite(_SpriteHandler, PIPEDOOR_IMAGE, 32, 32, 4, 4);

	titleBackground = CreateSurfaceFromFile(_d3ddv, TITLE_BACKGROUND_IMAGE);
	pauseBackground = CreateSurfaceFromFile(_d3ddv, PAUSE_BACKGROUND_IMAGE);
	gameoverBackground = CreateSurfaceFromFile(_d3ddv, GAMEOVER_BACKGROUND_IMAGE);
	cursorSprite = new CSprite(_SpriteHandler, CURSOR_IMAGE, 16, 16, 1, 1);
	
	
	ResetMario();

	//SuperStar* superStar = new SuperStar(100, 100, itemsSprite);
	//GoobaFactory* goombaFactory = new GoobaFactory(400, 128, 1);	
	//mObjectManager->addObject(goombaFactory);
	//mObjectManager->addObject(superStar);	
		

	D3DXCreateFont(d3ddv, 30, 0, FW_BOLD, 0, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, TEXT("Arial"), &fontArial);
	
	SetBackground();
}

void CMarioGame::SetBackground()
{
	if (mapLevel == 1){
		foregroundImage = new CSprite(_SpriteHandler, FOREGROUND_IMAGE, 2848, 720, 1, 1);
		LoadMap(mObjectManager, _SpriteHandler, "map1-1.txt");
		backgroundImage = new CSprite(_SpriteHandler, SCROLLBG_IMAGE, 4096, 432, 1, 1);
	}
	else{
		foregroundImage = new CSprite(_SpriteHandler, FOREGROUND_IMAGE_2, 2848, 928, 1, 1);
		LoadMap(mObjectManager, _SpriteHandler, "map1-2.txt");
		backgroundImage = new CSprite(_SpriteHandler, SCROLLBG_IMAGE_2, 4096, 432, 1, 1);
	}
	Animation *bgAnim = new Animation(0, 0);
	scrollBG = new Object(1000, 216, 4096, 432, 0, 0, 0, 0, 0, bgAnim, backgroundImage);
}

void CMarioGame::ResetMario()
{
	//return to last state
	if (lastState != NULL)
	{
		marioObject = new Mario(mario_x, mario_y, 32, 32, mario_vx, 0, 0, 0, 0, NULL, marioSprite, NULL, NULL);
		if (lastState->getName() == MarioStateLarge::STATE_NAME)
			marioObject->setState(new MarioStateLarge(marioObject));
		else if (lastState->getName() == MarioStateSuperInvincible::STATE_NAME)
			marioObject->setState(new MarioStateSuperInvincible(marioObject));
		else if (lastState->getName() == MarioStateRaccoon::STATE_NAME)
			marioObject->setState(new MarioStateRaccoon(marioObject));
		else
			marioObject->setState(new MarioStateSmall(marioObject));
	}

	else
	{
		marioObject = new Mario(mario_x, mario_y, 32, 32, mario_vx, 0, 0, 0, 0, NULL, marioSprite, NULL, NULL);
		marioObject->setState(new MarioStateLarge(marioObject));
	}
	marioObject->lives = 4;
	mObjectManager->addObject(marioObject);
	mario = mObjectManager->getMario();
}

void CMarioGame::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t)
{
	switch (gameStatus)
	{
	case GAME_TITLE:
	{
					   d3ddv->StretchRect(
						   titleBackground,			
						   NULL,	
						   _BackBuffer,	
						   NULL,		
						   D3DTEXF_NONE);
					   _SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
					   switch (titleSelector)
					   {
					   case 1:
						   cursorSprite->Render(108, 134);
						   break;
					   case 2:
						   cursorSprite->Render(112, 152);
						   break;
					   }
					   
					   _SpriteHandler->End();

	}
		break;

	case GAME_RUN:
	{

					 mObjectManager->update(t);

					 mObjectManager->checkCollition();

					 if (mario->getState()->getName()==MarioStateDie::STATE_NAME)
						 if (GetTickCount() - mario->timeToDie > 450)
						 {
							lastLives = mario->lives;
							mObjectManager->removeAllObject();
							delete foregroundImage;
							delete scrollBG;
							LoadResources(d3ddv);
							mario->lives = lastLives;
						 }
					 if (mario->lives < 0)
						 gameStatus = GAME_END;

					 if (mario->x > 2700)
					 {
						 mObjectManager->removeAllObject();						 
						 if (mapLevel == 1)
						 {
							 lastState = mario->getState();
							 lastLives = mario->lives;
							 mapLevel = 2;
							 delete foregroundImage;
							 delete scrollBG;
							 LoadResources(d3ddv);
							 mario->lives = lastLives;

							 /*lastState = mario->getState();
							 lastLives = mario->lives;
							 mapLevel = 2;
							 delete foregroundImage;
							 delete scrollBG;
							 mObjectManager->removeAllObject();
							 ResetMario();							 
							 SetBackground();*/ //?CPU tăng cao bất thường? :(
							
						 }							 
						 else if (mapLevel==2)
						 {
							 gameStatus = GAME_END;
						 }
						 
					 }
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
					 //////

					 _SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);					 
					 if (mario->y > 120)
					 {
						 vpx = mario->x - 90;
						 vpy = mario->y + 72;
						 if (vpy > 420)
							 vpy = 420;
					 }
					 else if (mario->y < -20)
					 {
						 if (mapLevel == 1)
						 {
							 vpx = 2240;
							 vpy = -64;
						 }
						 if (mapLevel == 2)
						 {
							 vpx = 1072;
							 vpy = mario->y + 72;
							 if (vpy <= -288)
								 vpy = -288;
						 }
					 }
					 else
					 {
						 vpx = mario->x - 90;
						 vpy = 192;
					 }

					 if (vpx <= 0) vpx = 0;
					 if (vpx >= 2490) vpx = 2490;


					scrollBG->render(vpx, vpy);

					 if (mapLevel == 1)
						 foregroundImage->Render(1424, 360 - 288, vpx, vpy);
					 else if (mapLevel == 2)
						 foregroundImage->Render(1424, -32, vpx, vpy);

	
					 mObjectManager->render(vpx, vpy);
		
					 _SpriteHandler->End();

					 ///draw text
					 rect.top = 0;
					 rect.left = 20;
					 rect.right = 640;//240
					 rect.bottom = 100;
					 char buffer[64] = { 0 };
					 sprintf_s(buffer, "Lives: %d              ", mario->lives);
					 MarioPowerBar* powerBar = mario->getPowerBar();
					 fontArial->DrawTextA(NULL, buffer, 10, &rect, DT_LEFT, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
		break;

	case GAME_PAUSE:
		d3ddv->StretchRect(
			pauseBackground,
			NULL,
			_BackBuffer,
			NULL,
			D3DTEXF_NONE);

		_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		switch (pauseSelector)
		{
		case 1:
			cursorSprite->Render(106, 105);
			break;
		case 2:
			cursorSprite->Render(80, 130);
			break;
		case 3:
			cursorSprite->Render(115, 155);
			break;
		default:
			break;
		}
		
		_SpriteHandler->End();

		break;

	case GAME_END:
		d3ddv->StretchRect(
			gameoverBackground,
			NULL,
			_BackBuffer,
			NULL,
			D3DTEXF_NONE);

		_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		switch (gameoverSelector)
		{
		case 1:
			cursorSprite->Render(92, 112);
			break;
		case 2:
			cursorSprite->Render(110, 140);
			break;
		}

		_SpriteHandler->End();

		break;

	}
	
}

void CMarioGame::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int t)
{
	switch (gameStatus)
	{
	case GAME_RUN:
		if (IsKeyDown(DIK_X)){
			if (mario->isAButtonPressed == 1){
				if (GetTickCount() - lastTimeAPress >= 250 && GetTickCount() - lastTimeAPress<350)
				{
					mario->ay += Mario::ACCELERATION_Y_PLUS - Mario::ACCELERATION_Y;
					lastTimeAPress = 0;//để chặn việc liên tục tăng ay, chỉ cộng vào ay 1 lần
				}
			}
		}
		if (IsKeyDown(DIK_DOWN)){
			if (mario->canSitDown == 1)
				mario->sitDown();
			mario->isGoingDown = 1;
			return;
		}
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
		if (mario->isLeftButtonPressed == 0 && mario->isRightButtonPressed == 0)//all key release
		{
			if (mario->vx_last > 0)
			{
				//mario->vx -= 0.00000015f;
				mario->ax = -Mario::ACCELERATION_X;
				if (mario->vx <= 0){
					mario->vx = 0;
					mario->ax = 0;
				}
			}
			else
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
		break;

	default:
		break;
	}
}

void CMarioGame::OnKeyDown(int KeyCode)
{
	switch (gameStatus)
	{
	case GAME_TITLE:
		switch (KeyCode)
		{		
		case DIK_RETURN:
			switch (titleSelector)
			{
			case 1:
				marioObject->setState(new MarioStateSuperInvincible(marioObject));
				gameStatus = GAME_RUN;
				break;
			case 2:
				PostMessage(_hWnd, WM_QUIT, 0, 0);
				break;
			}
			break;

			case DIK_DOWN:
				titleSelector++;
				if (titleSelector > 2)
					titleSelector = 1;
				break;

			case DIK_UP:
				titleSelector--;
				if (titleSelector < 1)
					titleSelector = 2;
				break;
		}
		
		break;

	case GAME_RUN:
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
		case DIK_ESCAPE:
			gameStatus = GAME_PAUSE;
			break;
		}
		break;

	case GAME_PAUSE:
		switch (KeyCode)
		{
		case DIK_ESCAPE:
			gameStatus = GAME_RUN;
			break;

		case DIK_DOWN:
			pauseSelector++;
			if (pauseSelector > 3)
				pauseSelector = 1;
			break;

		case  DIK_UP:
			pauseSelector--;
			if (pauseSelector < 1)
				pauseSelector = 3;
			break;

		case DIK_RETURN:
			switch (pauseSelector)
			{
			case 1:
				gameStatus = GAME_RUN;
				break;

			case 2:
				mObjectManager->removeAllObject();
				ResetMario();
				delete backgroundImage;
				delete foregroundImage;
				SetBackground();
				gameStatus = GAME_RUN;
				break;

			case 3:
				PostMessage(_hWnd, WM_QUIT, 0, 0);
				break;
			}
			break;
		}
		break;

	case GAME_END:
		switch (KeyCode)
		{
		case DIK_DOWN:
			gameoverSelector++;
			if (gameoverSelector > 2)
				gameoverSelector = 1;
			break;

		case  DIK_UP:
			gameoverSelector--;
			if (gameoverSelector < 1)
				gameoverSelector = 2;
			break;

		case DIK_RETURN:
			switch (gameoverSelector)
			{
			case 1:
				mapLevel = 1;
				mObjectManager->removeAllObject();
				ResetMario();
				delete backgroundImage;
				delete foregroundImage;
				SetBackground();
				gameStatus = GAME_RUN;
				break;

			case 2:
				PostMessage(_hWnd, WM_QUIT, 0, 0);
				break;
			}
		}
		break;

	}
}


void CMarioGame::OnKeyUp(int KeyCode)
{
	if (gameStatus == GAME_RUN)
	{
		switch (KeyCode)
		{
		case DIK_X:
			mario->isAButtonPressed = 0;
			break;
		case DIK_Z:
			mario->isBButtonPressed = 0;
			break;
		case DIK_DOWN:
			mario->standUp();
			break;
		case DIK_1:
			mario->x = 1000;
			break;
		case DIK_2:
			mario->x = 2000;
			break;
		case DIK_3:
			mario->x = 3000;
			break;
		case DIK_R:
			mario->setState(new MarioStateRaccoon(mario));
			break;
		case DIK_S:
			mario->setState(new MarioStateSmall(mario));
			break;
		case DIK_L:
			mario->setState(new MarioStateLarge(mario));
			break;
		case DIK_I:
			mario->setState(new MarioStateSuperInvincible(mario));
			break;
		}
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
			
			if (v[5] == 1)
			{
				RedMushroom * mushroom = new RedMushroom(0, 0, 16, 16, 0, 0, 0, 0, 0, itemsSprite);
				QBrick *qBrick = new QBrick(v[1], v[2], v[3], v[4], mushroom, qbAnim, qbSprite);
				obManager->addObject(qBrick);
			}
			else if (v[5] == 2){//coin
				Coin * coin = new Coin(0, 0, 16, 16, itemsSprite);
				QBrick *qBrick = new QBrick(v[1], v[2], v[3], v[4], coin, qbAnim, qbSprite);
				obManager->addObject(qBrick);
			}
			else if (v[5] == 3){//superStar
				SuperStar * superStar = new SuperStar(0,0, itemsSprite);
				QBrick *qBrick = new QBrick(v[1], v[2], v[3], v[4], superStar, qbAnim, qbSprite);
				obManager->addObject(qBrick);
			}
			else if (v[5] == 4){//one up
				GreenMushroom * oneUp = new GreenMushroom(0, 0, 16, 16, 0, 0, 0, 0, 0, itemsSprite);
				QBrick *qBrick = new QBrick(v[1], v[2], v[3], v[4], oneUp, qbAnim, qbSprite);
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
			
			StaticCoin *coin = new StaticCoin(v[1], v[2], 16, 16, coinAnim, itemsSprite);
			obManager->addObject(coin);
		}

		else if (v[0] == 7)
		{
			DoorPipe * pipe = new DoorPipe(v[1], v[2], v[3], v[4], v[5], doorPipeSprite, v[6], v[7]);
			obManager->addObject(pipe);
		}
		else if (v[0] == 8)
		{
			Door * door = new Door(v[1], v[2], v[3], v[4], v[5], v[6]);
			obManager->addObject(door);
		}

		else if (v[0] == 9)
		{
			Hole *hole = new Hole(v[1], -16, v[2], 32);
			obManager->addObject(hole);
		}

		else if (v[0] == 10)
		{
			
			Gooba* gooba = new Gooba(v[1], v[2], Gooba::WIDTH, Gooba::HEIGHT, -Gooba::SPEED_X, 0, -Gooba::SPEED_X, 0, 0, NULL, koopaTroopaGoombaSprite);
			if (v[3] == 1){
				gooba->setState(new GoobaParaState(gooba));
			}
			obManager->addObject(gooba);
			
		}
		else if (v[0] == 11)
		{
			//CSprite * koopaTroopaSprite = new CSprite(_SpriteHandler, KOOPA_TROOPA_GOOMBA_IMAGE, 18, 32, 48, 16);			
			if (v[3] == 1)
			{
				KoopaTroopa* koopa =
					new KoopaTroopa(v[1], v[2], 16, 28, -KoopaTroopa::KOOPA_VELOCITY_X, 0, -KoopaTroopa::KOOPA_VELOCITY_X, 0, 0, NULL, koopaTroopaGoombaSprite);
				koopa->setState(new KoopaNomalState(koopa));
				obManager->addObject(koopa);
			}
			else if (v[3] == 2)
			{
				KoopaTroopa* paraKoopa = new KoopaTroopa(v[1], v[2], KoopaTroopa::PARA_SPEED_X, NULL, koopaTroopaGoombaSprite);
				paraKoopa->setState(new KoopaParaState(paraKoopa));
				obManager->addObject(paraKoopa);
			}
			else if (v[3] == 3)
			{
				KoopaTroopa* vulnerableKoopa =
					new KoopaTroopa(v[1], v[2], 16, 28, -KoopaTroopa::KOOPA_VELOCITY_X, 0, -KoopaTroopa::KOOPA_VELOCITY_X, 0, 0, NULL, koopaTroopaGoombaSprite);
				vulnerableKoopa->setState(new KoopaVulnerableState(vulnerableKoopa));
				obManager->addObject(vulnerableKoopa);
			}
		}
		else if (v[0] == 12)
		{		
			if (v[3] == 1)
			{
				RedKoopa* koopa =
					new RedKoopa(v[1], v[2], 16, 28, -KoopaTroopa::KOOPA_VELOCITY_X, 0, -KoopaTroopa::KOOPA_VELOCITY_X, 0, 0, NULL, koopaTroopaGoombaSprite);
				koopa->setState(new KoopaNomalState(koopa));
				obManager->addObject(koopa);
			}
			else if (v[3] == 3)
			{
				RedKoopa* vulnerableKoopa =
					new RedKoopa(v[1], v[2], 16, 28, -KoopaTroopa::KOOPA_VELOCITY_X, 0, -KoopaTroopa::KOOPA_VELOCITY_X, 0, 0, NULL, koopaTroopaGoombaSprite);
				vulnerableKoopa->setState(new KoopaVulnerableState(vulnerableKoopa));
				obManager->addObject(vulnerableKoopa);
			}
		}
		else if (v[0] == 13){
			if (v[3] == 1)//Piranha Plant
			{
				PiranhaPlant* piranhaPlant = new PiranhaPlant(v[1], v[2], piranhaSprite, pipeSprite);
				obManager->addObject(piranhaPlant);
			}
			else if (v[3] == 2){//FirePiranha Plant
				FirePiranha* firePiranha = new FirePiranha(v[1], v[2], piranhaSprite, pipeSprite);
				obManager->addObject(firePiranha);
			}
			else if (v[3] == 3){//RedFire Piranha Plant
				RedFirePiranha* redFirePiranha = new RedFirePiranha(v[1], v[2], piranhaSprite, pipe32x40Sprite);
				obManager->addObject(redFirePiranha);
			}
		}
		else if (v[0] == 14){
			GoobaFactory* goombaFactory = new GoobaFactory(v[1], v[2], v[3]);
			obManager->addObject(goombaFactory);
		}
	
		/*PiranhaPlant* piranhaPlant = new PiranhaPlant(1808, 31 + 28, piranhaSprite, pipeSprite);
		FirePiranha* firePiranha = new FirePiranha(1871 + 1, 39 + 24 + FirePiranha::HEIGHT / 2, piranhaSprite, pipeSprite);///x+1 do sai số
		RedFirePiranha* redFirePiranha = new RedFirePiranha(367 + 1, 39 + 24 + RedFirePiranha::HEIGHT / 2, piranhaSprite, pipe32x40Sprite);///x+1 do sai số*/
		


	}
}