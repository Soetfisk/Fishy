#include "GameMain.h"

GameMain::GameMain()
{
	this->gameOn = true;
	this->prevTime = 0;
	this->deltaTime = 0.0f;
	this->currentTime = 0;
	//window is a namespace in util that keeps the value of the width/height, in file GLUtil.h
	this->window = new GLWindow(window::WIDTH, window::HEIGHT, "Survival of the fishest");
}


GameMain::~GameMain()
{
	delete this->window;
}

// The main gameloop
void GameMain::GameLoop()
{
	SDL_PumpEvents();

	while (this->gameOn) // Main game loop
	{
		this->SetDeltaTime();
		this->window->Clear(0.2, 0.2, 0.8);
		this->window->Update();
		this->scene->Update(this->deltaTime);

		while (SDL_PollEvent(&e)) // getting events
		{
			if (e.type == SDL_QUIT) // quit when clicking
			{
				this->gameOn = false;
			}
		}
	}

}

// setting delta time
void GameMain::SetDeltaTime()
{
	this->currentTime = SDL_GetTicks();
	this->deltaTime = (currentTime - prevTime) / 1000.0f;
	this->prevTime = currentTime;
}
