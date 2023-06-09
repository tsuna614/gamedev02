/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102
	
	SAMPLE 02 - SPRITE AND ANIMATION

	This sample illustrates how to:

		1/ Render a sprite (within a sprite sheet)
		2/ How to manage sprites/animations in a game
		3/ Enhance CGameObject with sprite animation
================================================================ */

#include <Windows.h>
#include <d3d10.h>
#include <d3dx10.h>

#include "debug.h"
#include "Game.h"
#include "Textures.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Animation.h"
#include "Animations.h"


#include "Mario.h"


#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"02 - Sprite animation"
#define WINDOW_ICON_PATH L"mario.ico"

#define BACKGROUND_COLOR D3DXCOLOR(200.0f/255, 200.0f/255, 255.0f/255,0.0f)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_ENEMY2 11
#define ID_TEX_MISC 20

#define TEXTURES_DIR L"textures"
#define TEXTURE_PATH_MARIO TEXTURES_DIR "\\mario.png"
#define TEXTURE_PATH_MISC TEXTURES_DIR "\\misc_transparent.png"
#define TEXTURE_PATH_ENEMIES TEXTURES_DIR "\\enemies.png"
#define TEXTURE_PATH_ENEMIES2 TEXTURES_DIR "\\enemies2.png"

CMario *mario;
#define MARIO_START_X 10.0f
#define MARIO_START_Y 130.0f
#define MARIO_START_VX 0.1f

CKoopa* koopa;
#define KOOPA_START_X 50.0f
#define KOOPA_START_Y 130.0f
#define KOOPA_START_VX 0.1f

CBrick* brick;
CGlassBrick *glassbrick;
CCoin* coin;

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources 
	In this example: load textures, sprites, animations and mario object
*/
void LoadResources()
{
	CTextures * textures = CTextures::GetInstance();

	textures->Add(ID_TEX_MARIO, TEXTURE_PATH_MARIO);
	//textures->Add(ID_ENEMY_TEXTURE, TEXTURE_PATH_ENEMIES, D3DCOLOR_XRGB(156, 219, 239));
	textures->Add(ID_TEX_ENEMY, TEXTURE_PATH_ENEMIES);
	textures->Add(ID_TEX_ENEMY2, TEXTURE_PATH_ENEMIES2);
	textures->Add(ID_TEX_MISC, TEXTURE_PATH_MISC);


	CSprites * sprites = CSprites::GetInstance();
	
	/******************************************************/
	// sprites of mario running

	LPTEXTURE texMario = textures->Get(ID_TEX_MARIO);

	// readline => id, left, top, right 

	sprites->Add(10001, 246, 154, 259, 181, texMario);
	sprites->Add(10002, 275, 154, 290, 181, texMario);
	sprites->Add(10003, 304, 154, 321, 181, texMario);

	sprites->Add(10011, 186, 154, 200, 181, texMario);
	sprites->Add(10012, 155, 154, 171, 181, texMario);
	sprites->Add(10013, 125, 154, 141, 181, texMario);

	CAnimations * animations = CAnimations::GetInstance();
	LPANIMATION ani;

	ani = new CAnimation(100);
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	animations->Add(500, ani);



	ani = new CAnimation(100);
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	animations->Add(501, ani);

	/******************************************************/
	// sprites of koopa moving

	//LPTEXTURE texKoopa[2];
	//texKoopa[0] = textures->Get(ID_TEX_ENEMY);
	//texKoopa[1] = textures->Get(ID_TEX_ENEMY2);

	LPTEXTURE texKoopa = textures->Get(ID_TEX_ENEMY);
	LPTEXTURE texKoopa2 = textures->Get(ID_TEX_ENEMY2);

	// readline => id, left, top, right 

	sprites->Add(10101, 436, 129, 451, 155, texKoopa2);
	sprites->Add(10102, 458, 129, 473, 155, texKoopa2);

	sprites->Add(10111, 28, 129, 43, 155, texKoopa);
	sprites->Add(10112, 6, 129, 22, 155, texKoopa);

	ani = new CAnimation(100);
	ani->Add(10101);
	ani->Add(10102);
	animations->Add(502, ani);



	ani = new CAnimation(100);
	ani->Add(10111);
	ani->Add(10112);
	animations->Add(503, ani);

	/******************************************************/
	// sprites of brick object
	LPTEXTURE texMisc = textures->Get(ID_TEX_MISC);
	sprites->Add(20001, 300, 117, 317, 133, texMisc);
	sprites->Add(20002, 318, 117, 335, 133, texMisc);
	sprites->Add(20003, 336, 117, 353, 133, texMisc);
	sprites->Add(20004, 354, 117, 371, 133, texMisc);

	ani = new CAnimation(100);
	ani->Add(20001,1000);
	ani->Add(20002);
	ani->Add(20003);
	ani->Add(20004);
	animations->Add(510, ani);

	/******************************************************/
	//Adding sprites animation of glassbrick
	sprites->Add(20011, 300, 135, 317, 150, texMisc);
	sprites->Add(20012, 318, 135, 335, 150, texMisc);
	sprites->Add(20013, 336, 135, 353, 150, texMisc);
	sprites->Add(20014, 354, 135, 371, 150, texMisc);

	ani = new CAnimation(200);
	ani->Add(20011,1000);
	ani->Add(20012);
	ani->Add(20013);
	ani->Add(20014);
	animations->Add(520, ani);

	/******************************************************/
	//Adding sprites animation of coin
	sprites->Add(20021, 303, 99, 313, 114, texMisc);
	sprites->Add(20022, 322, 99, 330, 114, texMisc);
	sprites->Add(20023, 342, 99, 346, 114, texMisc);

	ani = new CAnimation(100);
	ani->Add(20021);
	ani->Add(20022);
	ani->Add(20023);
	animations->Add(530, ani);
	
	
	mario = new CMario(MARIO_START_X, MARIO_START_Y, MARIO_START_VX);
	koopa = new CKoopa(KOOPA_START_X, KOOPA_START_Y, KOOPA_START_VX);
	brick = new CBrick(100.0f, 100.0f);
	glassbrick = new CGlassBrick(150.0f, 100.0f);
	coin = new CCoin(125.0f, 130.0f);

	//note to future self: dau tien sprites->Add se them tung sprite texture vao thong qua coordinate (left, top, right, bottom)
	// va cho no 1 cai id, sau do ani->Add se lay id cua tung sprite de dua vao animation.
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	mario->Update(dt); // luu y la se khong co update cua brick va glassbrick, vi coordinate x va y cua no khong thay doi
	koopa->Update(dt);
}

void Render()
{
	CGame* g = CGame::GetInstance();

	ID3D10Device* pD3DDevice = g->GetDirect3DDevice();
	IDXGISwapChain* pSwapChain = g->GetSwapChain();
	ID3D10RenderTargetView* pRenderTargetView = g->GetRenderTargetView();
	ID3DX10Sprite* spriteHandler = g->GetSpriteHandler();

	if (pD3DDevice != NULL)
	{
		// clear the background 
		pD3DDevice->ClearRenderTargetView(pRenderTargetView, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DX10_SPRITE_SORT_TEXTURE);

		// Use Alpha blending for transparent sprites
		FLOAT NewBlendFactor[4] = { 0,0,0,0 };
		pD3DDevice->OMSetBlendState(g->GetAlphaBlending(), NewBlendFactor, 0xffffffff);

		brick->Render();
		glassbrick->Render();
		coin->Render();
		mario->Render();
		koopa->Render();

		// Uncomment this line to see how to draw a porttion of a texture  
		//g->Draw(10, 10, texMisc, 300, 117, 316, 133);


		spriteHandler->End();
		pSwapChain->Present(0, 0);
	}
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = (HICON)LoadImage(hInstance, WINDOW_ICON_PATH, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		DWORD ErrCode = GetLastError();
		DebugOut(L"[ERROR] CreateWindow failed! ErrCode: %d\nAt: %s %d \n", ErrCode, _W(__FILE__), __LINE__);
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	SetDebugWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	ULONGLONG frameStart = GetTickCount64();
	ULONGLONG tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		ULONGLONG now = GetTickCount64();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		ULONGLONG dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			Update((DWORD)dt);
			Render();
		}
		else
			Sleep((DWORD)(tickPerFrame - dt));
	}

	return 1;
}

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
) {
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	// Hello World

	CGame *game = CGame::GetInstance();
	game->Init(hWnd);

	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}