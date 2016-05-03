#ifndef GAMEMAIN_H
#define GAMEMAIN_H
#include "GLUtil.h"
#include "GLWindow.h"
#include "Scene.h"

class GameMain
{
private:
	enum GameState
	{
		GAME_GAME,
		GAME_MENU
	};
	GameState gameState;
	int prevTime;
	int currentTime;
	float deltaTime;
	SDL_Event e;
	bool gameOn = true;
	GLWindow* window;
	Scene* scene;

	//Private functions below
	void SetDeltaTime();
public:
	GameMain();
	~GameMain();
	void GameLoop();
};
#endif

