#ifndef __OBJECT_MANAGER_H__
#define __OBJECT_MANAGER_H__
#include "MarioObject.h"
#include<exception>
#include <vector>
using namespace std;

class ObjectManager
{
private:
	vector<Object*> mListObject;
	ObjectManager();
	static ObjectManager* sInstance;
public:
	static ObjectManager* getInstance();
	void addObject(Object*ob);
	int removeObject(Object* ob);
	int removeObject(int position);
	void checkCollition();
	Mario* getMario();


};

#endif