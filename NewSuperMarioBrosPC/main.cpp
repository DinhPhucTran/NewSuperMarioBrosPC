#include <windows.h>
#include "MarioGame.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CMarioGame g(hInstance, L"Super Mario Bros. 3 PC", GAME_SCREEN_RESOLUTION_576_384_24, 0, 180);
	g.Init();
	g.Run();
	
	return 0;
}


