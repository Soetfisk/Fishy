#pragma once

#include "GUI.h"
#include "GameState.h"
#include "GLModel.h"
#include "GLCamera.h"
#include <time.h>

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
	enum MenuState
	{
		MENU,
		SHOW_CONTROLS,
		NUM_MENU_STATES
	};
	enum MenuButtons
	{
		TITLE,
		START_GAME,
		REMATCH,
		CONTROLS,
		EXIT,
		SELECTED,

		NUM_MENU_BUTTONS
	};
	enum
	{
		PlayerFish,
		GoldFish,
		BlueTang,
		Aquarium
	};

	GLCamera* camera;
	FishBox FSH_Loader;
	GLModel* model;
	GLModel* aquarium;
	GLShader* menuShader;
	GLShader* modelShader;
	GUI* gui;
	glm::mat4 projection;
	MenuButtons selectedBttn;
	MenuState currentMState;
	GLOBAL_GameState* gameState;
	bool deleteShader, deleteGUI;

	GLShader* textureToQuadShader;
	GLuint quadVAO, quadVBO;
	GLuint cTextureID;
	FSHData::texture* controlsTexture;

	GLfloat textPos[NUM_MENU_BUTTONS][2];
	GLfloat textScale[NUM_MENU_BUTTONS];
	glm::vec3 textColor[NUM_MENU_BUTTONS];
	std::string text[NUM_MENU_BUTTONS];

	void InitMenuTextureInfo();
	void HandleUp();
	void HandleDown();
	void HandleSpace();
	void FixSelected();
	void InitModels();

	void RenderQuad();
};

