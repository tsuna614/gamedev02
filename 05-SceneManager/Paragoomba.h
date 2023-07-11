#pragma once
#include "GameObject.h"
#include "Goomba.h"

#define PARAGOOMBA_GRAVITY 0.002f
#define PARAGOOMBA_WALKING_SPEED 0.05f

#define PARAGOOMBA_SMALL_JUMP_SPEED  0.2f
#define PARAGOOMBA_BIG_JUMP_SPEED  0.4f


#define PARAGOOMBA_BBOX_WIDTH 16
#define PARAGOOMBA_BBOX_HEIGHT 18
#define PARAGOOMBA_BBOX_HEIGHT_DIE 7

#define PARAGOOMBA_DIE_TIMEOUT 500
#define PARAGOOMBA_WALK_TIMEOUT 1500

#define PARAGOOMBA_STATE_WALKING 100
#define PARAGOOMBA_STATE_DIE 200

#define PARAGOOMBA_LEVEL_SMALL 1
#define PARAGOOMBA_LEVEL_BIG 2

#define ID_ANI_PARAGOOMBA_WALKING_BIG 5030
#define ID_ANI_PARAGOOMBA_DIE 5031
#define ID_ANI_PARAGOOMBA_WALKING_SMALL 5032

class CParaGoomba : public CGameObject
{
protected:
	float ax;
	float ay;

	int goombaLevel;

	int isJumping;
	int jumpCount;

	ULONGLONG die_start;
	ULONGLONG walk_start;

	CMario* mario;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return (state != GOOMBA_STATE_DIE_2); };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CParaGoomba(float x, float y);
	virtual void SetState(int state);

	int GetGoombaLevel() { return this->goombaLevel; }
	void SetGoombaLevelToSmall() { this->goombaLevel = PARAGOOMBA_LEVEL_SMALL; }

	void StartWalking() {
		walk_start = GetTickCount64();
	}
};