#pragma once
#include "GameObject.h"

#define PIRANHA_GRAVITY 0.002f
#define PIRANHA_MOVING_SPEED 0.03f


#define PIRANHA_BBOX_WIDTH 16
#define PIRANHA_BBOX_HEIGHT 25
#define PIRANHA_BBOX_HEIGHT_DIE 10

#define PIRANHA_DIE_TIMEOUT 500
#define PIRANHA_MOVING_TIMEOUT 1000
#define PIRANHA_STAYING_TIMEOUT 1500

#define PIRANHA_STATE_MOVING 100
#define PIRANHA_STATE_STAYING 200
#define PIRANHA_STATE_DIE 300

#define ID_ANI_PIRANHA_MOVING 5010
#define ID_ANI_PIRANHA_DIE 5011

class CPiranha : public CGameObject
{
protected:
	float ax;
	float ay;

	bool isMovingUp;

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
	CPiranha(float x, float y);
	virtual void SetState(int state);
};