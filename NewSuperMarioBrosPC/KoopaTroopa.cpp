

#include"RedKoopa.h"
#include"BrickGround.h"
#include"Physics.h"
#include <string>
#include"Qbrick.h"
#include"MarioState.h"
#include "ObjectManager.h"
using namespace std;

KoopaTroopa::KoopaTroopa(int x, int y, int width, int height, float vx, float vy, float vx_last, float ax, float ay, Animation* anim, CSprite * image) 
	:Object(x, y, width, height, vx, vy, vx_last, ax, ay, anim, image){
	if (mState == NULL){
		mState = new KoopaNomalState(this);
	}
	if(mAnimationFactory==NULL)
		mAnimationFactory = new KoopaAnimationFactory(this);
	if(mAnim==NULL)
		mAnim = mAnimationFactory->createAnimation();
	
}
const int KoopaTroopa::KOOPA_WIDTH = 16;
const int KoopaTroopa::KOOPA_HEIGHT = 27;
const int KoopaTroopa::KOOPA_VULNERABLE_HEIGHT = 16;
const int KoopaTroopa::NORMAL_ANIMATION_DELAY = Animation::FRAME_DELAY_DEFAULT;
const int KoopaTroopa::SLIDING_ANIMATION_DELAY = 1;
const float KoopaTroopa::KOOPA_VELOCITY_X = 0.1f;
const float KoopaTroopa::KOOPA_SLIDING_SPEED_X = 0.35f;
const float KoopaTroopa::KOOPA_VULNERABLE_SPEED_X = 0;
const int KoopaTroopa::WAKE_UP_FROM_VULNERABLE_TIME = 10000;
const string KoopaTroopa::OBJECT_NAME = "koopa_troopa";
string KoopaTroopa::getName(){
	return OBJECT_NAME;
}
void KoopaTroopa::onCollision(Object* ob,int dir){
	mState->onCollision(ob,dir);
}
KoopaTroopaState* KoopaTroopa::getState(){
	return mState;
}
void KoopaTroopa::setState(KoopaTroopaState* state){
	if (state != NULL){
		delete mState;// giải phóng mState hiện tại
		mState = state;
	}
	this->width = mState->getWidth();//thay đối lại kích thước của Koopa ứng với trạng thái
	this->height = mState->getHeight();
	this->mAnim->frameDelay = mState->getAnimationDelay();
	if (vx_last < 0){
		this->vx = -mState->getSpeed();
		vx_last = vx;
	}
	else
	{
		this->vx = mState->getSpeed();;
		vx_last = vx;
	}
}

void KoopaTroopa::setAnimationFactory(AnimationFactory* animFactory){
	mAnimationFactory = animFactory;
}

void KoopaTroopa::render(int vpx, int vpy){
	mSprite->Render(mAnimationFactory->createAnimation(), x, y, vpx, vpy);
}


/////////////////////KoopaTroopaState/////////////////////
string KoopaTroopaState::getName(){
	return "koopa_state";
}

void KoopaTroopaState::onCollision(Object*ob,int dir){
	//Tất cả các lơp kế thừa phải gọi hàm này nếu override
	//chứa tất cả các loại va chạm chung mà mọi trạng thái đều xử lý như nhau

	
}
KoopaTroopaState::KoopaTroopaState(KoopaTroopa* koopa){
	mKoopa = koopa;
	
}

float KoopaTroopaState::getSpeed(){
	return KoopaTroopa::KOOPA_VELOCITY_X;
}
int KoopaTroopaState::getHeight(){
	return KoopaTroopa::KOOPA_HEIGHT;
}
int KoopaTroopaState::getWidth(){
	return KoopaTroopa::KOOPA_WIDTH;
}
int KoopaTroopaState::getAnimationDelay(){
	return KoopaTroopa::NORMAL_ANIMATION_DELAY;
}

/////////////////////KoopaNomalState//////////////////

const string KoopaNomalState::STATE_NAME = "koopa_nomal_state";
string KoopaNomalState::getName(){
	return STATE_NAME;
}
void KoopaNomalState::onCollision(Object*ob, int dir){
	//xử lý va chạm, nếu chạm gạch thì quay đầu
	//chạm mario từ bên trái,phải hoặc bên dưới thì mario chết
	//chạm mario từ trên thì chuyển sang trạng thái Vulnerable;
	KoopaTroopaState::onCollision(ob, dir);
	string objName = ob->getName();
	if (objName == BrickGround::OBJECT_NAME || objName == Pipe::OBJECT_NAME){
		if (dir == Physics::COLLIDED_FROM_LEFT){
			if (mKoopa->vx_last < 0){
				mKoopa->vx = KoopaTroopa::KOOPA_VELOCITY_X;
				mKoopa->vx_last = mKoopa->vx;
			}
		}
		else if (dir == Physics::COLLIDED_FROM_RIGHT){
			if (mKoopa->vx_last > 0){
				mKoopa->vx = -KoopaTroopa::KOOPA_VELOCITY_X;
				mKoopa->vx_last = mKoopa->vx;
			}
		}
		else if (dir == Physics::COLLIDED_FROM_BOTTOM){
			mKoopa->vy = 0;
			mKoopa->ay = 0;
			mKoopa->y = ob->top() + mKoopa->height / 2;// chỉnh lại tọa độ y
		}
		else if (dir == Physics::COLLIDED_FROM_TOP){
			if (mKoopa->vy > 0){
				mKoopa->vy = -0.000001;//gần bằng 0, không đc =0 sẽ gây ra lổi
				mKoopa->ay = 0;
			}
		}
	}
	else if (objName == Mario::OBJECT_NAME)
	{
		//Nếu mario invicible thì ko xử lý tiếp nữa
		Mario* mario = (Mario*)ob;
		string stateName = (mario->getState())->getName();
		if (stateName == MarioStateInvincible::STATE_NAME){
			return;
		}

		//chạm trái phải dưới -> mario chết
		//trên thì chuyển sang vulnerable state;
		else if (dir == Physics::COLLIDED_FROM_TOP)
		{
			if (mKoopa->vy > 0){
				mKoopa->vy = -0.000001;//gần bằng 0, không đc =0 sẽ gây ra lổi
				mKoopa->ay = 0;
			}
			mKoopa->vx = 0;
			mKoopa->ax = 0;
			mKoopa->setState(new KoopaVulnerableState(mKoopa));
		}
	}
	//va chạm với rùa đang slide
	if (objName == RedKoopa::OBJECT_NAME || objName == KoopaTroopa::OBJECT_NAME){
		string stateName = ((KoopaTroopa*)ob)->getState()->getName();
		if (stateName == KoopaSlidingState::STATE_NAME){
			if (dir == Physics::COLLIDED_FROM_LEFT || dir == Physics::COLLIDED_FROM_RIGHT){
				mKoopa->die();
			}
		}
	}
}
KoopaNomalState::KoopaNomalState(KoopaTroopa* koopa)
	:KoopaTroopaState(koopa){
}

///////////////////KoopaVulnerableState///////////////
KoopaVulnerableState::KoopaVulnerableState(KoopaTroopa* koopa)
	: KoopaTroopaState(koopa){
	mLastTime = GetTickCount();
}


const string KoopaVulnerableState::STATE_NAME = "koopa_vulnerable_state";
string KoopaVulnerableState::getName(){
	return STATE_NAME;
}
int KoopaVulnerableState::getHeight(){
	return KoopaTroopa::KOOPA_VULNERABLE_HEIGHT;
}
float KoopaVulnerableState::getSpeed(){
	return KoopaTroopa::KOOPA_VULNERABLE_SPEED_X;
}

void KoopaVulnerableState::onCollision(Object*ob, int dir){
	//xử lý va chạm 
	//nếu chạm mario chuyển sang trạng thái bị đá SlidingState
	//Va chạm dưới với gạch, 
	//va chạm trên dưới trái phải với mario;
	DWORD now = GetTickCount();
	if (now - mLastTime >= 10000){
		Mario* mario = ObjectManager::getInstance()->getMario();
		if (mario->x > mKoopa->x){//khi wake up thì rùa đi hướng về phía mario;
			mKoopa->vx = KoopaTroopa::KOOPA_VELOCITY_X;
			mKoopa->vx_last = mKoopa->vx;
		}
		else
		{
			mKoopa->vx = -KoopaTroopa::KOOPA_VELOCITY_X;
			mKoopa->vx_last = mKoopa->vx;
		}
		mKoopa->setState(new KoopaNomalState(mKoopa));
		return;
	}

	KoopaTroopaState::onCollision(ob, dir);
	string objName = ob->getName();
	if (objName == BrickGround::OBJECT_NAME){
		if (dir == Physics::COLLIDED_FROM_BOTTOM){
			mKoopa->vy = 0;
			mKoopa->ay = 0;
			mKoopa->y = ob->top() + mKoopa->height / 2;// chỉnh lại tọa độ y
		}
		else if (dir == Physics::COLLIDED_FROM_TOP){
			if (mKoopa->vy > 0){
				mKoopa->vy = -0.000001;//gần bằng 0, không đc =0 sẽ gây ra lổi
				mKoopa->ay = 0;
			}
		}
	}
	//xử lý va chạm vs Mario
	if (ob->getName() == Mario::OBJECT_NAME){
		//Nếu mario invicible thì ko xử lý tiếp nữa
		Mario* mario = (Mario*)ob;
		string stateName = (mario->getState())->getName();
		if (stateName == MarioStateInvincible::STATE_NAME){
			return;
		}
		else if (mario->isBButtonPressed){//nếu B pressed thì mario cầm rùa chứ ko đá rùa
			//xử lý trường hợp mario cầm rùa
			mKoopa->y = mario->y;
			if (mario->vx_last > 0){
				mKoopa->x = mario->right();
			}
			else{
				mKoopa->x = mario->left();
			}

		}
		else if (dir == Physics::COLLIDED_FROM_TOP||dir==Physics::COLLIDED_FROM_BOTTOM){
			if (ob->x >= mKoopa->x){
				//slide qua trái
				ob->y = mKoopa->top() + ob->height / 2 + 2;
				mKoopa->x = ob->left() - mKoopa->width / 2 - 2;
				mKoopa->vx = -KoopaTroopa::KOOPA_SLIDING_SPEED_X;
				mKoopa->vx_last = mKoopa->vx;
				mKoopa->setState(new KoopaSlidingState(mKoopa));
			}
			else{
				//slide qua phải
				ob->y = mKoopa->top() +ob->height/2 + 2;
				mKoopa->x = ob->right() + mKoopa->width / 2 + 2;
				mKoopa->vx = KoopaTroopa::KOOPA_SLIDING_SPEED_X;
				mKoopa->vx_last = mKoopa->vx;
				mKoopa->setState(new KoopaSlidingState(mKoopa));
			}
		}
		else if (dir == Physics::COLLIDED_FROM_LEFT){
			mKoopa->x = ob->right() + mKoopa->width / 2+2;
			mKoopa->vx = KoopaTroopa::KOOPA_SLIDING_SPEED_X;
			mKoopa->vx_last = mKoopa->vx;
			mKoopa->setState(new KoopaSlidingState(mKoopa));
		}
		else if (dir == Physics::COLLIDED_FROM_RIGHT){
			mKoopa->x = ob->left() - mKoopa->width / 2 - 2;
			mKoopa->vx = -KoopaTroopa::KOOPA_SLIDING_SPEED_X;
			mKoopa->vx_last = mKoopa->vx;
			mKoopa->setState(new KoopaSlidingState(mKoopa));
		}
	}
	//va chạm với rùa đang slide
	if (objName == RedKoopa::OBJECT_NAME || objName == KoopaTroopa::OBJECT_NAME){
		string stateName = ((KoopaTroopa*)ob)->getState()->getName();
		if (stateName == KoopaSlidingState::STATE_NAME){
			if (dir == Physics::COLLIDED_FROM_LEFT || dir == Physics::COLLIDED_FROM_RIGHT){
				mKoopa->die();
			}
		}
	}
}



/////////////////////////////////////////////////

const string KoopaSlidingState::STATE_NAME = "koopa_sliding_state";
string KoopaSlidingState::getName(){
	return STATE_NAME;
}
void KoopaSlidingState::onCollision(Object*ob,int dir){
	//xử lý va chạm 
	//nếu chạm mario từ trái hoặc phải thì mario chết
	//nếu chạm mario từ trên xuống thì dừng lại chuyển sang trạng thái vulnerable
	//nếu chạm gạch vở đc thì gach vở, đổi hướng.
	//nếu chạm kẻ thù (Goomba, koopa..) thì kẻ thù chết.

	KoopaTroopaState::onCollision(ob, dir);
	string objName = ob->getName();
	if (ob->getName() == BrickGround::OBJECT_NAME||ob->getName()==Pipe::OBJECT_NAME){
		if (dir == Physics::COLLIDED_FROM_LEFT){
			if (mKoopa->vx_last < 0){
				mKoopa->vx = KoopaTroopa::KOOPA_SLIDING_SPEED_X;
				mKoopa->vx_last = mKoopa->vx;
			}
		}
		else if (dir == Physics::COLLIDED_FROM_RIGHT){
			if (mKoopa->vx_last > 0){
				mKoopa->vx = -KoopaTroopa::KOOPA_SLIDING_SPEED_X;
				mKoopa->vx_last = mKoopa->vx;
			}
		}
		else if (dir == Physics::COLLIDED_FROM_BOTTOM){
			mKoopa->vy = 0;
			mKoopa->ay = 0;
			mKoopa->y = ob->top() + mKoopa->height / 2;// chỉnh lại tọa độ y
		}
		else if (dir == Physics::COLLIDED_FROM_TOP){
			if (mKoopa->vy > 0){
				mKoopa->vy = -0.000001;//gần bằng 0, không đc =0 sẽ gây ra lổi
				mKoopa->ay = 0;
			}
		}
	}
	//xử lý với mario
	if (objName == Mario::OBJECT_NAME){
		//Nếu mario invicible thì ko xử lý tiếp nữa
		Mario* mario = (Mario*)ob;
		string stateName = (mario->getState())->getName();
		if (stateName == MarioStateInvincible::STATE_NAME){
			return;
		}
		else if (dir == Physics::COLLIDED_FROM_TOP){
			mKoopa->vx = 0;
			mKoopa->ax = 0;
			mKoopa->setState(new KoopaVulnerableState(mKoopa));
		}
	}
	
	if (objName == QBrick::OBJECT_NAME){
		QBrick* qBrick = (QBrick*)ob;
		if (dir == Physics::COLLIDED_FROM_LEFT || dir == Physics::COLLIDED_FROM_RIGHT){
			qBrick->revealHiddenObject();
		}
	}
	
}
KoopaSlidingState::KoopaSlidingState(KoopaTroopa* koopa) 
	:KoopaTroopaState(koopa){

}
int KoopaSlidingState::getAnimationDelay(){
	return KoopaTroopa::SLIDING_ANIMATION_DELAY;
}
int KoopaSlidingState::getHeight(){
	return KoopaTroopa::KOOPA_VULNERABLE_HEIGHT;
}
float KoopaSlidingState::getSpeed(){
	return KoopaTroopa::KOOPA_SLIDING_SPEED_X;
}

/////////////////////////////KoopaAnimationFactory///////////////

Animation* KoopaAnimationFactory::createAnimation(){
	string stateName = mKoopa->getState()->getName();
	Animation* result;
	if (stateName == KoopaVulnerableState::STATE_NAME){
		result = mKoopaVulnerableAnim;
	}
	else if (stateName == KoopaSlidingState::STATE_NAME){
		result = mKoopaSlidingAnim;
	}
	else {///normal state
		if (mKoopa->vx_last < 0){
			result = mKoopaLeftWalkAnim;
		}
		else{
			result = mKoopaRightWalkAnim;
		}
	}
	result->Update();
	return result;
}

KoopaAnimationFactory::KoopaAnimationFactory(KoopaTroopa*koopa){
	mKoopa = koopa;
}
KoopaAnimationFactory::~KoopaAnimationFactory(){
	/*delete mKoopaLeftWalkAnim;
	delete mKoopaRightWalkAnim;
	delete mKoopaSlidingAnim;
	delete mKoopaVulnerableAnim;*/
}