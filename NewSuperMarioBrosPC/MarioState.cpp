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
void MarioState::onCollision(Object* ob){
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
void MarioStateSmall::onCollision(Object* ob){
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
void MarioStateLarge::onCollision(Object* ob){
	//xử lý va chạm trong trường hợp mario Lớn
}

//==================SATE_RACON==============
const string MarioStateRacon::STATE_NAME = "mario_state_racon";
string MarioStateRacon::getName(){
	return STATE_NAME;
}
MarioStateRacon::MarioStateRacon(Mario* ob){
	MarioStateRacon::mMario = ob;
}
void MarioStateRacon::onAPress(){
	//jump;
}
void MarioStateRacon::onBPress(){
	//do nothing;
}
void MarioStateRacon::onCollision(Object* ob){
	//xử lý va chạm trong trường hợp mario Lớn
}

