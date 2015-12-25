#include "cliststatic.h"
#include <Windows.h>
class QuadNode
{
public:
	cliststatic * clistobject;
	RECT *Rect;
	QuadNode *LT, *RT, *LB, *RB;
	QuadNode();
	QuadNode(int left, int top, int width, int height);
	~QuadNode();
};
class QuadTree
{
public:
	QuadNode *Root;
	int MapWidth, MapHeight;
	int Count;
	QuadTree(int w, int h);
	~QuadTree();
	int CheckRECT(RECT *rootRECT, RECT * Rectdata);
	void Add(QuadNode *root, object data);
	bool RECTInRECT(RECT r, RECT rect);
	void getListObject(QuadNode *root, RECT Screen, cliststatic * listObject);
	void getAllObject(QuadNode *root, cliststatic * listObject);
	void deleteQuadTree(QuadNode *root);
	void CheckCollision(QuadNode *root, RECT Screen, RECT rectMario, int *result, RECT * rectOb);
	void CollisionUp(QuadNode *root, RECT Screen, RECT rectMario, int *result, RECT * rectOb, bool isBreak);
	void CheckCollisionCoin(QuadNode *root, RECT Screen, RECT rectMario, int *result);
};