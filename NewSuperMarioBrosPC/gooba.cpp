#include"gooba.h"
#include <string>


using namespace std;


const float Gooba::SPEED_X = 0.13f;
Gooba::Gooba(int x, int y, int width, int height, float vx, float vy, float vx_last, float ax, float ay, Animation* anim, CSprite * image)
:Object(x, y, width, height, vx, vy, vx_last, ax, ay, anim, image){
	mAnimationFactory = new GoobaAnimationFactory(this);
	mState = new GoobaNomalState(this);
}

const string Gooba::OBJECT_NAME = "gooba";
string Gooba::getName(){
	return OBJECT_NAME;
}
void Gooba::onCollision(Object* ob,int dir){
	mState->onCollision(ob,dir);
}
GoobaState* Gooba::getState(){
	return mState;
}

void Gooba::setAnimationFactory(AnimationFactory* animFactory){
	mAnimationFactory = animFactory;
}

void Gooba::render(int vpx, int vpy){
	mSprite->Render(mAnimationFactory->createAnimation(), x, y, vpx, vpy);
}


/////////////////////KoopaTroopaState/////////////////////
string GoobaState::getName(){
	return "gooba_state";
}
GoobaState::GoobaState(Gooba* gooba){
	mGooba = gooba;
}
void GoobaState::onCollision(Object*ob,int direction){
	//khong xử lý va chạm, vì đây là trạng thái ảo
}

/////////////////////KoopaNomalState//////////////////

const string GoobaNomalState::STATE_NAME = "gooba_nomal_state";
string GoobaNomalState::getName(){
	return STATE_NAME;
}
void GoobaNomalState::onCollision(Object*ob,int dir){
	//xử lý va chạm, nếu chạm gạch thì quay đầu
	//chạm mario từ bên trái,phải hoặc bên dưới thì mario chết
	//chạm mario từ trên thì chuyển sang trạng thái Vulnerable;
	if (ob->getName() == BrickGround::OBJECT_NAME){
		if (dir == Physics::COLLIDED_FROM_LEFT){
			if (mGooba->vx_last < 0){
				mGooba->vx = Gooba::SPEED_X;
				mGooba->vx_last = mGooba->vx;
			}
			return;//tối ưu hóa;
		}
		else if (dir == Physics::COLLIDED_FROM_RIGHT){
			if (mGooba->vx_last > 0){
				mGooba->vx = -Gooba::SPEED_X;
				mGooba->vx_last = mGooba->vx;
			}
			return; //tối ưu hóa
		}
		else if (dir == Physics::COLLIDED_FROM_BOTTOM){
			mGooba->vy = 0;
			mGooba->ay = 0;
			mGooba->y = ob->top() + mGooba->height / 2;// chỉnh lại tọa độ y
			return;//dừng được rồi khoongn cần chạy thêm nữa
		}
		else if (dir == Physics::COLLIDED_FROM_TOP){
			if (mGooba->vy > 0){
				mGooba->vy = -0.000001;//gần bằng 0, không đc =0 sẽ gây ra lổi
				mGooba->ay = 0;
			}
			return;//tối ưu hóa code
		}
	}
}
GoobaNomalState::GoobaNomalState(Gooba* gooba)
	:GoobaState(gooba){

}
///////////////////KoopaVulnerableState///////////////

//const string KoopaVulnerableState::STATE_NAME = "koopa_vulnerable_state";
//string KoopaVulnerableState::getName(){
//	return STATE_NAME;
//}
//void KoopaVulnerableState::onCollision(Object*ob){
//	//xử lý va chạm 
//	//nếu chạm mario chuyển sang trạng thái bị đá SlidingState
//}


/////////////////////////////////////////////////
//const string KoopaSlidingState::STATE_NAME = "koopa_sliding_state";
//string KoopaSlidingState::getName(){
//	return STATE_NAME;
//}
//void KoopaSlidingState::onCollision(Object*ob){
//	//xử lý va chạm 
//	//nếu chạm mario từ trái hoặc phải thì mario chết
//	//nếu chạm mario từ trên xuống thì dừng lại chuyển sang trạng thái vulnerable
//	//nếu chạm gạch vở đc thì gach vở, đổi hướng.
//	//nếu chạm kẻ thù (Goomba, koopa..) thì kẻ thù chết.
//}

/////////////////////////////KoopaAnimationFactory///////////////
Animation* GoobaAnimationFactory::createAnimation(){
	string stateName = mGooba->getState()->getName();
	Animation* result;

	if (mGooba->vx_last < 0){
		result = mGoobaLeftWalkAnim;
	}
	else{
		result = mGoobaRightWalkAnim;
	}
	result->Update();
	return result;
}

GoobaAnimationFactory::GoobaAnimationFactory(Gooba*gooba){
	mGooba = gooba;
}