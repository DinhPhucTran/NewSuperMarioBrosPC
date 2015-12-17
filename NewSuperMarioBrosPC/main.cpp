#include <windows.h>
#include "MarioGame.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CMarioGame g(hInstance, L"Mario Sample - A larger world", GAME_SCREEN_RESOLUTION_640_480_24, 0, 60);
	g.Init();
	g.Run();
	
	return 0;
}


