﻿#ifndef __OBJECT_MANAGER_H__
#define __OBJECT_MANAGER_H__
#include "MarioObject.h"
#include<exception>
#include <vector>
using namespace std;

class ObjectManager
{
private:
	vector<Object*> mListStaticObject;
	vector<Object*>mListObject;
	vector<Object*>mListOfGarbageObject;
	ObjectManager();
	static ObjectManager* sInstance;
public:
	static ObjectManager* getInstance();
	void addObject(Object*ob);
	int removeObject(Object* ob);//đánh dấu ob thành NULL
	void removeAllObject();
	//int removeObject(int position);
	void checkCollition();
	Mario* getMario();
	void update(int t);
	void render(int vpx, int vpy);
	void refeshList();//xóa Null pointer khỏi danh sách và giải phóng vùng nhớ
	vector<Object*> getStaticObjectList();
};

#endif