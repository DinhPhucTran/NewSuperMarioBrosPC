#include"Physics.h"


bool Physics::ContainsPoint(Object *o, int x, int y)
{
	return (x >= (o->x - (o->width / 2)) && y <= (o->y + (o->height / 2)) && x <= (o->x + (o->width / 2)) && y >= (o->y - (o->height / 2)));
}

const int Physics::COLLIDED_FROM_BOTTOM = -1;
const int Physics::COLLIDED_FROM_TOP = 1;
const int Physics::COLLIDED_FROM_LEFT = -2;
const int Physics::COLLIDED_FROM_RIGHT = 2;
int Physics::CollisionStatic(Object *o1, Object *o2)
{
	//1: đụng đầu o1
	//2: đụng bên phải o1
	//-1: dưới o1
	//-2: bên trái o1
	//0: không đụng độ
	if (o1->vy < 0)
	{
		if (ContainsPoint(o2, o1->x, o1->bottom()))
		{
			//o1->vy = 0;
			//o1->y = o2->top() + o1->height / 2;
			return -1;
		}
	}

	if (o1->vy > 0)
	{
		if (ContainsPoint(o2, o1->x, o1->top()))
		{
			//o1->vy = -o1->vy;
			return 1;
		}
	}

	if (ContainsPoint(o2, o1->right(), o1->y))
	{
		//o1->x = o2->left() - o1->width / 2;
		return 2;
	}

	if (ContainsPoint(o2, o1->left(), o1->y))
	{
		//o1->x = o2->right() + o1->width / 2;
		return -2;
	}
	return 0;
}