#ifndef GAMEMAIN_H
#define GAMEMAIN_H
#include "GLUtil.h"
#include "GLWindow.h"
#include "Scene.h"
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
	const unsigned int SCREEN_WIDTH = 1024, SCREEN_HEIGHT = 768;

	//Private functions below
	void SetDeltaTime();
public:
	GameMain();
	~GameMain();
	void GameLoop();
};
#endif

