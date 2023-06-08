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

//void CMysteryBlock::SetState(int state)
//{
//	switch (state)
//	{
//	case MYSTERYBLOCK_STATE_ACTIVATED:
//
//	}
//}