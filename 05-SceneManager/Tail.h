#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "Brick.h"


#define FIREBALL_X_SPEED 0.06f
#define FIREBALL_Y_SPEED 0.03f


#define FIREBALL_BBOX_WIDTH 10
#define FIREBALL_BBOX_HEIGHT 10
#define FIREBALL_BBOX_HEIGHT_DIE 10

#define FIREBALL_DIE_TIMEOUT 500
#define FIREBALL_MOVING_TIMEOUT 1000
#define FIREBALL_STAYING_TIMEOUT 1500

#define TAIL_STATE_SWING 100

#define ID_ANI_TAIL_LEFT 5222
#define ID_ANI_TAIL_RIGHT 5223

class CTail : public CGameObject
{
protected:
	int isStarted;
	ULONGLONG timer_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }

	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CTail(float x, float y);
	virtual void SetState(int state);
	void StartTimer() { timer_start = GetTickCount64(); isStarted = 1; }
};