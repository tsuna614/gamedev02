#include "Fireball.h"
#include "Mario.h"
#include "Mushroom.h"
#include "Pipe.h"
#include "Collision.h"

extern vector<LPGAMEOBJECT> objects;

CFireball::CFireball(float x, float y) :CGameObject(x, y)
{
	this->vx = 0;
	this->vy = 0;
	this->ax = 0;
	this->ay = 0;
	this->isFreezable = 1;
	SetState(FIREBALL_STATE_MOVING);
}

void CFireball::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - FIREBALL_BBOX_WIDTH / 2;
	top = y - FIREBALL_BBOX_HEIGHT / 2;
	right = left + FIREBALL_BBOX_WIDTH;
	bottom = top + FIREBALL_BBOX_HEIGHT;
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


	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CFireball::Render()
{
	int aniId = ID_ANI_FIREBALL;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CFireball::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FIREBALL_STATE_MOVING:
		{
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
				if (y > my)
				{
					vx = -FIREBALL_X_SPEED;
					vy = -FIREBALL_Y_SPEED;
				}
				else
				{
					vx = -FIREBALL_X_SPEED;
					vy = FIREBALL_Y_SPEED;
				}
			}
			else
			{
				if (y > my)
				{
					vx = FIREBALL_X_SPEED;
					vy = -FIREBALL_Y_SPEED;
				}
				else
				{
					vx = FIREBALL_X_SPEED;
					vy = FIREBALL_Y_SPEED;
				}
			}
			break;
		}
	}
}
