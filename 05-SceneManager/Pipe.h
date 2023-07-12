#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_PIPE 12000
#define ID_ANI_BLACK_PIPE 12001

#define PIPE_WIDTH 32
#define PIPE_BBOX_WIDTH 32
#define PIPE_BBOX_HEIGHT 48

class CPipe : public CGameObject {
public:
	CPipe(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	//int IsDirectionCollidable(float nx, float ny)
	//{
	//	return 0;
	//}

	//int IsBlocking() { return 0; }
};

class CWarpPipe : public CGameObject {
public:
	CWarpPipe(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);

};

class CBlackPipe : public CGameObject {
public:
	CBlackPipe(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);

};