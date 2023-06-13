#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK 10000

#define ID_ANI_GLASSBRICK 10001

#define ID_ANI_MYSTERYBLOCK 10002
#define ID_ANI_MYSTERYBLOCK_ACTIVATED 10003
#define MYSTERYBLOCK_STATE_ACTIVATED 100

#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

class CBrick : public CGameObject {
public:
	CBrick(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

class CGlassBrick : public CGameObject {
public:
	CGlassBrick(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

class CMysteryBlock : public CGameObject {
public:
	CMysteryBlock(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	//virtual void SetState(int state);
};

class CCoinBlock : public CGameObject {
//protected:
//	float ax;
//	float ay;
//
//	bool isMovingUp;
//
//	ULONGLONG die_start;
//	ULONGLONG moving_start;
//	ULONGLONG staying_start;
//
//	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
//	virtual void Render();
//
//	//virtual int IsCollidable() { return 0; };
//	//virtual int IsBlocking() { return 0; }
public:
	CCoinBlock(float x, float y) : CGameObject(x, y) 
	{
		//this->ax = 0;
		//this->ay = 0;
		//this->isMovingUp = false;
	}

	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	//void Update(DWORD dt)
	//{

	//}
	//virtual void SetState(int state)
	//{

	//}
};
