#include "ObjectManager.h"

ObjectManager* ObjectManager::sInstance;
ObjectManager::ObjectManager(){
}

ObjectManager* ObjectManager::getInstance(){
	if (sInstance == NULL){
		sInstance = new ObjectManager();
	}
	return sInstance;
}

void ObjectManager::addObject(Object* ob){
	mListObject.push_back(ob);
}

int ObjectManager::removeObject(int position){
	Object* ob;
	try{
		ob = mListObject[position];
	}
	catch (out_of_range exception){
		return 0;
	}
	delete ob;
	mListObject.erase(mListObject.begin() + position);
	return 1;
}
int ObjectManager::removeObject(Object *ob){
	for (int i = 0; i < mListObject.size(); ++i){
		if (mListObject[i] == ob){
			mListObject.erase(mListObject.begin() + i);
			return 1;
		}
	}
	return 0;
}

void ObjectManager::checkCollition(){
	for (int i = 0; i < mListObject.size()-1; ++i){
		for (int j = i + 1; j < mListObject.size(); ++j){
			//if(isCollision(mListObject[i],mlistObject[j])==true) {
			//objecti.onCollition(objectj);
			//objectJ.onCollition(objecti);
		}
	}
}

Mario* ObjectManager::getMario(){
	for (int i = 0; i < mListObject.size(); ++i){
		Object* ob = mListObject[i];
		string obName = ob->getName();

		if (obName == Mario::OBJECT_NAME){
			return (Mario*)ob;
		}
	}
	return NULL;
}