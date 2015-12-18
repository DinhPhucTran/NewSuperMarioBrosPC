#include "ObjectManager.h"
#include "Physics.h"

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
	//delete ob;
	ob = 0;
	mListObject.erase(mListObject.begin() + position);
	return 1;
}
int ObjectManager::removeObject(Object *ob){
	for (int i = 0; i < mListObject.size(); ++i){
		if (mListObject[i] == ob){
			mListObject.erase(mListObject.begin() + i);
			//delete ob;
			ob = 0;
			return 1;
		}
	}
	return 0;
}

void ObjectManager::checkCollition(){
	for (int i = 0; i < mListObject.size()-1; ++i){
		for (int j = i + 1; j < mListObject.size(); ++j){
			Object *ob1, *ob2;
			ob1 = mListObject[i];
			ob2 = mListObject[j];
			int dir = Physics::CollisionStatic(mListObject[i], mListObject[j]);
			if (dir != 0){
				if (ob1)
					ob1->onCollision(ob2, dir);//ob 1 bị đụng trái thì ob2 bị đụng phải, tương tự trên dưới
				if (ob2)
					ob2->onCollision(ob1, -dir);
			}
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

void ObjectManager::render(int vpx,int vpy){
	/*for (int i = 0; i < mListObject.size() ; ++i){
		mListObject[i]->render(vpx,vpy);
	}*/

	for (int i = mListObject.size() - 1; i >= 0; --i){
		mListObject[i]->render(vpx, vpy);
	}
}

void ObjectManager::update(int t){
	for (int i = 0; i < mListObject.size(); ++i){
		mListObject[i]->update(t);
	}
}