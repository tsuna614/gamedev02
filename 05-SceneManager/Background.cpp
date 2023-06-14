#include "Background.h"

void CHill::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_HILL)->Render(x, y);
	//RenderBoundingBox();
}

void CHill::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - HILL_BBOX_WIDTH / 2;
	t = y - HILL_BBOX_HEIGHT / 2;
	r = l + HILL_BBOX_WIDTH;
	b = t + HILL_BBOX_HEIGHT;
}