#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_HILL 11234
#define ID_ANI_OVERWORLD_MAP 11235
#define ID_ANI_BOTTOM_BAR 11236
#define ID_ANI_TITLE_SCREEN 11237

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

class COverworldMap : public CGameObject {
public:
	COverworldMap(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
};

class CBottomBar : public CGameObject {
public:
	CBottomBar(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
};

class CTitleScreen : public CGameObject {
public:
	CTitleScreen(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
};