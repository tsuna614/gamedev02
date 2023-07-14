#include "PButton.h"
#include "Brick.h"
#include "Coin.h"

extern vector<LPGAMEOBJECT> objects;

void CPButton::Render()
{
	int aniID = ID_ANI_PBUTTON;
	if (state == PBUTTON_STATE_ACTIVATED)
	{
		aniID = ID_ANI_PBUTTON_ACTIVATED;
	}
	CAnimations* animations = CAnimations::GetInstance();
	if (state == PBUTTON_STATE_ACTIVATED) animations->Get(aniID)->Render(x, y + 3);
	else animations->Get(aniID)->Render(x, y);
	//RenderBoundingBox();
}

void CPButton::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}

void CPButton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;

	if (GetTickCount64() - timer_start >= 5000 && this->GetState() == PBUTTON_STATE_ACTIVATED)
	{
		for (size_t i = 0; i < objects.size(); i++)
		{
			if (dynamic_cast<CCoin*>(objects[i]))
			{
				CCoin* coin = dynamic_cast<CCoin*>(objects[i]);
				float x, y;
				coin->GetPosition(x, y);
				CGameObject* brick = new CGlassBrick(x, y);
				objects.push_back(brick);
				coin->Delete();
			}
		}
	}
}

void CPButton::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PBUTTON_STATE_ACTIVATED:
		CGlassBrick* brick;
		for (size_t i = 0; i < objects.size(); i++)
		{
			if (dynamic_cast<CGlassBrick*>(objects[i]))
			{
				brick = dynamic_cast<CGlassBrick*>(objects[i]);
				float x, y;
				brick->GetPosition(x, y);
				CGameObject* coin = new CCoin(x, y);
				objects.push_back(coin);
				brick->Delete();
			}
		}
		StartTimer();
		break;
	}
}