#pragma once
#include <windows.h>
struct object
{
	int id;//id
	int kind;//loai
	int x;//vi tri
	int y;
	int w;//chieu
	int h;
	int se; //
};
//su dung list don
struct node
{
	object info;
	node * pnext;
};

struct list
{
	node *phead;
	node *ptail;
};

node* getnode(object data);

void addlist(list &l, object data);

class cliststatic
{

public:
	int n;
	list l;
	cliststatic(void);
	void setobject(object data);
	void setnode(int id, int kind, int x, int y, int w, int h);
	object getobject(int id);
	RECT getRectObject(int id);
	void deleteallobject();
	void deleteObjet(int id);
	~cliststatic(void);
};