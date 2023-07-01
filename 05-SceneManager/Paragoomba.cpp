#include "Paragoomba.h"
#include "Goomba.h"
#include "Mario.h"
#include "Mushroom.h"
#include "Pipe.h"
#include "Brick.h"

extern vector<LPGAMEOBJECT> objects;

CParaGoomba::CParaGoomba(float x, float y) : CGameObject(x, y)
{
	this->ax = 0;
	this->ay = PARAGOOMBA_GRAVITY;
	this->goombaLevel = PARAGOOMBA_LEVEL_BIG;
	this->isJumping = 1;
	this->jumpCount = 0;
	die_start = -1;
	SetState(PARAGOOMBA_STATE_WALKING);

	this->isFreezable = 1;
}

void CParaGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == PARAGOOMBA_STATE_DIE)
	{
		left = x - PARAGOOMBA_BBOX_WIDTH / 2;
		top = y - PARAGOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + PARAGOOMBA_BBOX_WIDTH;
		bottom = top + PARAGOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - PARAGOOMBA_BBOX_WIDTH / 2;
		top = y - PARAGOOMBA_BBOX_HEIGHT / 2;
		right = left + PARAGOOMBA_BBOX_WIDTH;
		bottom = top + PARAGOOMBA_BBOX_HEIGHT;
	}
}

void CParaGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CParaGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CInvisibleBarrier*>(e->obj))
	{
		vx = -vx;
	}
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CParaGoomba*>(e->obj)) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;
	if (dynamic_cast<CMushroom*>(e->obj)) return;


	if (goombaLevel == PARAGOOMBA_LEVEL_BIG)
	{
		if (e->ny != 0)
		{
			if (isJumping == 1)
			{
				if (jumpCount < 3)
				{
					vy = -PARAGOOMBA_SMALL_JUMP_SPEED;
					jumpCount++;
				}
				else
				{
					vy = -PARAGOOMBA_BIG_JUMP_SPEED;
					jumpCount = 0;
					isJumping = 0;
					StartWalking();
				}
			}
			else
			{
				vy = 0;
			}
		}
	}
	else
	{
		if (e->ny != 0)
		{
			vy = 0;
			//vy = -PARAGOOMBA_SMALL_JUMP_SPEED;
		}
	}

	if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CParaGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (goombaLevel == PARAGOOMBA_LEVEL_BIG)
	{
		CMario* mario = dynamic_cast<CMario*>(objects[0]);

		for (size_t i = 0; i < objects.size(); i++)
		{
			if (dynamic_cast<CMario*>(objects[i]))
			{
				mario = dynamic_cast<CMario*>(objects[i]);
			}
		} // look through objects to find Mario

		float mx, my;
		mario->GetPosition(mx, my);

		if (this->x > mx)
		{
			vx = -abs(vx);
		}
		else
		{
			vx = abs(vx);
		}
	}

	if ((state != PARAGOOMBA_STATE_DIE) && (GetTickCount64() - walk_start > PARAGOOMBA_WALK_TIMEOUT && walk_start != -1))
	{
		isJumping = 1;
		walk_start = -1;
	}

	if ((state == PARAGOOMBA_STATE_DIE) && (GetTickCount64() - die_start > PARAGOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CParaGoomba::Render()
{
	int aniId = ID_ANI_PARAGOOMBA_WALKING_BIG;

	if (goombaLevel == PARAGOOMBA_LEVEL_SMALL)
	{
		aniId = ID_ANI_PARAGOOMBA_WALKING_SMALL;
	}
	if (state == PARAGOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_PARAGOOMBA_DIE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CParaGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PARAGOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		y += (PARAGOOMBA_BBOX_HEIGHT - PARAGOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case PARAGOOMBA_STATE_WALKING:
		vx = -PARAGOOMBA_WALKING_SPEED;
		break;
	}
}
