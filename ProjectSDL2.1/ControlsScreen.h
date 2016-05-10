#pragma once
//#include "FishBox.h"
#include "GLShader.h";
#include "GLtexture.h"
#include "GameState.h"

class ControlsScreen
{
public:
	ControlsScreen();
	ControlsScreen(GLOBAL_GameState* state);
	ControlsScreen(GLOBAL_GameState* state, GLShader* shader);
	virtual ~ControlsScreen();

	void Draw();
	void HandleEvenet(SDL_Event* e);
private:
	//FishBox* fishBox;
	GLShader* shader;
	GLOBAL_GameState* state;
	bool deleteShader;
	
	//GLTexture* texture;
	GLuint quadVAO, quadVBO;

	void RenderQuad();
};

