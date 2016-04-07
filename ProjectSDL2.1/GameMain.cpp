#include "GameMain.h"



GameMain::GameMain()
{
	this->gameOn = true;
	this->prevTime = 0;
	this->deltaTime = 0.0f;
	this->currentTime = 0;
}


GameMain::~GameMain()
{
}

// The main gameloop
void GameMain::GameLoop()
{
	SDL_PumpEvents();

	while (this->gameOn)
	{
		while (SDL_PollEvent(&e)) // getting events
		{
			if (e.type == SDL_QUIT) // quit when clicking
			{
				this->gameOn = false;
			}
		}
	}

}
