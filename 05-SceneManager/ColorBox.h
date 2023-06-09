#pragma once

#include "GameObject.h"

// 
// The most popular type of object in Mario! 
// 
class CColorBox : public CGameObject
{
protected:
	int length;				// Unit: cell 
	int height;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	int spriteIdTopBegin, spriteIdTopMiddle, spriteIdTopEnd;
	int spriteIdMidBegin, spriteIdMidMiddle, spriteIdMidEnd;
	int spriteIdBotBegin, spriteIdBotMiddle, spriteIdBotEnd;

public:
	CColorBox(float x, float y,
		float cell_width, float cell_height, int length, int height,
		int sprite_id_top_begin, int sprite_id_top_middle, int sprite_id_top_end,
		int sprite_id_mid_begin, int sprite_id_mid_middle, int sprite_id_mid_end,
		int sprite_id_bot_begin, int sprite_id_bot_middle, int sprite_id_bot_end) :CGameObject(x, y)
	{
		this->length = length;
		this->height = height;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->spriteIdTopBegin = sprite_id_top_begin;
		this->spriteIdTopMiddle = sprite_id_top_middle;
		this->spriteIdTopEnd = sprite_id_top_end;
		this->spriteIdMidBegin = sprite_id_mid_begin;
		this->spriteIdMidMiddle = sprite_id_mid_middle;
		this->spriteIdMidEnd = sprite_id_mid_end;
		this->spriteIdBotBegin = sprite_id_bot_begin;
		this->spriteIdBotMiddle = sprite_id_bot_middle;
		this->spriteIdBotEnd = sprite_id_bot_end;
	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();

	int IsDirectionCollidable(float nx, float ny)
	{
		if (nx == 0 && ny == -1) return 1;
		else return 0;
	}
};

typedef CColorBox* LPCOLORBOX;