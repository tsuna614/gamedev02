#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK 10000
#define ID_ANI_FIREBALL 10010
#define BRICK_WIDTH 16

#define OBJECT_GRAVITY 0.002f
#define GROUND_Y 160.0f

class CBrick : public CGameObject {
public:
	CBrick(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt);
};

class CFireball : public CGameObject {
public:
	CFireball(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt);
};