//#pragma once
#include "GameObject.h"

#define FREEZE_TIME 500

class CAliveGameObject : public CGameObject
{
public:
	int freeze;
	ULONGLONG freeze_start;
	CAliveGameObject(float x, float y) : CGameObject(x, y)
	{
		this->x = x;
		this->y = y;
		this->freeze = 0;
		this->freeze_start = -1;
	};
	void StartFreezing() { freeze = 1; freeze_start = GetTickCount64(); }
	void UpdateFreezeTime()
	{
		if (GetTickCount64() - freeze_start > FREEZE_TIME)
		{
			this->freeze = 0;
			this->freeze_start = 0;
		}
	};
};