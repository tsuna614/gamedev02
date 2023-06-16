#pragma once
#include "GameObject.h"
#include "Mario.h"


#define FIREBALL_X_SPEED 0.06f
#define FIREBALL_Y_SPEED 0.03f


#define FIREBALL_BBOX_WIDTH 16
#define FIREBALL_BBOX_HEIGHT 25
#define FIREBALL_BBOX_HEIGHT_DIE 10

#define FIREBALL_DIE_TIMEOUT 500
#define FIREBALL_MOVING_TIMEOUT 1000
#define FIREBALL_STAYING_TIMEOUT 1500

#define FIREBALL_STATE_MOVING 100
#define FIREBALL_STATE_STAYING 200
#define FIREBALL_STATE_DIE 300

#define ID_ANI_FIREBALL 5100

class CFireball : public CGameObject
{
protected:
	float ax;
	float ay;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CFireball(float x, float y);
	virtual void SetState(int state);
};