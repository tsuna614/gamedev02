#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define BRICK_MOVING_SPEED 0.1f

#define ID_ANI_BRICK 10000

#define ID_ANI_GLASSBRICK 10001

#define ID_ANI_MYSTERYBLOCK 10002
#define ID_ANI_MYSTERYBLOCK_ACTIVATED 10003
#define MYSTERYBLOCK_STATE_ACTIVATED 100
#define MYSTERYBLOCK_STATE_MOVING_UP 200
#define MYSTERYBLOCK_STATE_MOVING_DOWN 300
#define MYSTERYBLOCK_STATE_NOT_ACTIVATED 400

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
	ULONGLONG timer_start;
public:
	CMysteryBlock(float x, float y) : CGameObject(x, y) 
	{
		timer_start = -1;
		this->SetState(MYSTERYBLOCK_STATE_NOT_ACTIVATED);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	//virtual void SetState(int state);
	virtual void SetState(int state);
	void StartTimer() { timer_start = GetTickCount64(); }
};

class CCoinBlock : public CGameObject {
	ULONGLONG timer_start;
public:
	CCoinBlock(float x, float y) : CGameObject(x, y)
	{
		timer_start = -1;
		this->SetState(MYSTERYBLOCK_STATE_NOT_ACTIVATED);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	//virtual void SetState(int state);
	virtual void SetState(int state);
	void StartTimer() { timer_start = GetTickCount64(); }
};
