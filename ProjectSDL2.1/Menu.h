#pragma once

#include "GUI.h"
#include "GameState.h"

class Menu
{
public:
	Menu();
	Menu(GLOBAL_GameState* state);
	Menu(GUI* gui, GLOBAL_GameState* state);
	Menu(GUI* gui, GLOBAL_GameState* state, GLShader* shader);
	virtual ~Menu();
	void Update(float dt);
	void Draw();
	void HandleEvenet(SDL_Event* e);

private:
	enum MenuButtons
	{
		TITLE,
		START_GAME,
		CONTROLS,
		EXIT,
		SELECTED,

		NUM_MENU_BUTTONS
	};

	GLShader* menuShader;
	GUI* gui;
	glm::mat4 projection;
	MenuButtons selectedBttn;
	GLOBAL_GameState* gameState;
	bool deleteShader, deleteGUI;

	GLfloat textPos[NUM_MENU_BUTTONS][2];
	GLfloat textScale[NUM_MENU_BUTTONS];
	glm::vec3 textColor[NUM_MENU_BUTTONS];
	std::string text[NUM_MENU_BUTTONS];

	void InitMenuTextureInfo();
	void HandleUp();
	void HandleDown();
	void HandleSpace();
	void FixSelected();
};

