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
	if (ob->isStaticObject()){
		mListStaticObject.push_back(ob);
	}
	else{
		mListObject.push_back(ob);
	}
	
}

//int ObjectManager::removeObject(int position){
//	Object* ob;
//	try{
//		ob = mListObject[position];
//	}
//	catch (out_of_range exception){
//		return 0;
//	}
//	//delete ob;
//	ob = 0;
//	mListObject.erase(mListObject.begin() + position);
//	return 1;
//}
int ObjectManager::removeObject(Object *ob){
	for (int i = 0; i < mListObject.size(); ++i){
		if (mListObject[i] == ob){
			//mListObject.erase(mListObject.begin() + i);
			//delete ob;
			mListOfGarbageObject.push_back(ob);
			mListObject[i] = 0;
			return 1;
		}
	}
	for (int i = 0; i < mListStaticObject.size(); ++i){
		if (mListStaticObject[i] == ob){
			//mListStaticObject.erase(mListObject.begin() + i);
			//delete ob;
			mListOfGarbageObject.push_back(ob);
			mListStaticObject[i] = 0;
			return 1;
		}
	}
	return 0;
}

void ObjectManager::checkCollition(){
	//for (int i = 0; i < mListObject.size()-1; ++i){
	//	for (int j = i + 1; j < mListObject.size(); ++j){
	//		Object *ob1, *ob2;
	//		ob1 = mListObject[i];
	//		ob2 = mListObject[j];
	//		int dir = Physics::CollisionStatic(mListObject[i], mListObject[j]);
	//		if (dir != 0){
	//			if (ob1)
	//				ob1->onCollision(ob2, dir);//ob 1 bị đụng trái thì ob2 bị đụng phải, tương tự trên dưới
	//			if (ob2)
	//				ob2->onCollision(ob1, -dir);
	//		}
	//	}
	//}
	
	for (int i = 0; i < mListObject.size(); ++i){
		for (int j = 0; j < mListObject.size(); ++j){
			Object *ob1, *ob2;
			ob1 = mListObject[i];
			ob2 = mListObject[j];
			if (ob1 == 0){//object này đả bị xóa, tiếp tục chạy sẽ gây lỗi
				break;
			}
			else if (ob2 == 0){
				continue;
			}
			int dir = Physics::CollisionStatic(ob1, ob2);
			if (dir != 0){
				if (ob1!=0 && ob2 !=0)
					ob1->onCollision(ob2, dir);//ob 1 bị đụng trái thì ob2 bị đụng phải, tương tự trên dưới
				if (ob2 != 0 && ob1 != 0)
					ob2->onCollision(ob1, -dir);
			}
		}
		//check collision for static object
		for (int k = 0; k < mListStaticObject.size(); ++k){
			Object *ob1, *ob2;
			ob1 = mListObject[i];
			ob2 = mListStaticObject[k];
			if (ob1 == 0){//object này đả bị xóa, tiếp tục chạy sẽ gây lỗi
				break;
			}
			else if (ob2 == 0){
				continue;
			}
			int dir = Physics::CollisionStatic(ob1, ob2);
			if (dir != 0){
				if (ob1!=0 && ob2!=0){
					ob1->onCollision(ob2, dir);
				}
				if (ob2!=0 && ob1!=0){
					ob2->onCollision(ob1, -dir);
				}
			}
		}
	}
	refeshList();
}

Mario* ObjectManager::getMario(){
	for (int i = 0; i < mListObject.size(); ++i){
		Object* ob = mListObject[i];
		if (ob == NULL){
			return NULL;
		}
		string obName = ob->getName();

		if (obName == Mario::OBJECT_NAME){
			return (Mario*)ob;
		}
	}
	return NULL;
}

void ObjectManager::render(int vpx,int vpy){

	refeshList();

	for (vector<Object*>::iterator itr = mListStaticObject.begin(); itr != mListStaticObject.end(); itr++){
		Object* ob = (*itr);
		if (ob == 0){
			continue;
		}else 
			ob->render(vpx, vpy);
	}
	for (vector<Object*>::iterator itr = mListObject.begin(); itr != mListObject.end(); itr++){
		Object* ob = (*itr);
		if (ob == 0){
			continue;
		}
		else
			ob->render(vpx, vpy);
	}
}

void ObjectManager::update(int t){
	for (int i = 0; i < mListObject.size(); ++i){
		Object* ob = mListObject[i];
		if (ob != 0){
			Mario* mario = getMario();
			if (mario != NULL){
				if (abs(ob->x - mario->x) < 450)//chỉ update khi mario tới gần
					ob->update(t);
			}
			else ob->update(t);
				
		}
			
	}
	for (int i = 0; i < mListStaticObject.size(); ++i){
		Object* ob = mListStaticObject[i];
		if (ob != 0){
			Mario* mario = getMario();
			if (mario != NULL){
				if (abs(ob->x - mario->x) < 450)//chỉ update khi mario tới gần
					ob->update(t);
			}
			else ob->update(t);
		}
	}
}
void ObjectManager::refeshList(){
	for (vector<Object*>::iterator itr = mListOfGarbageObject.begin(); itr != mListOfGarbageObject.end();itr++){
 		Object* ob = (*itr);
		//delete ob;
	}
	mListOfGarbageObject.clear();



	for (int i = 0; i < mListObject.size(); ++i){
		Object* ob = mListObject[i];
		if (ob == 0){
			mListObject.erase(mListObject.begin() + i);
		}
	}
	for (int i = 0; i < mListStaticObject.size(); ++i){
		Object* ob = mListStaticObject[i];
		if (ob == 0){
			mListStaticObject.erase(mListStaticObject.begin() + i);
		}
	}

	/*for (vector<Object*>::iterator itr = mListObject.begin(); itr != mListObject.end(); itr++){
		Object* ob = (*itr);
		if (ob == 0){
			mListObject.erase(itr);
		}
	}
	for (vector<Object*>::iterator itr = mListStaticObject.begin(); itr != mListStaticObject.end(); itr++){
		Object* ob = (*itr);
		if (ob == 0){
			mListObject.erase(itr);
		}
	}*/
}

vector<Object*> ObjectManager::getStaticObjectList(){
	return mListStaticObject;
}