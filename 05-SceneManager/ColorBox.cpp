#include "ColorBox.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"

void CColorBox::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	float xx = x - this->cellWidth / 2 + rect.right / 2;

	// * this line draw ugly red box for some reason?
	CGame::GetInstance()->Draw(xx - cx, y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CColorBox::Render()
{
	if (this->length <= 0) return;

	// DRAW TOP
	float xx = x;
	CSprites* s = CSprites::GetInstance();

	s->Get(this->spriteIdTopBegin)->Draw(xx, y);
	xx += this->cellWidth;
	for (int i = 1; i < this->length - 1; i++)
	{
		s->Get(this->spriteIdTopMiddle)->Draw(xx, y);
		xx += this->cellWidth;
	}
	if (length > 1)
		s->Get(this->spriteIdTopEnd)->Draw(xx, y);

	// DRAW MIDDLE

	for (int j = 0; j < height; j++)
	{
		xx = x;
		s = CSprites::GetInstance();

		s->Get(this->spriteIdMidBegin)->Draw(xx, y + (j + 1) * 9);
		xx += this->cellWidth;
		for (int i = 1; i < this->length - 1; i++)
		{
			s->Get(this->spriteIdMidMiddle)->Draw(xx, y + (j + 1) * 9);
			xx += this->cellWidth;
		}
		if (length > 1)
			s->Get(this->spriteIdMidEnd)->Draw(xx, y + (j + 1) * 9);
	}

	// DRAW BOTTOM
	xx = x;
	s = CSprites::GetInstance();

	s->Get(this->spriteIdBotBegin)->Draw(xx, y + (height + 1) * 9);
	xx += this->cellWidth;
	for (int i = 1; i < this->length - 1; i++)
	{
		s->Get(this->spriteIdBotMiddle)->Draw(xx, y + (height + 1) * 9);
		xx += this->cellWidth;
	}
	if (length > 1)
		s->Get(this->spriteIdBotEnd)->Draw(xx, y + (height + 1) * 9);

	RenderBoundingBox();
}

void CColorBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	float cellWidth_div_2 = this->cellWidth / 2;
	l = x - cellWidth_div_2;
	t = y - this->cellHeight / 2 - 1;
	r = l + this->cellWidth * this->length;
	b = t + this->cellHeight;
}