#pragma once
#include "GameObject.h"

#define GOAL_BBOX_WIDTH 16
#define GOAL_BBOX_HEIGHT 16
#define GOAL_BBOX_HEIGHT_DIE 7

#define ID_ANI_GOAL 6003

/************* MUSHROOM *****************/

class CGoal : public CGameObject
{
protected:
	float ax;
	float ay;



	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CGoal(float x, float y);
	virtual void SetState(int state);
};