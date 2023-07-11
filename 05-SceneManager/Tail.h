#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "Brick.h"

#define TAIL_VX_SPEED 0.2f

#define TAIL_BBOX_WIDTH 10
#define TAIL_BBOX_HEIGHT 10
#define TAIL_BBOX_HEIGHT_DIE 10

#define TAIL_MOVING_TIMEOUT 50

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