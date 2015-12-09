#include"KoopaTroopa.h"
#include <string>
using namespace std;

KoopaTroopa::KoopaTroopa(int x, int y, int width, int height, float vx, float vy, float vx_last, float ax, float ay, Animation* anim, CSprite * image) 
	:Object(x, y, width, height, vx, vy, vx_last, ax, ay, anim, image){
	mAnimationFactory = new KoopaAnimationFactory(this);
}

const string KoopaTroopa::OBJECT_NAME = "koopa_troopa";
string KoopaTroopa::getName(){
	return OBJECT_NAME;
}
void KoopaTroopa::onCollision(Object* ob){
	mState->onCollision(ob);
}


/////////////////////KoopaTroopaState/////////////////////
string KoopaTroopaState::getName(){
	return "koopa_state";
}

void KoopaTroopaState::onCollision(Object*ob){
	//khong xử lý va chạm, vì đây là trạng thái ảo
}

/////////////////////KoopaNomalState//////////////////

const string KoopaNomalState::STATE_NAME = "koopa_nomal_state";
string KoopaNomalState::getName(){
	return STATE_NAME;
}
void KoopaNomalState::onCollision(Object*ob){
	//xử lý va chạm, nếu chạm gạch thì quay đầu
	//chạm mario từ bên trái,phải hoặc bên dưới thì mario chết
	//chạm mario từ trên thì chuyển sang trạng thái Vulnerable;
}

///////////////////KoopaVulnerableState///////////////

const string KoopaVulnerableState::STATE_NAME = "koopa_vulnerable_state";
string KoopaVulnerableState::getName(){
	return STATE_NAME;
}
void KoopaVulnerableState::onCollision(Object*ob){
	//xử lý va chạm 
	//nếu chạm mario chuyển sang trạng thái bị đá SlidingState
}


/////////////////////////////////////////////////
const string KoopaSlidingState::STATE_NAME = "koopa_sliding_state";
string KoopaSlidingState::getName(){
	return STATE_NAME;
}
void KoopaSlidingState::onCollision(Object*ob){
	//xử lý va chạm 
	//nếu chạm mario từ trái hoặc phải thì mario chết
	//nếu chạm mario từ trên xuống thì dừng lại chuyển sang trạng thái vulnerable
	//nếu chạm gạch vở đc thì gach vở, đổi hướng.
	//nếu chạm kẻ thù (Goomba, koopa..) thì kẻ thù chết.
}

/////////////////////////////KoopaAnimationFactory///////////////
Animation* KoopaAnimationFactory::createAnimation(){
	return 0;
}

KoopaAnimationFactory::KoopaAnimationFactory(KoopaTroopa*koopa){
	mKoopa = koopa;
}