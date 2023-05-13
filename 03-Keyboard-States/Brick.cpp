#include "Brick.h"
#include "debug.h"

extern vector<LPGAMEOBJECT> objects;

void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BRICK)->Render(x,y);
}

void CBrick::Update(DWORD dt) {
	x += vx * dt;
	y += vy * dt;


	// simple screen edge collision!!!
	if (vx > 0 && x > 290) {
		vx = -vx;
	};
	if (vx < 0 && x < 0) {
		vx = -vx;
	};
}

void CFireball::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_FIREBALL)->Render(x, y);
}

void CFireball::Update(DWORD dt) {
	x += vx * dt;
	y += vy * dt;

	//vy += OBJECT_GRAVITY * dt;

	// simple screen edge collision!!!
	if (vx > 0 && x > 290) {
		vx = -vx;

	};
	if (vx < 0 && x < 0) {
		vx = -vx;
	};

	if (y > GROUND_Y)
	{
		vy = 0; y = GROUND_Y;
		//objects.pop_back();
	}
}

