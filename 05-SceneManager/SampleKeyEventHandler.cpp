#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"

#include "Tail.h"

extern vector<LPGAMEOBJECT> objects;

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 
	CGameObject* tail = new CTail(-100, -100);

	switch (KeyCode)
	{
	case DIK_A:
		float mx, my;
		mario->GetPosition(mx, my);
		//tail->SetPosition(mx, my);
		if (mario->GetLevel() == MARIO_LEVEL_TANOOKI)
			if (mario->Getnx() > 0)
			{
				tail->SetPosition(mx, my + 5);
			}
			else
			{
				tail->SetPosition(mx, my + 5);
			}
			objects.push_back(tail);
		mario->isPressingA = 1;
		break;
	case DIK_DOWN:
		if (mario->GetState() != MARIO_STATE_IDLE)
		{
			break;
		}
		mario->SetState(MARIO_STATE_SIT);
		break;
	case DIK_S:
		mario->SetState(MARIO_STATE_JUMP);
		break;
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_3:
		mario->SetLevel(MARIO_LEVEL_TANOOKI);
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_R: // reset
		//Reload();
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_A:
		mario->isPressingA = 0;
		break;
	case DIK_S:
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	case DIK_RIGHT:
		{
			if (game->IsKeyDown(DIK_DOWN))
			{
				mario->SetState(MARIO_STATE_SIT);
			}
			break;
		}
	case DIK_LEFT:
		{
			if (game->IsKeyDown(DIK_DOWN))
			{
				mario->SetState(MARIO_STATE_SIT);
			}
			break;
		}
	}
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_A))
			mario->SetState(MARIO_STATE_RUNNING_RIGHT);
		else
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_A))
			mario->SetState(MARIO_STATE_RUNNING_LEFT);
		else
			mario->SetState(MARIO_STATE_WALKING_LEFT);
	}
	else
		mario->SetState(MARIO_STATE_IDLE);
}