#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"

#include "Mushroom.h"
#include "Brick.h"
#include "Pipe.h"
#include "Piranha.h"
#include "Koopa.h"
#include "Fireball.h"
#include "Paragoomba.h"
#include "WingKoopa.h"
#include "CoinAnimation.h"

#include "Collision.h"

extern vector<LPGAMEOBJECT> objects;

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	if (GetTickCount64() - low_gravity_start > MARIO_LOW_GRAVITY_TIME && this->isPressingA != 1)
	{
		ay = MARIO_GRAVITY;
		low_gravity_start = 0;
	}

	// reset attacking timer
	if (GetTickCount64() - attacking_start > MARIO_ATTACKING_TIME && this->attacking_start != -1)
	{
		isAttacking = 0;
		attacking_start = -1;
	}

	// reset kicking timer
	if (GetTickCount64() - kicking_start > 100 && this->kicking_start != -1)
	{
		isKicking = 0;
		kicking_start = -1;
	}

	isOnPlatform = false;

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

	if (level == MARIO_LEVEL_MAP)
	{
		ax = 0;
		ay = 0;
	}

	if (y > 200) SetState(MARIO_STATE_DIE);
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	//if (dynamic_cast<CPipe*>(e->obj))
	//{
	//	return;
	//}

	if ((e->ny != 0 && e->obj->IsBlocking())/* || dynamic_cast<CPipe*>(e->obj)*/)
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else if ((e->nx != 0 && e->obj->IsBlocking())/* || dynamic_cast<CPipe*>(e->obj)*/)
	{
		vx = 0;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CMushroom*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<CLeaf*>(e->obj))
		OnCollisionWithLeaf(e);
	else if (dynamic_cast<CGlassBrick*>(e->obj) || dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	else if (dynamic_cast<CMysteryBlock*>(e->obj))
		OnCollisionWithMysteryBlock(e);
	else if (dynamic_cast<CPiranha*>(e->obj))
		OnCollisionWithPiranha(e);
	else if (dynamic_cast<CCoinBlock*>(e->obj))
		OnCollisionWithCoinBlock(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CFireball*>(e->obj))
		OnCollisionWithFireball(e);
	else if (dynamic_cast<CParaGoomba*>(e->obj))
		OnCollisionWithParaGoomba(e);
	else if (dynamic_cast<CWingKoopa*>(e->obj))
		OnCollisionWithWingKoopa(e);
	else if (dynamic_cast<CWarpPipe*>(e->obj))
		OnCollisionWithWarpPipe(e);
	else if (dynamic_cast<CBlackPipe*>(e->obj))
		OnCollisionWithBlackPipe(e);
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE && goomba->GetState() != GOOMBA_STATE_DIE_2)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE && goomba->GetState() != GOOMBA_STATE_DIE_2)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level -= 1;
					StartUntouchable();
					StartFreezing();
					
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithParaGoomba(LPCOLLISIONEVENT e)
{
	CParaGoomba* goomba = dynamic_cast<CParaGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetGoombaLevel() == PARAGOOMBA_LEVEL_BIG)
		{
			goomba->SetGoombaLevelToSmall();
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (goomba->GetState() != PARAGOOMBA_STATE_DIE)
		{
			goomba->SetState(PARAGOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != PARAGOOMBA_STATE_DIE && goomba->GetState() != GOOMBA_STATE_DIE_2)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level -= 1;
					StartUntouchable();
					StartFreezing();

				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);

	// jump on top >> kill koopa and deflect a bit 
	if (e->ny < 0)
	{
		if (koopa->GetState() != KOOPA_STATE_SHELL)
		{
			koopa->SetState(KOOPA_STATE_SHELL);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (koopa->GetState() == KOOPA_STATE_SHELL)
		{
			//koopa->GetMarioPosition(this->x, this->y);
			koopa->SetState(KOOPA_STATE_SHELL_MOVING);
		}
	}
	else // collision with koopa by the side
	{
		if (untouchable == 0)
		{
			if (koopa->GetState() == KOOPA_STATE_WALKING || koopa->GetState() == KOOPA_STATE_SHELL_MOVING)
			{
				// if koopa shell is moving, kills mario when touches
				if (level > MARIO_LEVEL_SMALL)
				{
					level -= 1;
					StartUntouchable();
					StartFreezing();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
			else if (koopa->GetState() == KOOPA_STATE_SHELL)
			{
				// if koopa shell is not moving, either kicks it or pick it up when pressing A

				//if (this->GetState() == MARIO_STATE_RUNNING_LEFT)
				//{
				//	//koopa->SetPosition(this->x - 15, this->y);
				//	koopa->isBeingHeld = true;
				//}
				//else if (this->GetState() == MARIO_STATE_RUNNING_RIGHT)
				//{
				//	//koopa->SetPosition(this->x + 15, this->y);
				//	koopa->isBeingHeld = true;
				//}

				if (this->isPressingA == 1 && isHoldingKoopa != 1)
				{
					isHoldingKoopa = 1;
					koopa->isBeingHeld = true;
				}
				else
				{
					if (isHoldingKoopa != 1)
					{
						//koopa->GetMarioPosition(this->x, this->y);
						StartKicking();
						koopa->SetState(KOOPA_STATE_SHELL_MOVING);
					}
				}
			}
		}
	}
}

void CMario::OnCollisionWithWingKoopa(LPCOLLISIONEVENT e)
{
	CWingKoopa* koopa = dynamic_cast<CWingKoopa*>(e->obj);

	// jump on top >> kill koopa and deflect a bit 
	if (e->ny < 0)
	{
		if (koopa->GetLevel() == KOOPA_LEVEL_BIG)
		{
			koopa->SetLevelSmall();
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else
		{
			if (koopa->GetState() != KOOPA_STATE_SHELL)
			{
				koopa->SetState(KOOPA_STATE_SHELL);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
			else if (koopa->GetState() == KOOPA_STATE_SHELL)
			{
				koopa->SetState(KOOPA_STATE_SHELL_MOVING);
			}
		}
	}
	else // collide with koopa by the side
	{
		if (untouchable == 0)
		{
			if (koopa->GetState() == KOOPA_STATE_WALKING || koopa->GetState() == KOOPA_STATE_SHELL_MOVING)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level -= 1;
					StartUntouchable();
					StartFreezing();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
			else if (koopa->GetState() == KOOPA_STATE_SHELL)
			{
				if (this->isPressingA == 1 && isHoldingKoopa != 1)
				{
					isHoldingKoopa = 1;
					koopa->isBeingHeld = true;
				}
				else
				{
					if (isHoldingKoopa != 1)
					{
						//koopa->GetMarioPosition(this->x, this->y);
						StartKicking();
						koopa->SetState(KOOPA_STATE_SHELL_MOVING);
					}
				}
			}
		}
	}
}

void CMario::OnCollisionWithPiranha(LPCOLLISIONEVENT e)
{
	CPiranha* piranha = dynamic_cast<CPiranha*>(e->obj);
	if (untouchable == 0)
	{
		if (piranha->GetState() != GOOMBA_STATE_DIE)
		{
			if (level > MARIO_LEVEL_SMALL)
			{
				level -= 1;
				StartUntouchable();
				StartFreezing();
			}
			else
			{
				DebugOut(L">>> Mario DIE >>> \n");
				SetState(MARIO_STATE_DIE);
			}
		}
	}
}

void CMario::OnCollisionWithFireball(LPCOLLISIONEVENT e)
{
	if (level > MARIO_LEVEL_SMALL && untouchable == 0)
	{
		level -= 1;
		StartUntouchable();
		StartFreezing();
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	if (level < MARIO_LEVEL_BIG)
	{
		this->y -= 10;
		level = MARIO_LEVEL_BIG;
		StartFreezing();
	}
	e->obj->SetState(MUSHROOM_STATE_DIE);
	//e->obj->Delete();
}

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	if (level < MARIO_LEVEL_BIG)
	{
		this->y -= 10;
		level = MARIO_LEVEL_BIG;
		StartFreezing();
	}
	else if (level == MARIO_LEVEL_BIG)
	{
		level = MARIO_LEVEL_TANOOKI;
		StartFreezing();
	}
	e->obj->SetState(MUSHROOM_STATE_DIE);
	//e->obj->Delete();
}

void CMario::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	if (e->ny > 0 && level > MARIO_LEVEL_SMALL)
	{
		e->obj->Delete();
	}
}

void CMario::OnCollisionWithMysteryBlock(LPCOLLISIONEVENT e)
{
	if (e->ny > 0)
	{
		if (e->obj->GetState() == MYSTERYBLOCK_STATE_NOT_ACTIVATED)
		{
			float x, y;
			e->obj->GetPosition(x, y);
			if (level == MARIO_LEVEL_SMALL)
			{
				CGameObject* obj = new CMushroom(x, y);
				objects.push_back(obj);
			}
			else if (level == MARIO_LEVEL_BIG || level == MARIO_LEVEL_TANOOKI)
			{
				CGameObject* obj = new CLeaf(x, y);
				objects.push_back(obj);
			}
			e->obj->SetState(MYSTERYBLOCK_STATE_MOVING_UP);
		}
	}
}

void CMario::OnCollisionWithCoinBlock(LPCOLLISIONEVENT e)
{
	if (e->ny > 0)
	{
		if (e->obj->GetState() == MYSTERYBLOCK_STATE_NOT_ACTIVATED)
		{
			//float x, y;
			//e->obj->GetPosition(x, y);
			//CGameObject* obj = new CMushroom(x, y - 15);
			//objects.push_back(obj);
			float x, y;
			e->obj->GetPosition(x, y);
			CGameObject* obj = new CCoinAnimation(x, y);
			objects.push_back(obj);
			coin++;
			e->obj->SetState(MYSTERYBLOCK_STATE_MOVING_UP);
		}
	}
}

void CMario::OnCollisionWithWarpPipe(LPCOLLISIONEVENT e)
{
	if (e->ny < 0)
	{
		if (isSitting)
		{
			CGame::GetInstance()->InitiateSwitchScene(5);
		}
	}
}

void CMario::OnCollisionWithBlackPipe(LPCOLLISIONEVENT e)
{
	if (e->ny > 0)
	{
		if (isPressingUp)
		{
			CGame::GetInstance()->InitiateSwitchScene(3);
		}
	}
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	if (isHoldingKoopa == 0)
	{
		if (!isOnPlatform)
		{
			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (nx >= 0)
					return ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
				else
					return ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
			}
			else
			{
				if (nx >= 0)
					return ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
				else
					return ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
			}
		}
		else
			if (isSitting)
			{
				if (nx > 0)
					return ID_ANI_MARIO_SIT_RIGHT;
				else
					return ID_ANI_MARIO_SIT_LEFT;
			}
			else
				if (vx == 0)
				{
					if (nx > 0) return ID_ANI_MARIO_SMALL_IDLE_RIGHT;
					else return ID_ANI_MARIO_SMALL_IDLE_LEFT;
				}
				else if (vx > 0)
				{
					if (ax < 0)
						return ID_ANI_MARIO_SMALL_BRACE_RIGHT;
					else if (ax == MARIO_ACCEL_RUN_X)
						return ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
					else if (ax == MARIO_ACCEL_WALK_X)
						return ID_ANI_MARIO_SMALL_WALKING_RIGHT;
				}
				else // vx < 0
				{
					if (ax > 0)
						return ID_ANI_MARIO_SMALL_BRACE_LEFT;
					else if (ax == -MARIO_ACCEL_RUN_X)
						return ID_ANI_MARIO_SMALL_RUNNING_LEFT;
					else if (ax == -MARIO_ACCEL_WALK_X)
						return ID_ANI_MARIO_SMALL_WALKING_LEFT;
				}

		return ID_ANI_MARIO_SMALL_IDLE_RIGHT;
	}
	else // isHoldingKoopa == 1
	{
		if (!isOnPlatform)
		{
			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (nx >= 0)
					return ID_ANI_MARIO_SMALL_HOLDING_KOOPA_JUMP_RUN_RIGHT;
				else
					return ID_ANI_MARIO_SMALL_HOLDING_KOOPA_JUMP_RUN_LEFT;
			}
			else
			{
				if (nx >= 0)
					return ID_ANI_MARIO_SMALL_HOLDING_KOOPA_JUMP_RUN_RIGHT;
				else
					return ID_ANI_MARIO_SMALL_HOLDING_KOOPA_JUMP_RUN_LEFT;
			}
		}
		else
		{
			if (vx == 0)
			{
				if (nx > 0) return ID_ANI_MARIO_SMALL_HOLDING_KOOPA_IDLE_RIGHT;
				else return ID_ANI_MARIO_SMALL_HOLDING_KOOPA_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					return ID_ANI_MARIO_SMALL_HOLDING_KOOPA_WALKING_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					return ID_ANI_MARIO_SMALL_HOLDING_KOOPA_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					return ID_ANI_MARIO_SMALL_HOLDING_KOOPA_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					return ID_ANI_MARIO_SMALL_HOLDING_KOOPA_WALKING_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					return ID_ANI_MARIO_SMALL_HOLDING_KOOPA_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					return ID_ANI_MARIO_SMALL_HOLDING_KOOPA_WALKING_LEFT;
			}
		}

		return ID_ANI_MARIO_SMALL_HOLDING_KOOPA_IDLE_RIGHT;
	}
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	if (isHoldingKoopa == 0)
	{
		if (!isOnPlatform)
		{
			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (nx >= 0)
					return ID_ANI_MARIO_JUMP_RUN_RIGHT;
				else
					return ID_ANI_MARIO_JUMP_RUN_LEFT;
			}
			else
			{
				if (nx >= 0)
					return ID_ANI_MARIO_JUMP_WALK_RIGHT;
				else
					return ID_ANI_MARIO_JUMP_WALK_LEFT;
			}
		}
		else
			if (isSitting)
			{
				if (nx > 0)
					return ID_ANI_MARIO_SIT_RIGHT;
				else
					return ID_ANI_MARIO_SIT_LEFT;
			}
			else
				if (vx == 0)
				{
					if (nx > 0) return ID_ANI_MARIO_IDLE_RIGHT;
					else return ID_ANI_MARIO_IDLE_LEFT;
				}
				else if (vx > 0)
				{
					if (ax < 0)
						return ID_ANI_MARIO_BRACE_RIGHT;
					else if (ax == MARIO_ACCEL_RUN_X)
						return ID_ANI_MARIO_RUNNING_RIGHT;
					else if (ax == MARIO_ACCEL_WALK_X)
						return ID_ANI_MARIO_WALKING_RIGHT;
				}
				else // vx < 0
				{
					if (ax > 0)
						return ID_ANI_MARIO_BRACE_LEFT;
					else if (ax == -MARIO_ACCEL_RUN_X)
						return ID_ANI_MARIO_RUNNING_LEFT;
					else if (ax == -MARIO_ACCEL_WALK_X)
						return ID_ANI_MARIO_WALKING_LEFT;
				}

		return ID_ANI_MARIO_IDLE_RIGHT;
	}
	else // isHoldingKoopa == 1
	{
		if (!isOnPlatform)
		{
			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (nx >= 0)
					return ID_ANI_MARIO_BIG_HOLDING_KOOPA_JUMP_RUN_RIGHT;
				else
					return ID_ANI_MARIO_BIG_HOLDING_KOOPA_JUMP_RUN_LEFT;
			}
			else
			{
				if (nx >= 0)
					return ID_ANI_MARIO_BIG_HOLDING_KOOPA_JUMP_RUN_RIGHT;
				else
					return ID_ANI_MARIO_BIG_HOLDING_KOOPA_JUMP_RUN_LEFT;
			}
		}
		else
		{
			if (vx == 0)
			{
				if (nx > 0) return ID_ANI_MARIO_BIG_HOLDING_KOOPA_IDLE_RIGHT;
				else return ID_ANI_MARIO_BIG_HOLDING_KOOPA_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					return ID_ANI_MARIO_BIG_HOLDING_KOOPA_WALKING_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					return ID_ANI_MARIO_BIG_HOLDING_KOOPA_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					return ID_ANI_MARIO_BIG_HOLDING_KOOPA_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					return ID_ANI_MARIO_BIG_HOLDING_KOOPA_WALKING_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					return ID_ANI_MARIO_BIG_HOLDING_KOOPA_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					return ID_ANI_MARIO_BIG_HOLDING_KOOPA_WALKING_LEFT;
			}
		}

		return ID_ANI_MARIO_BIG_HOLDING_KOOPA_IDLE_RIGHT;
	}
}

//
// Get animdation ID for tanooki Mario
//
int CMario::GetAniIdTanooki()
{
	if (isHoldingKoopa == 0)
	{
		if (!isOnPlatform)
		{
			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (nx >= 0)
					return ID_ANI_MARIO_TANOOKI_JUMP_RUN_RIGHT;
				else
					return ID_ANI_MARIO_TANOOKI_JUMP_RUN_LEFT;
			}
			else
			{
				if (nx >= 0)
					return ID_ANI_MARIO_TANOOKI_JUMP_WALK_RIGHT;
				else
					return ID_ANI_MARIO_TANOOKI_JUMP_WALK_LEFT;
			}
		}
		else
			if (isSitting)
			{
				if (nx > 0)
					return ID_ANI_MARIO_TANOOKI_SIT_RIGHT;
				else
					return ID_ANI_MARIO_TANOOKI_SIT_LEFT;
			}
			else
				if (vx == 0)
				{
					if (nx > 0) return ID_ANI_MARIO_TANOOKI_IDLE_RIGHT;
					else return ID_ANI_MARIO_TANOOKI_IDLE_LEFT;
				}
				else if (vx > 0)
				{
					if (ax < 0)
						return ID_ANI_MARIO_TANOOKI_BRACE_RIGHT;
					else if (ax == MARIO_ACCEL_RUN_X)
						return ID_ANI_MARIO_TANOOKI_RUNNING_RIGHT;
					else if (ax == MARIO_ACCEL_WALK_X)
					{
						return ID_ANI_MARIO_TANOOKI_WALKING_RIGHT;
					}
				}
				else // vx < 0
				{
					if (ax > 0)
						return ID_ANI_MARIO_TANOOKI_BRACE_LEFT;
					else if (ax == -MARIO_ACCEL_RUN_X)
						return ID_ANI_MARIO_TANOOKI_RUNNING_LEFT;
					else if (ax == -MARIO_ACCEL_WALK_X)
						return ID_ANI_MARIO_TANOOKI_WALKING_LEFT;
				}

		return ID_ANI_MARIO_TANOOKI_IDLE_RIGHT;
	}
	else // isHoldingKoopa == 1
	{
		if (!isOnPlatform)
		{
			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (nx >= 0)
					return ID_ANI_MARIO_TANOOKI_HOLDING_KOOPA_JUMP_RUN_RIGHT;
				else
					return ID_ANI_MARIO_TANOOKI_HOLDING_KOOPA_JUMP_RUN_LEFT;
			}
			else
			{
				if (nx >= 0)
					return ID_ANI_MARIO_TANOOKI_HOLDING_KOOPA_JUMP_RUN_RIGHT;
				else
					return ID_ANI_MARIO_TANOOKI_HOLDING_KOOPA_JUMP_RUN_LEFT;
			}
		}
		else
		{
			if (vx == 0)
			{
				if (nx > 0) return ID_ANI_MARIO_TANOOKI_HOLDING_KOOPA_IDLE_RIGHT;
				else return ID_ANI_MARIO_TANOOKI_HOLDING_KOOPA_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					return ID_ANI_MARIO_TANOOKI_HOLDING_KOOPA_WALKING_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					return ID_ANI_MARIO_TANOOKI_HOLDING_KOOPA_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
				{
					return ID_ANI_MARIO_TANOOKI_HOLDING_KOOPA_WALKING_RIGHT;
				}
			}
			else // vx < 0
			{
				if (ax > 0)
					return ID_ANI_MARIO_TANOOKI_HOLDING_KOOPA_WALKING_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					return ID_ANI_MARIO_TANOOKI_HOLDING_KOOPA_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					return ID_ANI_MARIO_TANOOKI_HOLDING_KOOPA_WALKING_LEFT;
			}
		}

		return ID_ANI_MARIO_TANOOKI_HOLDING_KOOPA_IDLE_RIGHT;
	}
}

int CMario::GetAniIdTanookiTail()
{
	if (isHoldingKoopa == 0)
	{
		if (!isOnPlatform)
		{
			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (nx >= 0)
					return ID_ANI_MARIO_TANOOKI_TAIL_JUMP_RUN_RIGHT;
				else
					return ID_ANI_MARIO_TANOOKI_TAIL_JUMP_RUN_LEFT;
			}
			else
			{
				if (nx >= 0)
					return ID_ANI_MARIO_TANOOKI_TAIL_JUMP_WALK_RIGHT;
				else
					return ID_ANI_MARIO_TANOOKI_TAIL_JUMP_WALK_LEFT;
			}
		}
		else
			if (isSitting)
			{
				if (nx > 0)
					return ID_ANI_MARIO_TANOOKI_TAIL_SIT_RIGHT;
				else
					return ID_ANI_MARIO_TANOOKI_TAIL_SIT_LEFT;
			}
			else
				if (vx == 0)
				{
					if (nx > 0) return ID_ANI_MARIO_TANOOKI_TAIL_IDLE_RIGHT;
					else return ID_ANI_MARIO_TANOOKI_TAIL_IDLE_LEFT;
				}
				else if (vx > 0)
				{
					if (ax < 0)
						return 0;
					else if (ax == MARIO_ACCEL_RUN_X)
						return ID_ANI_MARIO_TANOOKI_TAIL_RUNNING_RIGHT;
					else if (ax == MARIO_ACCEL_WALK_X)
					{
						return ID_ANI_MARIO_TANOOKI_TAIL_WALKING_RIGHT;
					}
				}
				else // vx < 0
				{
					if (ax > 0)
						return 0;
					else if (ax == -MARIO_ACCEL_RUN_X)
						return ID_ANI_MARIO_TANOOKI_TAIL_RUNNING_LEFT;
					else if (ax == -MARIO_ACCEL_WALK_X)
						return ID_ANI_MARIO_TANOOKI_TAIL_WALKING_LEFT;
				}

		return ID_ANI_MARIO_TANOOKI_TAIL_IDLE_RIGHT;
	}
	else // isHoldingKoopa == 1
	{
		if (!isOnPlatform)
		{
			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (nx >= 0)
					return ID_ANI_MARIO_TANOOKI_TAIL_HOLDING_KOOPA_JUMP_RUN_RIGHT;
				else
					return ID_ANI_MARIO_TANOOKI_TAIL_HOLDING_KOOPA_JUMP_RUN_LEFT;
			}
			else
			{
				if (nx >= 0)
					return ID_ANI_MARIO_TANOOKI_TAIL_HOLDING_KOOPA_JUMP_RUN_RIGHT;
				else
					return ID_ANI_MARIO_TANOOKI_TAIL_HOLDING_KOOPA_JUMP_RUN_LEFT;
			}
		}
		else
		{
			if (vx == 0)
			{
				if (nx > 0) return ID_ANI_MARIO_TANOOKI_TAIL_HOLDING_KOOPA_IDLE_RIGHT;
				else return ID_ANI_MARIO_TANOOKI_TAIL_HOLDING_KOOPA_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					return 0;
				else if (ax == MARIO_ACCEL_RUN_X)
					return ID_ANI_MARIO_TANOOKI_TAIL_HOLDING_KOOPA_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
				{
					return ID_ANI_MARIO_TANOOKI_TAIL_HOLDING_KOOPA_WALKING_RIGHT;
				}
			}
			else // vx < 0
			{
				if (ax > 0)
					return 0;
				else if (ax == -MARIO_ACCEL_RUN_X)
					return ID_ANI_MARIO_TANOOKI_TAIL_HOLDING_KOOPA_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					return ID_ANI_MARIO_TANOOKI_TAIL_HOLDING_KOOPA_WALKING_LEFT;
			}
		}

		return ID_ANI_MARIO_TANOOKI_TAIL_HOLDING_KOOPA_IDLE_RIGHT;
	}
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;



	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (isAttacking == 1)
	{
		if (nx < 0)
		{
			aniId = ID_ANI_MARIO_TANOOKI_ATTACK_LEFT;
		}
		else if (nx > 0)
		{
			aniId = ID_ANI_MARIO_TANOOKI_ATTACK_RIGHT;
		}
	}
	else if (isKicking == 1)
	{
		if (level == MARIO_LEVEL_SMALL)
		{
			if (nx > 0)
			{
				aniId = ID_ANI_MARIO_SMALL_KICK_RIGHT;
			}
			else if (nx < 0)
			{
				aniId = ID_ANI_MARIO_SMALL_KICK_LEFT;
			}
		}
		else if (level == MARIO_LEVEL_BIG)
		{
			if (nx > 0)
			{
				aniId = ID_ANI_MARIO_BIG_KICK_RIGHT;
			}
			else if (nx < 0)
			{
				aniId = ID_ANI_MARIO_BIG_KICK_LEFT;
			}
		}
		else if (level == MARIO_LEVEL_TANOOKI)
		{
			if (nx > 0)
			{
				aniId = ID_ANI_MARIO_TANOOKI_KICK_RIGHT;
			}
			else if (nx < 0)
			{
				aniId = ID_ANI_MARIO_TANOOKI_KICK_LEFT;
			}
		}

	}
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_TANOOKI)
		aniId = GetAniIdTanooki();
	else if (level == MARIO_LEVEL_MAP)
		aniId = ID_ANI_MARIO_MAP;

	animations->Get(aniId)->Render(x, y);
	if (level == MARIO_LEVEL_TANOOKI && isAttacking == 0 && state != MARIO_STATE_DIE)
	{
		aniId = GetAniIdTanookiTail();
		
		if (aniId != 0)
		{
			if (isHoldingKoopa == 0)
			{
				if (aniId == ID_ANI_MARIO_TANOOKI_TAIL_SIT_RIGHT)
				{
					animations->Get(aniId)->Render(x - 10, y);
				}
				else if (aniId == ID_ANI_MARIO_TANOOKI_TAIL_SIT_LEFT)
				{
					animations->Get(aniId)->Render(x + 10, y);
				}
				if (nx > 0)
				{
					animations->Get(aniId)->Render(x - 12, y);
				}
				else
				{
					animations->Get(aniId)->Render(x + 12, y);
				}
			}
			else
			{
				if (nx > 0)
				{
					animations->Get(aniId)->Render(x - 11, y);
				}
				else
				{
					animations->Get(aniId)->Render(x + 11, y);
				}
			}
		}
	}
	else if (level == MARIO_LEVEL_TANOOKI && isAttacking == 1)
	{
		if (nx > 0)
		{
			aniId = ID_ANI_MARIO_TANOOKI_TAIL_ATTACK_RIGHT;
			animations->Get(aniId)->Render(x - 12, y);
		}
		else
		{
			aniId = ID_ANI_MARIO_TANOOKI_TAIL_ATTACK_LEFT;
			animations->Get(aniId)->Render(x + 12, y);
		}
	}
	//animations->Get(aniId)->Render(x - 10, y);

	//RenderBoundingBox();
	
	DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting)
		{
			isSitting = false;
			y -= 5;
		};
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting)
		{
			isSitting = false;
			y -= 5;
		};
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting)
		{
			isSitting = false;
			y -= 5;
		};
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting)
		{
			isSitting = false;
			y -= 5;
		};
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;
	case MARIO_STATE_FLYING:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		if (!isOnPlatform)
		{
			if (isPressingA == 1)
			{
				vy = -0.25;
				//ay = 0;
				SetState(MARIO_STATE_GLIDE);
				StartLowGravity();
			}
			else
			{
				vy = 0;
				SetState(MARIO_STATE_GLIDE);
				StartLowGravity();
			}
		}
		break;
	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		if (level == MARIO_LEVEL_TANOOKI && level != MARIO_LEVEL_MAP)
		{
			ay = MARIO_GRAVITY;
		}
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y +=MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;

	//case MARIO_STATE_ATTACK:
	//	if (!isAttacking)
	//	{
	//		StartAttacking();
	//	}
	//	break;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level == MARIO_LEVEL_BIG)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else if (level == MARIO_LEVEL_TANOOKI)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else if (nx < 0)
		{
			left = x - MARIO_TANOOKI_BBOX_WIDTH / 2;
			top = y - MARIO_TANOOKI_BBOX_HEIGHT / 2;
			right = left + MARIO_TANOOKI_BBOX_WIDTH;
			bottom = top + MARIO_TANOOKI_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_TANOOKI_BBOX_WIDTH / 2;
			top = y - MARIO_TANOOKI_BBOX_HEIGHT / 2;
			right = left + MARIO_TANOOKI_BBOX_WIDTH;
			bottom = top + MARIO_TANOOKI_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH/2;
		top = y - MARIO_SMALL_BBOX_HEIGHT/2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}

