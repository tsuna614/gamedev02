#include "Tail.h"
#include "Mario.h"
#include "Mushroom.h"
#include "Pipe.h"
#include "Collision.h"
#include "Brick.h"
#include "Game.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Koopa.h"
#include "Piranha.h"
#include "Paragoomba.h"
#include "WingKoopa.h"

extern vector<LPGAMEOBJECT> objects;

CTail::CTail(float x, float y) :CGameObject(x, y)
{
	this->x = x;
	this->y = y;
	this->vx = 0;
	this->vy = 0;
	this->isStarted = -1;
	this->timer_start = -1;
	this->isFreezable = 1;
	SetState(TAIL_STATE_SWING);
}

void CTail::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - TAIL_BBOX_WIDTH / 2;
	top = y - TAIL_BBOX_HEIGHT / 2;
	right = left + TAIL_BBOX_WIDTH;
	bottom = top + TAIL_BBOX_HEIGHT;
}

void CTail::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CTail::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CPiranha*>(e->obj))
	{
		CPiranha* piranha = dynamic_cast<CPiranha*>(e->obj);
		piranha->SetState(PIRANHA_STATE_DIE);
	}
	if (dynamic_cast<CGoomba*>(e->obj))
	{
		CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
		goomba->SetState(GOOMBA_STATE_DIE_2);
	}
	if (dynamic_cast<CParaGoomba*>(e->obj))
	{
		CParaGoomba* goomba = dynamic_cast<CParaGoomba*>(e->obj);
		goomba->SetState(GOOMBA_STATE_DIE_2);
	}
	if (dynamic_cast<CKoopa*>(e->obj))
	{
		CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
		koopa->SetState(KOOPA_STATE_SHELL);
	}
	if (dynamic_cast<CWingKoopa*>(e->obj))
	{
		CWingKoopa* koopa = dynamic_cast<CWingKoopa*>(e->obj);
		koopa->SetState(KOOPA_STATE_SHELL);
	}

	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CTail*>(e->obj)) return;
	if (dynamic_cast<CMario*>(e->obj)) return;
	if (dynamic_cast<CMushroom*>(e->obj)) return;
	if (dynamic_cast<CMysteryBlock*>(e->obj))
	{
		if (e->obj->GetState() == MYSTERYBLOCK_STATE_NOT_ACTIVATED)
		{
			float x, y;
			e->obj->GetPosition(x, y);
			CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
			if (mario->GetLevel() == MARIO_LEVEL_SMALL)
			{
				CGameObject* obj = new CMushroom(x, y, 1);
				objects.push_back(obj);
			}
			else if (mario->GetLevel() == MARIO_LEVEL_BIG || mario->GetLevel() == MARIO_LEVEL_TANOOKI)
			{
				CGameObject* obj = new CLeaf(x, y);
				objects.push_back(obj);
			}
			e->obj->SetState(MYSTERYBLOCK_STATE_MOVING_UP);
		}
	}
	if (dynamic_cast<CCoinBlock*>(e->obj))
	{
		if (e->obj->GetState() == MYSTERYBLOCK_STATE_NOT_ACTIVATED)
		{
			e->obj->SetState(MYSTERYBLOCK_STATE_MOVING_UP);
		}
	}
	if (dynamic_cast<CGlassBrick*>(e->obj))
	{
		e->obj->Delete();
	}

	//if (e->ny != 0)
	//{
	//	vy = 0;
	//}
	//else if (e->nx != 0)
	//{
	//	vx = -vx;
	//}
}

void CTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//vy += ay * dt;
	//vx += ax * dt;


	if (GetTickCount64() - this->timer_start > TAIL_MOVING_TIMEOUT)
	{
		this->Delete();
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CTail::Render()
{
	//int aniId = ID_ANI_TAIL_LEFT;

	//CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	//if (mario->Getnx() > 0)
	//{
	//	aniId = ID_ANI_TAIL_RIGHT;
	//}
	//else
	//{
	//	aniId = ID_ANI_TAIL_LEFT;
	//}

	//CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CTail::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case TAIL_STATE_SWING:
		{
			CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
			if (mario->Getnx() > 0)
			{
				vx = TAIL_VX_SPEED;
			}
			else
			{
				vx = -TAIL_VX_SPEED;
			}
			StartTimer();
			break;
		}
	}
}
