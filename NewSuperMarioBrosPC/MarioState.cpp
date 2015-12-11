#include "MarioState.h"
#include "MarioObject.h"

#include <string>
using namespace std;

//================STATE====================
void MarioState::onAPress(){
	//do nothing
}
void MarioState::onBPress(){
	//do nothing
}
void MarioState::onCollision(Object* ob,int dir){
	// do nothing 
}
string MarioState::getName(){
	return "mario_state";
}

//================STATE SMALL==============
const string MarioStateSmall::STATE_NAME = "mario_state_small";
string MarioStateSmall::getName(){
	return STATE_NAME;
}

MarioStateSmall::MarioStateSmall(Mario* ob){//contructor
	MarioStateSmall::mMario = ob;
}


void MarioStateSmall::onAPress(){
	//jump
}
void MarioStateSmall::onBPress(){
	//do nothing
}
void MarioStateSmall::onCollision(Object* ob,int dir){
	//xử lý va chạm khi mario ở trạng thái Small
}
//==================SATE_LARGE==============
const string MarioStateLarge::STATE_NAME = "mario_state_large";
string MarioStateLarge::getName(){
	return STATE_NAME;
}
MarioStateLarge::MarioStateLarge(Mario* ob){
	MarioStateLarge::mMario = ob;
}
void MarioStateLarge::onAPress(){
	//jump;
}
void MarioStateLarge::onBPress(){
	//do nothing;
}
void MarioStateLarge::onCollision(Object* ob,int dir){
	//xử lý va chạm trong trường hợp mario Lớn
}

//==================SATE_RACON==============
const string MarioStateRaccoon::STATE_NAME = "mario_state_raccoon";
string MarioStateRaccoon::getName(){
	return STATE_NAME;
}
MarioStateRaccoon::MarioStateRaccoon(Mario* ob){
	MarioStateRaccoon::mMario = ob;
}
void MarioStateRaccoon::onAPress(){
	//jump;
}
void MarioStateRaccoon::onBPress(){
	//do nothing;
}
void MarioStateRaccoon::onCollision(Object* ob,int dir){
	//xử lý va chạm trong trường hợp mario Lớn
}

