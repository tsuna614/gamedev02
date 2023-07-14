#pragma once
#include "GameObject.h"

#define MUSHROOM_GRAVITY 0.002f
#define MUSHROOM_WALKING_SPEED 0.05f

#define MUSHROOM_MOVING_UP_SPEED 0.03f
#define MUSHROOM_MOVING_TIMEOUT 550


#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 14
#define MUSHROOM_BBOX_HEIGHT_DIE 7

#define MUSHROOM_DIE_TIMEOUT 500

#define MUSHROOM_STATE_WALKING 100
#define MUSHROOM_STATE_DIE 200
#define MUSHROOM_STATE_MOVING_UP 300

#define ID_ANI_MUSHROOM 6000
#define ID_ANI_LEAF 6001
#define ID_ANI_MUSHROOM_LIFE 6002

#define MUSHROOM_TYPE_BIG 1
#define MUSHROOM_TYPE_LIFE 2

/************* MUSHROOM *****************/

class CMushroom : public CGameObject
{
protected:
	float ax;
	float ay;

	int mushroomType;

	ULONGLONG die_start;
	ULONGLONG timer_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CMushroom(float x, float y, int type);
	virtual void SetState(int state);
	void StartTimer() { timer_start = GetTickCount64(); }
};

/************* LEAF *****************/

class CLeaf : public CGameObject
{
protected:
	float ax;
	float ay;

	ULONGLONG die_start;
	ULONGLONG timer_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CLeaf(float x, float y);
	virtual void SetState(int state);
	void StartTimer() { timer_start = GetTickCount64(); }
};