#ifndef _PHYSICS_H
#define _PHYSICS_H
#include "object.h"
class Physics
{
public:
	static const int COLLIDED_FROM_TOP;
	static const int COLLIDED_FROM_BOTTOM;
	static const int COLLIDED_FROM_LEFT;
	static const int COLLIDED_FROM_RIGHT;
	static bool ContainsPoint(Object *o, int x, int y);
	static int CollisionStatic(Object *o1, Object *o2);
};
#endif 