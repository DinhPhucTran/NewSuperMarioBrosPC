#include "cliststatic.h"

//get node
node* getnode(object data)//lay thong tin cho node (data-pointer)
{
	node*p;
	p = new node;

	if (p == NULL)
	{
		exit(1);
	}
	p->info = data;
	p->pnext = NULL;
	return p;

}

//add dau
void addlist(list &l, object data)
{
	node * new_ele = getnode(data);
	if (l.phead == NULL)
	{
		l.phead = new_ele;
		l.ptail = l.phead;
	}
	else
	{
		new_ele->pnext = l.phead;
		l.phead = new_ele;
	}

}

//khoi tao
cliststatic::cliststatic(void)
{
	n = 0;
	l.phead = NULL;
	l.ptail = NULL;

}

cliststatic::~cliststatic(void)
{
}
//khoi tao cho node ma khong can thong qua data 
void cliststatic::setnode(int id, int kind, int x, int y, int w, int h)
{
	object data;
	data.kind = kind;
	data.x = x;
	data.y = y;
	data.h = h;
	data.id = id;
	data.w = w;
	data.h = h;

	addlist(l, data);
	n++;



}
//add dau vao 1 node co data la:
void cliststatic::setobject(object data)
{
	addlist(l, data);
	n++;
}
//lay ra object co id duoc chon
object cliststatic::getobject(int id)
{

	int i = 0;
	node * p = l.phead;
	while (p != NULL)
	{
		i++;
		if (i == id)
		{
			break;
		}
		p = p->pnext;
	}
	return p->info;


}
//delete tat ca list
void cliststatic::deleteallobject()
{

	node * p;
	while (l.phead != NULL)
	{
		p = l.phead;
		l.phead = p->pnext;
		delete p;
	}
	l.ptail = NULL;
	n = 0;

}
//return ra hinh chu nhat cua doi tuong duoc chi den.
RECT cliststatic::getRectObject(int id)
{
	object ob = getobject(id);
	RECT rect;
	rect.top = ob.y;
	rect.left = ob.x;
	rect.bottom = rect.top + ob.h;
	rect.right = rect.left + ob.w;

	return rect;

}

void cliststatic::deleteObjet(int id)
{
	int i = 0;

	node *p = l.phead;
	node *q = NULL;
	while (p != NULL)
	{
		i++;
		if (i == id)
			break;//tim thay
		q = p; p = p->pnext;
	}
	if (p == NULL)
		return;
	if (q != NULL)
	{
		if (p == l.ptail)
			l.ptail = q;
		q->pnext = p->pnext;
		delete p;
	}
	else
	{
		l.phead = p->pnext;
		if (l.phead == NULL)
			l.ptail = NULL;
	}
	n--;

}