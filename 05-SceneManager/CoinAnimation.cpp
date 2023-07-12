#include "CoinAnimation.h"

void CCoinAnimation::Render()
{
	int aniID = ID_ANI_COIN_ANIMATION;
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniID)->Render(x, y);
	//RenderBoundingBox();
}

void CCoinAnimation::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}

void CCoinAnimation::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;

	if (GetTickCount64() - timer_start >= 100 && this->GetState() == COIN_ANIMATION_STATE_MOVING_UP)
	{
		this->SetState(COIN_ANIMATION_STATE_MOVING_DOWN);
	}
	else if (GetTickCount64() - timer_start >= 120 && this->GetState() == COIN_ANIMATION_STATE_MOVING_DOWN)
	{
		this->Delete();
	}

}

void CCoinAnimation::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case COIN_ANIMATION_STATE_MOVING_UP:
		vy = -BRICK_MOVING_SPEED;
		StartTimer();
		break;
	case COIN_ANIMATION_STATE_MOVING_DOWN:
		vy = BRICK_MOVING_SPEED;
		StartTimer();
		break;
	}
}