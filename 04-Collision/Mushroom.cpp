#include "Mushroom.h"
#include "Mario.h"
#include "Goomba.h"
#include "Coin.h"

CMushroom::CMushroom(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = MUSHROOM_GRAVITY;
	die_start = -1;
	SetState(MUSHROOM_STATE_WALKING);
}

void CMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == MUSHROOM_STATE_DIE)
	{
		left = x - MUSHROOM_BBOX_WIDTH / 2;
		top = y - MUSHROOM_BBOX_HEIGHT_DIE / 2;
		right = left + MUSHROOM_BBOX_WIDTH;
		bottom = top + MUSHROOM_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - MUSHROOM_BBOX_WIDTH / 2;
		top = y - MUSHROOM_BBOX_HEIGHT / 2;
		right = left + MUSHROOM_BBOX_WIDTH;
		bottom = top + MUSHROOM_BBOX_HEIGHT;
	}
}

void CMushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	/**** MUSHROOM touches coin ****/
	//if (dynamic_cast<CCoin*>(e->obj))
	//	OnCollisionWithCoin(e);

	/***********/
	// * neu collide voi nhung vat sau day thi se return khong lam gi het
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CMushroom*>(e->obj)) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;
	if (dynamic_cast<CMario*>(e->obj)) return;

	if (e->ny != 0) // * neu collide y voi mat dat hoac platform hoac blocks (isBlocking == 1)
	{
		vy = 0;
	}
	else if (e->nx != 0) // * neu collide x voi mot object nao do isBlocking == 1
	{
		vx = -vx;
	}


}

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == MUSHROOM_STATE_DIE) && (GetTickCount64() - die_start > MUSHROOM_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CMushroom::Render()
{
	int aniId = ID_ANI_MUSHROOM;
	//if (state == MUSHROOM_STATE_DIE)
	//{
	//	aniId = ID_ANI_MUSHROOM_DIE;
	//}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CMushroom::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MUSHROOM_STATE_DIE:
		die_start = GetTickCount64(); // this to start death animation
		y += (MUSHROOM_BBOX_HEIGHT - MUSHROOM_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case MUSHROOM_STATE_WALKING:
		vx = -MUSHROOM_WALKING_SPEED;
		break;
	}
}
