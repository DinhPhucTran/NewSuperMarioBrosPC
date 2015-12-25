#include "QuadTree.h"
QuadNode::QuadNode()
{
	Rect = NULL;
	clistobject = NULL;
	LT = LB = RB = RT = NULL;
}
QuadNode::QuadNode(int left, int top, int width, int height)
{
	Rect = new RECT();
	Rect->top = top;
	Rect->left = left;
	Rect->bottom = Rect->top + height;
	Rect->right = Rect->left + width;
	clistobject = new cliststatic();
	LT = LB = RB = RT = NULL;
}
QuadNode::~QuadNode()
{
	delete Rect;
	delete RT;
	delete RB;
	delete LB;
	delete LT;
	delete clistobject;
}
QuadTree::QuadTree(int w, int h)
{
	MapWidth = w;
	MapHeight = h;
	Root = new QuadNode(0, 0, MapWidth, MapHeight);
	Count = 0;
}
QuadTree::~QuadTree()
{
	delete Root;
}
int QuadTree::CheckRECT(RECT *rootRECT, RECT * Rectdata)
{
	int result = 0;//Add binh thuong
	int rw = Rectdata->right - Rectdata->left;//chieu rong cua object
	int rh = Rectdata->bottom - Rectdata->top;// chieu cao cua object

	int w = rootRECT->right - rootRECT->left;//chieu rong cua root
	int h = rootRECT->bottom - rootRECT->top;//chieu cao cua root
	//2 duong thang chia rootRect thanh 4 phan bang nhau
	int x = (rootRECT->right + rootRECT->left) / 2;
	int y = (rootRECT->bottom + rootRECT->top) / 2;

	if ((rw*rh>w*h / 4) || (x>Rectdata->left&&x <= Rectdata->right)
		|| (y>Rectdata->top&&y <= Rectdata->bottom))
		result = 0;//add vao ngay phan cua root do
	else
	{
		if (Rectdata->left >= rootRECT->left&&Rectdata->left<x
			&&Rectdata->top >= rootRECT->top&&Rectdata->top<y)
			result = 1;//Add vao goc LT
		else if (Rectdata->left >= x&&Rectdata->left<rootRECT->right
			&&Rectdata->top >= rootRECT->top&&Rectdata->top<y)
			result = 2;//Add vao goc RT
		else if (Rectdata->left >= rootRECT->left&&Rectdata->left<x
			&&Rectdata->top >= y&&Rectdata->top<rootRECT->bottom)
			result = 3;//add vao goc LB
		else
			result = 4;//add vao goc RB
	}
	return result;
}
void QuadTree::Add(QuadNode *root, object data)
{
	RECT *rect = new RECT();
	rect->top = data.y;
	rect->left = data.x;
	rect->right = data.x + data.w;
	rect->bottom = data.y + data.h;
	if (root != NULL)
	{
		int result = CheckRECT(root->Rect, rect);
		if (result == 0)//add vao ngay tai vi tri goc do
		{
			root->clistobject->setobject(data);
			Count++;
		}
		else
		{
			int w = root->Rect->right - root->Rect->left;
			int h = root->Rect->bottom - root->Rect->top;
			if (w / 2>5 && h / 2>5)
			{
				int x = (root->Rect->right + root->Rect->left) / 2;//duong trung binh x
				int y = (root->Rect->bottom + root->Rect->top) / 2;
				switch (result)
				{
				case 1: //add vao goc LT
					if (root->LT == NULL)
						root->LT = new QuadNode(root->Rect->left,
						root->Rect->top,
						w / 2, h / 2);
					Add(root->LT, data);
					break;
				case 2://add vao goc RT
					if (root->RT == NULL)
						root->RT = new QuadNode(x, root->Rect->top, w / 2, h / 2);
					Add(root->RT, data);
					break;
				case 3://add vao goc LB
					if (root->LB == NULL)
						root->LB = new QuadNode(root->Rect->left, y, w / 2, h / 2);
					Add(root->LB, data);
					break;
				case 4: //add vao goc RB
					if (root->RB == NULL)
						root->RB = new QuadNode(x, y, w / 2, h / 2);
					Add(root->RB, data);
					break;

				}
			}
		}
	}
	delete rect;
}
bool QuadTree::RECTInRECT(RECT r, RECT rect)
{
	RECT dest;
	if (IntersectRect(&dest, &r, &rect))
		return true;
	else
		return false;
}
void QuadTree::getListObject(QuadNode *root, RECT Screen, cliststatic * listObject)
{
	for (int i = 1; i <= root->clistobject->n; i++)
	if (RECTInRECT(root->clistobject->getRectObject(i), Screen))//kiem tra 2 rect co giao nhau hay ko
	{
		//add object co Rect giao voi man hinh vao list
		listObject->setobject(root->clistobject->getobject(i));
		if (root->clistobject->getobject(i).id == 2)//enermy,object dong thi xoa ngay
		{
			root->clistobject->deleteObjet(i);
			continue;
		}
		if (root->clistobject->getobject(i).id == 3
			&& root->clistobject->getobject(i).kind == 5)//neu la thanh
		{
			root->clistobject->deleteObjet(i);
			continue;
		}
	}
	if (root->LT != NULL && (RECTInRECT(*root->LT->Rect, Screen)))
	{
		getListObject(root->LT, Screen, listObject);
	}
	if (root->RT != NULL && (RECTInRECT(*root->RT->Rect, Screen)))
	{
		getListObject(root->RT, Screen, listObject);
	}
	if (root->LB != NULL && (RECTInRECT(*root->LB->Rect, Screen)))
	{
		getListObject(root->LB, Screen, listObject);

	}
	if (root->RB != NULL && (RECTInRECT(*root->RB->Rect, Screen)))
	{
		getListObject(root->RB, Screen, listObject);

	}
}
void QuadTree::getAllObject(QuadNode *root, cliststatic *listObject)
{
	for (int i = 1; i <= root->clistobject->n; i++)
	{
		listObject->setobject(root->clistobject->getobject(i));
	}

	if (root->LT != NULL)
		getAllObject(root->LT, listObject);
	if (root->RT != NULL)
		getAllObject(root->RT, listObject);
	if (root->LB != NULL)
		getAllObject(root->LB, listObject);
	if (root->RB != NULL)
		getAllObject(root->RB, listObject);

}
void QuadTree::deleteQuadTree(QuadNode *root)
{
	for (int i = 1; i <= root->clistobject->n; i++)
	{
		root->clistobject->deleteallobject();
	}
	if (root->LT != NULL)
		deleteQuadTree(root->LT);
	if (root->RT != NULL)
		deleteQuadTree(root->RT);
	if (root->LB != NULL)
		deleteQuadTree(root->LB);
	if (root->RB != NULL)
		deleteQuadTree(root->RB);
}