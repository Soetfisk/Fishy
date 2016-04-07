#include <crtdbg.h>
#include <stdlib.h>
#include <time.h>

#include "GLUtil.h"
#include "GLWindow.h"
#include "GLCamera.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	int prevTime = 0;
	int currentTime = 0;
	float deltaTime = 0.0f;
	float counter = 0;

	//Project Setup:
	// C/C++ -> General -> Additional Include Directories = .\include
	// Linker -> General -> Additional Library Directories = .\lib
	// Linker -> Input -> Additional Dependencies = glew32.lib;glew32s.lib;SDL2.lib;SDL2main.lib;SDL2test.lib;OpenGL32.lib;
	// Project is set to x64 by default, change it to x86 to make it work

	const unsigned int SCREEN_WIDTH = 1024, SCREEN_HEIGHT = 768;

	GLWindow* window = new GLWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL Window");
	GLCamera* camera = new GLCamera(glm::vec3(0, 1, 1), 70.0f, window->GetAspect(), 0.01f, 1000.0f);

	while (!window->IsClosed())
	{
		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - prevTime) / 1000.0f;
		prevTime = currentTime;
		counter += 0.01;
		window->Clear(0.2, 0.2, 0.8);

		//Draw shit here!

		window->Update(deltaTime);
	}

	delete window;
	delete camera;

}