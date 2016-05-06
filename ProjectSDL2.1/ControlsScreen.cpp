#include "ControlsScreen.h"

ControlsScreen::ControlsScreen()
{
	//fishBox = nullptr;
	shader = nullptr;
	deleteShader = false;
	state = nullptr;
}

ControlsScreen::ControlsScreen(GLOBAL_GameState* state)
{
	//this->fishBox = fishBox;
	shader = new GLShader("pass");
	deleteShader = true;
	this->state = state;
}

ControlsScreen::ControlsScreen(GLOBAL_GameState* state, GLShader* shader)
{
	//this->fishBox = fishBox;
	this->shader = shader;
	deleteShader = false;
	this->state = state;
}

ControlsScreen::~ControlsScreen()
{
	if (deleteShader)
		delete shader;
}

void ControlsScreen::Draw()
{
	shader->Bind();
	//Texture
	RenderQuad();
}

void ControlsScreen::HandleEvenet(SDL_Event* e)
{
	if (e->type == SDL_KEYDOWN)
	{
		*state = GLOBAL_GameState::MENU;
	}
}

void ControlsScreen::RenderQuad()
{
	if (quadVAO == 0) //init
	{
		GLfloat quadVertices[] = {
			// Positions        // Texture Coords
			-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};
		// Setup plane VAO
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	}
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}