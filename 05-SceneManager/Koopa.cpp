#include "Koopa.h"
#include "Mario.h"
#include "Mushroom.h"
#include "Pipe.h"
#include "Brick.h"

extern vector<LPGAMEOBJECT> objects;

CKoopa::CKoopa(float x, float y) : CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPA_GRAVITY;
	this->px = -1;
	this->mx = -1;
	this->my = -1;
	this->isFreezable = 1;
	die_start = -1;
	SetState(KOOPA_STATE_WALKING);
}

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPA_STATE_DIE || state == KOOPA_STATE_SHELL || state == KOOPA_STATE_SHELL_MOVING)
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT_SHELL / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT_SHELL;
	}
	else
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT;
	}
}

void CKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CInvisibleBarrier*>(e->obj) && this->GetState() == KOOPA_STATE_WALKING)
	{
		vx = -vx;
	}
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CKoopa*>(e->obj)) return;
	if (dynamic_cast<CMario*>(e->obj)) return;
	if (dynamic_cast<CMushroom*>(e->obj)) return;

	if (dynamic_cast<CMysteryBlock*>(e->obj))
	{
		if (e->nx != 0)
		{
			if (e->obj->GetState() == MYSTERYBLOCK_STATE_NOT_ACTIVATED)
			{
				float x, y;
				e->obj->GetPosition(x, y);
				CGameObject* obj = new CMushroom(x, y);
				objects.push_back(obj);
				e->obj->SetState(MYSTERYBLOCK_STATE_MOVING_UP);
			}
		}
	}

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == KOOPA_STATE_DIE) && (GetTickCount64() - die_start > KOOPA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}
	else if ((state == KOOPA_STATE_SHELL) && (GetTickCount64() - shell_start > KOOPA_SHELL_TIMEOUT))
	{
		this->SetState(KOOPA_STATE_WALKING);
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CKoopa::Render()
{
	int aniId;

	if (vx < 0)
	{
		aniId = ID_ANI_KOOPA_WALKING_LEFT;
	}
	else
	{
		aniId = ID_ANI_KOOPA_WALKING_RIGHT;
	}
	// koopa doesn't have a die animation yet
	//if (state == KOOPA_STATE_DIE)
	//{
	//	aniId = ID_ANI_KOOPA_DIE;
	//}

	if (state == KOOPA_STATE_SHELL)
	{
		aniId = ID_ANI_KOOPA_SHELL;
	}
	else if (state == KOOPA_STATE_SHELL_MOVING)
	{ 
		aniId = ID_ANI_KOOPA_SHELL_MOVING;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_STATE_DIE:
		die_start = GetTickCount64();
		y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_SHELL) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case KOOPA_STATE_WALKING:
		y -= (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_SHELL + 10) / 2;
		if (px < 0)
		{
			vx = -KOOPA_WALKING_SPEED;
		}
		else vx = KOOPA_WALKING_SPEED;
		break;
	case KOOPA_STATE_SHELL:
		shell_start = GetTickCount64();
		y -= (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_SHELL - 8) / 2;
		if (vx == abs(KOOPA_WALKING_SPEED))
		{
			px = vx;
		}
		vx = 0;
		vy = 0;
		break;
	case KOOPA_STATE_SHELL_MOVING:
		y -= (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_SHELL) / 2;
		if (mx < x)
		{
			vx = KOOPA_SHELL_SPEED;
		}
		else
		{
			vx = -KOOPA_SHELL_SPEED;
		} // if mario collides with koopa on the left of koopa will make koopa moves to the right and vice versa
		vy = 0;
		break;
	}
}
