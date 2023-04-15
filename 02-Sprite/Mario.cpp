#include "Game.h"
#include "Mario.h"

// Mario object
CMario::CMario(float x, float y, float vx):CGameObject(x, y)
{
	this->vx = vx;
};

void CMario::Update(DWORD dt)
{
	x += vx*dt;

	int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
	if (x <= 0 || x >= BackBufferWidth - MARIO_WIDTH) {

		vx = -vx;

		if (x <= 0)
		{
			x = 0;
		}
		else if (x >= BackBufferWidth - MARIO_WIDTH)
		{
			x = (float)(BackBufferWidth - MARIO_WIDTH);
		}
	}
}

void CMario::Render()
{
	LPANIMATION ani;

	//[RED FLAG][TODO]: Student needs to think about how to associate this animation/asset to Mario!!
	if (vx>0) ani = CAnimations::GetInstance()->Get(500);
	else ani = CAnimations::GetInstance()->Get(501); // if mario is going from left to right, get sprite with id 500, if otherwise get id 501

	ani->Render(x, y);
}

// Koopa object

CKoopa::CKoopa(float x, float y, float vx) :CGameObject(x, y)
{
	this->vx = vx;
};

void CKoopa::Update(DWORD dt)
{
	x += vx * dt;

	int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
	if (x <= 0 || x >= BackBufferWidth - KOOPA_WIDTH) {

		vx = -vx;

		if (x <= 0)
		{
			x = 0;
		}
		else if (x >= BackBufferWidth - KOOPA_WIDTH)
		{
			x = (float)(BackBufferWidth - KOOPA_WIDTH);
		}
	}
}

void CKoopa::Render()
{
	LPANIMATION ani;

	//[RED FLAG][TODO]: Student needs to think about how to associate this animation/asset to Mario!!
	if (vx > 0) ani = CAnimations::GetInstance()->Get(502);
	else ani = CAnimations::GetInstance()->Get(503); // if mario is going from left to right, get sprite with id 500, if otherwise get id 501

	ani->Render(x, y);
}

/****************************************************/

void CBrick::Render() {

	LPANIMATION ani = CAnimations::GetInstance()->Get(510);

	ani->Render(x, y);

}

void CGlassBrick::Render() {

	LPANIMATION ani = CAnimations::GetInstance()->Get(520);

	ani->Render(x, y);

}

void CCoin::Render() {

	LPANIMATION ani = CAnimations::GetInstance()->Get(530);

	ani->Render(x, y);

}