#ifndef GAMEMAIN_H
#define GAMEMAIN_H
#include "GLUtil.h"
#include "GLWindow.h"
#include "Scene.h"
#include "Menu.h"

class GameMain
{
private:
	int prevTime;
	int currentTime;
	float deltaTime;
	SDL_Event e;
	bool gameOn = true;
	GLWindow* window;
	Scene* scene;
	Menu* menu;

	//Private functions below
	void SetDeltaTime();
public:
	GameMain();
	~GameMain();
	void GameLoop();
};
#endif

