#include <windows.h>
#include "MarioGame.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CMarioGame g(hInstance, L"Super Mario Bro 3", GAME_SCREEN_RESOLUTION_640_480_24, 0, 180 );
	g.Init();
	g.Run();
	
	return 0;
}


