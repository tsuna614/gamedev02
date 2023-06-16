#include "Fireball.h"
#include "Mario.h"
#include "Mushroom.h"
#include "Pipe.h"
#include "Collision.h"

extern vector<LPGAMEOBJECT> objects;

CFireball::CFireball(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	this->isMovingUp = true;
	die_start = -1;
	SetState(FIREBALL_STATE_STAYING);
}

void CFireball::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == FIREBALL_STATE_DIE)
	{
		left = x - FIREBALL_BBOX_WIDTH / 2;
		top = y - FIREBALL_BBOX_HEIGHT_DIE / 2;
		right = left + FIREBALL_BBOX_WIDTH;
		bottom = top + FIREBALL_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - FIREBALL_BBOX_WIDTH / 2;
		top = y - FIREBALL_BBOX_HEIGHT / 2;
		right = left + FIREBALL_BBOX_WIDTH;
		bottom = top + FIREBALL_BBOX_HEIGHT;
	}
}

void CFireball::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CFireball::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CFireball*>(e->obj)) return;
	if (dynamic_cast<CMario*>(e->obj)) return;
	if (dynamic_cast<CMushroom*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CFireball::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;



	if ((state == FIREBALL_STATE_DIE) && (GetTickCount64() - die_start > FIREBALL_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	if ((state == FIREBALL_STATE_MOVING) && GetTickCount64() - moving_start > FIREBALL_MOVING_TIMEOUT)
	{
		this->SetState(FIREBALL_STATE_STAYING);
	}

	if ((state == FIREBALL_STATE_STAYING) && GetTickCount64() - staying_start > FIREBALL_STAYING_TIMEOUT)
	{
		this->SetState(FIREBALL_STATE_MOVING);
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CFireball::Render()
{
	int aniId;
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
		aniId = ID_ANI_FIREBALL_LEFT;
	}
	else
	{
		aniId = ID_ANI_FIREBALL_RIGHT;
	}
	if (state == FIREBALL_STATE_DIE)
	{
		aniId = ID_ANI_FIREBALL_DIE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CFireball::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FIREBALL_STATE_DIE:
		die_start = GetTickCount64();
		y += (FIREBALL_BBOX_HEIGHT - FIREBALL_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case FIREBALL_STATE_MOVING:
		moving_start = GetTickCount64();
		if (isMovingUp)
		{
			vy = -FIREBALL_MOVING_SPEED;
		}
		else
		{
			vy = FIREBALL_MOVING_SPEED;
		}
		isMovingUp = !isMovingUp;
		break;
	case FIREBALL_STATE_STAYING:
		staying_start = GetTickCount64();
		vy = 0;
		break;
	}
}
