#ifndef GAMEMAIN_H
#define GAMEMAIN_H
#include "GLUtil.h"
class GameMain
{
private:
	int prevTime;
	int currentTime;
	float deltaTime;
	SDL_Event e;
	bool gameOn = true;
public:
	GameMain();
	~GameMain();
	void GameLoop();
};
#endif

