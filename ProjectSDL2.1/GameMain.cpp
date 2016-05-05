#include "GameMain.h"
GameMain::GameMain()
{
	this->gameOn = true;
	this->prevTime = 0;
	this->deltaTime = 0.0f;
	this->currentTime = 0;
	//window is a namespace in util that keeps the value of the width/height, in file GLUtil.h
	this->window = new GLWindow(window::WIDTH, window::HEIGHT, "Survival of the fishest");
	this->textToScreen = new GUI();
	this->gameState = GLOBAL_GameState::MENU;
	this->scene = new Scene(&this->gameState);
	this->menu = new Menu(&this->gameState);
}

GameMain::~GameMain()
{
	delete this->window;
	delete this->scene;
	delete this->menu;
	delete this->textToScreen;
}

// setting delta time
void GameMain::SetDeltaTime()
{
	this->currentTime = SDL_GetTicks();
	this->deltaTime = (currentTime - prevTime) / 1000.0f;
	this->prevTime = currentTime;
}

void GameMain::HandleUpdateDraw()
{
	switch (this->gameState)
	{
	case GLOBAL_GameState::GAME:
		this->scene->Update(this->deltaTime);
		this->scene->DrawScene();

		break;
	case GLOBAL_GameState::MENU:
		this->menu->Update(this->deltaTime);
		this->menu->Draw();
		break;
	case GLOBAL_GameState::CONTROLS:
		break;
	case GLOBAL_GameState::EXIT:
		this->gameOn = false;
		break;
	default:
		std::cout << "GAMESTATE ERROR!\n";
		break;
	}
}

void GameMain::HandleEvents()
{
	switch (this->gameState)
	{
	case GLOBAL_GameState::GAME:
		this->scene->HandleEvenet(&e);
		break;
	case GLOBAL_GameState::MENU:
		this->menu->HandleEvenet(&e);
		break;
	case GLOBAL_GameState::CONTROLS:
		break;
	case GLOBAL_GameState::EXIT:
		this->gameOn = false;
		break;
	default:
		std::cout << "GAMESTATE ERROR!\n";
		break;
	}
}

// The main gameloop
void GameMain::GameLoop()
{
	while (this->gameOn) // Main game loop
	{
		//std::cout << 1 / this->deltaTime << std::endl;
		SDL_PumpEvents();
		this->SetDeltaTime();
		this->window->Clear(0, .1f, 1);

		this->HandleUpdateDraw();

		while (SDL_PollEvent(&e)) // getting events
		{
			if (e.type == SDL_QUIT) // quit when clicking
				this->gameOn = false;
			else if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				this->gameOn = false;
			else
			{
				HandleEvents();
			}
		}
		this->window->Update();
	}
}
