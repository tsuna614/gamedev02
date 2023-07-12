#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define BRICK_MOVING_SPEED 0.5f

#define ID_ANI_COIN_ANIMATION 11000

#define COIN_ANIMATION_STATE_ACTIVATED 100
#define COIN_ANIMATION_STATE_MOVING_UP 200
#define COIN_ANIMATION_STATE_MOVING_DOWN 300
#define COIN_ANIMATION_STATE_NOT_ACTIVATED 400

#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16


class CCoinAnimation : public CGameObject {
	ULONGLONG timer_start;
public:
	CCoinAnimation(float x, float y) : CGameObject(x, y)
	{
		timer_start = -1;
		this->SetState(COIN_ANIMATION_STATE_MOVING_UP);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	//virtual void SetState(int state);
	virtual void SetState(int state);
	void StartTimer() { timer_start = GetTickCount64(); }

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
};