#include "Goomba.h"
#include "Mario.h"
#include "Mushroom.h"

extern vector<LPGAMEOBJECT> objects;


CMushroom::CMushroom(float x, float y) : CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	this->vx = 0;
	this->vy = 0;
	die_start = -1;
	SetState(MUSHROOM_STATE_MOVING_UP);
	this->isFreezable = 1;
}

void CMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - MUSHROOM_BBOX_WIDTH / 2;
	top = y - MUSHROOM_BBOX_HEIGHT / 2;
	right = left + MUSHROOM_BBOX_WIDTH;
	bottom = top + MUSHROOM_BBOX_HEIGHT;
}

void CMushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;
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

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	//if ((state == MUSHROOM_STATE_DIE) && (GetTickCount64() - die_start > MUSHROOM_DIE_TIMEOUT))
	//{
	//	isDeleted = true;
	//	return;
	//}

	if ((state == MUSHROOM_STATE_MOVING_UP) && (GetTickCount64() - timer_start > MUSHROOM_MOVING_TIMEOUT))
	{
		SetState(MUSHROOM_STATE_WALKING);
	}

	if (state == MUSHROOM_STATE_DIE)
	{
		//this->Delete();
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CMushroom::Render()
{
	int aniId = ID_ANI_MUSHROOM;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CMushroom::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MUSHROOM_STATE_MOVING_UP:
		vy = -MUSHROOM_MOVING_UP_SPEED;
		StartTimer();
		break;
	case MUSHROOM_STATE_DIE:
		//die_start = GetTickCount64();
		//y += (MUSHROOM_BBOX_HEIGHT - MUSHROOM_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case MUSHROOM_STATE_WALKING:
		{
			// Get Mario's position when starting state walking
			CMario* mario = dynamic_cast<CMario*>(objects[0]);
			for (size_t i = 0; i < objects.size(); i++)
			{
				if (dynamic_cast<CMario*>(objects[i]))
				{
					mario = dynamic_cast<CMario*>(objects[i]);
				}
			}
			float mx, my;
			mario->GetPosition(mx, my);


			if (x > mx)
			{
				vx = MUSHROOM_WALKING_SPEED;
			}
			else
			{
				vx = -MUSHROOM_WALKING_SPEED;
			}
			vy = 0;
			ay = MUSHROOM_GRAVITY;
			break;
		}
	}
}
