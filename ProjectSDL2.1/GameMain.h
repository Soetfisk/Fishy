#ifndef GAMEMAIN_H
#define GAMEMAIN_H
#include "GLUtil.h"
#include "GLWindow.h"
#include "Scene.h"
#include "Menu.h"
#include "ControlsScreen.h"


class GameMain
{
private:
	enum
	{
		BACKGROUND,
		HIGH,

		NUM_MUSIC
	};
	GLOBAL_GameState gameState;
	int prevTime;
	int currentTime;
	float deltaTime;
	SDL_Event e;
	bool gameOn;
	GLWindow* window;
	Scene* scene;
	Menu* menu;
	ControlsScreen* controls;
	GUI* textToScreen;

	//Private functions below
	void SetDeltaTime();
	void HandleUpdateDraw();
	void HandleEvents();
public:
	GameMain();
	~GameMain();
	void GameLoop();
};
#endif

