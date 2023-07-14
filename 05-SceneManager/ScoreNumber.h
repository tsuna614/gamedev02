#pragma once
#include "GameObject.h"

#define NUMBER_GRAVITY 0.00004f
#define NUMBER_WALKING_SPEED 0.05f

#define NUMBER_MOVING_UP_SPEED 0.1f
#define NUMBER_MOVING_TIMEOUT 1000


#define NUMBER_BBOX_WIDTH 16
#define NUMBER_BBOX_HEIGHT 14
#define NUMBER_BBOX_HEIGHT_DIE 7

#define NUMBER_DIE_TIMEOUT 500

#define NUMBER_STATE_WALKING 100
#define NUMBER_STATE_DIE 200
#define NUMBER_STATE_MOVING_UP 300

#define ID_ANI_NUMBER_100 6004

/************* NUMBER *****************/

class CNumber100 : public CGameObject
{
protected:
	float ax;
	float ay;

	ULONGLONG die_start;
	ULONGLONG timer_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CNumber100(float x, float y);
	virtual void SetState(int state);
	void StartTimer() { timer_start = GetTickCount64(); }
};