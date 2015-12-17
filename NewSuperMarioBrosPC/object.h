#ifndef _OBJECT_H
#define _OBJECT_H
#include <string>
#include "object.h"
#include "sprite.h"
#include "animation.h"


using namespace std;
class MarioState;//khai báo lớp MarioState,
class MarioAnimationFactory;//khai báo có lớp MarioAnimationFactory



class Object {
public:
	static const string OBJECT_NAME;
	int x, y;
	float ax;
	float ay;
	int width, height;
	float vx, vy;
	float vx_last;//vx của mario trước khi dừng, để xác định hướng di chuyển của mario
	CSprite * mSprite;
	Animation* mAnim;
	Object(int x, int y, int width, int height, float vx, float vy, float vx_last,  float ax, float ay, Animation* anim, CSprite * image);
	Object(int x, int y, int width, int height);
	void setAnimation(Animation* anim);
	Animation* getAnimation();
	void setSprite(CSprite* sprite);
	virtual void update(int t);//Nếu lớp kế thừa có cách thức di chuyển đặc biệt, thì override và định nghĩa cách di chuyển mới.
	virtual string getName();
	virtual void onCollision(Object* ob, int direction);
	virtual void render(int vpx,int vpy);//ObjectManager thấy mario, rùa, goomba ... như là 1 Object, và cần hàm này để render. các lớp kế thừa phải override hàm này để vẽ đối tượng 
	virtual void die();//các lớp kế thừa nên override hàm này để animation hóa cái chết, ví dụ mario thì bay lên rồi rơi xuống...

	int left();		//trả vệ tọa độ x ở cạnh trái
	int right();	//trả về tạo độ x cạnh phải
	int top();		//tọa độ y cạnh trên
	int bottom();	//tạo độ y cạnh dưới
	
	~Object();
};
#endif