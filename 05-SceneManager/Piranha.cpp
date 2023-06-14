#include "Piranha.h"
#include "Mario.h"
#include "Mushroom.h"
#include "Pipe.h"
#include "Collision.h"

extern vector<LPGAMEOBJECT> objects;

CPiranha::CPiranha(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	this->isMovingUp = true;
	die_start = -1;
	SetState(PIRANHA_STATE_STAYING);
}

void CPiranha::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == PIRANHA_STATE_DIE)
	{
		left = x - PIRANHA_BBOX_WIDTH / 2;
		top = y - PIRANHA_BBOX_HEIGHT_DIE / 2;
		right = left + PIRANHA_BBOX_WIDTH;
		bottom = top + PIRANHA_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - PIRANHA_BBOX_WIDTH / 2;
		top = y - PIRANHA_BBOX_HEIGHT / 2;
		right = left + PIRANHA_BBOX_WIDTH;
		bottom = top + PIRANHA_BBOX_HEIGHT;
	}
}

void CPiranha::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CPiranha::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CPiranha*>(e->obj)) return;
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

void CPiranha::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;



	if ((state == PIRANHA_STATE_DIE) && (GetTickCount64() - die_start > PIRANHA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	if ((state == PIRANHA_STATE_MOVING) && GetTickCount64() - moving_start > PIRANHA_MOVING_TIMEOUT)
	{
		this->SetState(PIRANHA_STATE_STAYING);
	}

	if ((state == PIRANHA_STATE_STAYING) && GetTickCount64() - staying_start > PIRANHA_STAYING_TIMEOUT)
	{
		this->SetState(PIRANHA_STATE_MOVING);
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CPiranha::Render()
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
	DebugOut(L"%f", mx);
	if (this->x > mx)
	{
		aniId = ID_ANI_PIRANHA_LEFT;
	}
	else
	{
		aniId = ID_ANI_PIRANHA_RIGHT;
	}
	if (state == PIRANHA_STATE_DIE)
	{
		aniId = ID_ANI_PIRANHA_DIE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CPiranha::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PIRANHA_STATE_DIE:
		die_start = GetTickCount64();
		y += (PIRANHA_BBOX_HEIGHT - PIRANHA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case PIRANHA_STATE_MOVING:
		moving_start = GetTickCount64();
		if (isMovingUp)
		{
			vy = -PIRANHA_MOVING_SPEED;
		}
		else
		{
			vy = PIRANHA_MOVING_SPEED;
		}
		isMovingUp = !isMovingUp;
		break;
	case PIRANHA_STATE_STAYING:
		staying_start = GetTickCount64();
		vy = 0;
		break;
	}
}
