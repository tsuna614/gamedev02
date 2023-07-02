#pragma once
#include "GameObject.h"

#define KOOPA_GRAVITY 0.001f
#define KOOPA_WALKING_SPEED 0.05f
#define KOOPA_SHELL_SPEED 0.15f
#define KOOPA_JUMP_SPEED  0.3f


#define KOOPA_BBOX_WIDTH 16
#define KOOPA_BBOX_HEIGHT 24
#define KOOPA_BBOX_HEIGHT_SHELL 14

#define KOOPA_DIE_TIMEOUT 500
#define KOOPA_SHELL_TIMEOUT 5000

#define KOOPA_STATE_WALKING 100
#define KOOPA_STATE_DIE 200
#define KOOPA_STATE_SHELL 300
#define KOOPA_STATE_SHELL_MOVING 400

#define ID_ANI_KOOPA_WALKING_LEFT 5020
#define ID_ANI_KOOPA_WALKING_RIGHT 5021
#define ID_ANI_KOOPA_SHELL 5022
#define ID_ANI_KOOPA_SHELL_MOVING 5023
#define ID_ANI_KOOPA_WING_LEFT 5024
#define ID_ANI_KOOPA_WING_RIGHT 5025

#define KOOPA_LEVEL_SMALL 1
#define KOOPA_LEVEL_BIG 2


class CWingKoopa : public CGameObject
{
protected:
	float ax;
	float ay;

	float mx;
	float my; // cordinate of mario at the moment of colliding with koopa

	float px; // save the direction Koopa was moving before turning into the shell

	int koopaLevel;

	ULONGLONG die_start;
	ULONGLONG shell_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CWingKoopa(float x, float y);
	virtual void SetState(int state);
	void GetMarioPosition(float x, float y) { this->mx = x, this->my = y; }
	int GetLevel() { return this->koopaLevel; }
	void SetLevelSmall() { this->koopaLevel = KOOPA_LEVEL_SMALL; }
};