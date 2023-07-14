#pragma once
#include "GameObject.h"
#include "Mario.h"

#define PIRANHA_GRAVITY 0.002f
#define PIRANHA_MOVING_SPEED 0.03f


#define PIRANHA_BBOX_WIDTH 16
#define PIRANHA_BBOX_HEIGHT 31
#define PIRANHA_BBOX_HEIGHT_DIE 10

#define PIRANHA_DIE_TIMEOUT 500
#define PIRANHA_MOVING_TIMEOUT 1200
#define PIRANHA_STAYING_TIMEOUT 1500

#define PIRANHA_STATE_MOVING 100
#define PIRANHA_STATE_STAYING 200
#define PIRANHA_STATE_DIE 300

#define ID_ANI_PIRANHA_TOP_LEFT 5010
#define ID_ANI_PIRANHA_TOP_RIGHT 5011
#define ID_ANI_PIRANHA_BOTTOM_LEFT 5012
#define ID_ANI_PIRANHA_BOTTOM_RIGHT 5013
#define ID_ANI_PIRANHA_DIE 5014
#define ID_ANI_PIRANHA_VERTICAL 5015

#define PIRANHA_TYPE_RED_FIRE 1
#define PIRANHA_TYPE_GREEN_VERTICAL 2

class CPiranha : public CGameObject
{
protected:
	float ax;
	float ay;

	bool isMovingUp;

	int piranhaType;

	ULONGLONG die_start;
	ULONGLONG moving_start;
	ULONGLONG staying_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CPiranha(float x, float y, int type);
	virtual void SetState(int state);
};