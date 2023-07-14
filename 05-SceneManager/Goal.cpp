#include "Goomba.h"
#include "Mario.h"
#include "Goal.h"

CGoal::CGoal(float x, float y) : CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	this->vx = 0;
	this->vy = 0;
}

void CGoal::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - GOAL_BBOX_WIDTH / 2;
	top = y - GOAL_BBOX_HEIGHT / 2;
	right = left + GOAL_BBOX_WIDTH;
	bottom = top + GOAL_BBOX_HEIGHT;
}

void CGoal::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoal::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;
	if (dynamic_cast<CMario*>(e->obj)) return;
	if (dynamic_cast<CGoal*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CGoal::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	//if ((state == GOAL_STATE_DIE) && (GetTickCount64() - die_start > GOAL_DIE_TIMEOUT))
	//{
	//	isDeleted = true;
	//	return;
	//}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoal::Render()
{
	int aniId = ID_ANI_GOAL;


	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CGoal::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{

	}
}