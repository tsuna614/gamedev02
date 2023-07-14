#include "Goomba.h"
#include "Mario.h"
#include "ScoreNumber.h"

/**************** NUMBER *****************/

CNumber100::CNumber100(float x, float y) : CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	this->vx = 0;
	this->vy = 0;
	timer_start = -1;
	die_start = -1;
	SetState(NUMBER_STATE_MOVING_UP);
}

void CNumber100::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - NUMBER_BBOX_WIDTH / 2;
	top = y - NUMBER_BBOX_HEIGHT / 2;
	right = left + NUMBER_BBOX_WIDTH;
	bottom = top + NUMBER_BBOX_HEIGHT;
}

void CNumber100::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CNumber100::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;
	if (dynamic_cast<CMario*>(e->obj)) return;
	if (dynamic_cast<CNumber100*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CNumber100::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (vy > 0) this->Delete();

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CNumber100::Render()
{
	int aniId = ID_ANI_NUMBER_100;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CNumber100::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case NUMBER_STATE_MOVING_UP:
			vy = -NUMBER_MOVING_UP_SPEED;
			ay = 0.0001f;
			break;
	}
}
