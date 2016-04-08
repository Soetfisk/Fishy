#include <crtdbg.h>
#include <stdlib.h>
#include <time.h>

#include "GLUtil.h"
#include "GameMain.h"

void InitDosConsole() {
	AllocConsole();
	freopen("CONIN$", "rb", stdin);
	freopen("CONOUT$", "wb", stdout);
	freopen("CONOUT$", "wb", stderr);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	InitDosConsole();

	//Project Setup:
	// C/C++ -> General -> Additional Include Directories = .\include
	// Linker -> General -> Additional Library Directories = .\lib
	// Linker -> Input -> Additional Dependencies = glew32.lib;glew32s.lib;SDL2.lib;SDL2main.lib;SDL2test.lib;OpenGL32.lib;
	// Project is set to x64 by default, change it to x86 to make it work
	// comment
	GameMain* game = new GameMain();

	game->GameLoop();

	delete game;

}