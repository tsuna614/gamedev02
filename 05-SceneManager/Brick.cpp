#include "Brick.h"


/***************** CLASS BRICK *******************/
void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BRICK)->Render(x, y);
	//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - BRICK_BBOX_WIDTH/2;
	t = y - BRICK_BBOX_HEIGHT/2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}

/***************** CLASS GLASSBRICK *******************/

void CGlassBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_GLASSBRICK)->Render(x, y);
	//RenderBoundingBox();
}

void CGlassBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}

/***************** CLASS MYSTERY BLOCK *******************/

void CMysteryBlock::Render()
{
	int aniID = ID_ANI_MYSTERYBLOCK;
	if (state == MYSTERYBLOCK_STATE_ACTIVATED)
	{
		aniID = ID_ANI_MYSTERYBLOCK_ACTIVATED;
	}
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniID)->Render(x, y);
	//RenderBoundingBox();
}

void CMysteryBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}

void CMysteryBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;

	if (GetTickCount64() - timer_start >= 100 && this->GetState() == MYSTERYBLOCK_STATE_MOVING_UP)
	{
		this->SetState(MYSTERYBLOCK_STATE_MOVING_DOWN);
	}
	else if (GetTickCount64() - timer_start >= 120 && this->GetState() == MYSTERYBLOCK_STATE_MOVING_DOWN)
	{
		vy = 0;
		this->SetState(MYSTERYBLOCK_STATE_ACTIVATED);
	}

}

void CMysteryBlock::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MYSTERYBLOCK_STATE_MOVING_UP:
		vy = -BRICK_MOVING_SPEED;
		StartTimer();
		break;
	case MYSTERYBLOCK_STATE_MOVING_DOWN:
		vy = BRICK_MOVING_SPEED;
		StartTimer();
		break;
	}
}

/***************** CLASS COIN BLOCK *******************/

void CCoinBlock::Render()
{
	int aniID = ID_ANI_MYSTERYBLOCK;
	if (state == MYSTERYBLOCK_STATE_ACTIVATED)
	{
		aniID = ID_ANI_MYSTERYBLOCK_ACTIVATED;
	}
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniID)->Render(x, y);
	//RenderBoundingBox();
}

void CCoinBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}

void CCoinBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;

	if (GetTickCount64() - timer_start >= 100 && this->GetState() == MYSTERYBLOCK_STATE_MOVING_UP)
	{
		this->SetState(MYSTERYBLOCK_STATE_MOVING_DOWN);
	}
	else if (GetTickCount64() - timer_start >= 120 && this->GetState() == MYSTERYBLOCK_STATE_MOVING_DOWN)
	{
		vy = 0;
		this->SetState(MYSTERYBLOCK_STATE_ACTIVATED);
	}

}

void CCoinBlock::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MYSTERYBLOCK_STATE_MOVING_UP:
		vy = -BRICK_MOVING_SPEED;
		StartTimer();
		break;
	case MYSTERYBLOCK_STATE_MOVING_DOWN:
		vy = BRICK_MOVING_SPEED;
		StartTimer();
		break;
	}
}