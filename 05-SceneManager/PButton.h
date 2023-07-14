#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_PBUTTON 5101
#define ID_ANI_PBUTTON_ACTIVATED 5102

#define PBUTTON_STATE_ACTIVATED 100
#define PBUTTON_STATE_NOT_ACTIVATED 200

#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

class CPButton : public CGameObject {
	ULONGLONG timer_start;
public:
	CPButton(float x, float y) : CGameObject(x, y)
	{
		timer_start = -1;
		this->SetState(PBUTTON_STATE_NOT_ACTIVATED);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	//virtual void SetState(int state);
	virtual void SetState(int state);
	void StartTimer() { timer_start = GetTickCount64(); }

	virtual int IsBlocking() { return 0; }
};