#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_HILL 11000

#define HILL_WIDTH 127
#define HILL_BBOX_WIDTH 127
#define HILL_BBOX_HEIGHT 64

class CHill : public CGameObject {
public:
	CHill(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
};