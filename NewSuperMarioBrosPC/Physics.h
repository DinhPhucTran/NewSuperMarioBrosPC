#ifndef _PHYSICS_H
#define _PHYSICS_H
#include "object.h"
class Physics
{
public:
	static bool ContainsPoint(Object *o, int x, int y);
	static int CollisionStatic(Object *o1, Object *o2);
};
#endif 