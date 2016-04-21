#include "GLGUIHandler.h"



GLGUIHandler::GLGUIHandler()
{
	
}

GLGUIHandler::GLGUIHandler(GLShader& shader)
{
	gui = new GUI();
	projection = glm::ortho(0.0f, static_cast<GLfloat>(window::WIDTH), 0.0f, static_cast<GLfloat>(window::HEIGHT));
	shader.Bind();
	glUniformMatrix4fv(shader.GetUnifromLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_BLEND);

	// Player1
	score[PLAYER1] = 0;
	textPos[PLAYER1][0] = 0;
	textPos[PLAYER1][1] = window::HEIGHT - 40;
	textScale[PLAYER1] = 1;
	textStart[PLAYER1] = "Player1: ";
	textEnd[PLAYER1] = " points";
	printText[PLAYER1] = "";

	// Player2
	score[PLAYER2] = 0;
	textPos[PLAYER2][0] = 0;
	textPos[PLAYER2][1] = 0;
	textScale[PLAYER2] = 1;
	textStart[PLAYER2] = "Player2: ";
	textEnd[PLAYER2] = " points";
	printText[PLAYER2] = "";

	// Time
	time = 0;
	newSec = 0;
	textPos[TIME][0] = window::WIDTH * 0.5;
	textPos[TIME][1] = window::HEIGHT * 0.5;
	textScale[TIME] = 1;
	textStart[TIME] = "Counter: ";
	textEnd[TIME] = " sec";
	printText[TIME] = "";
}


GLGUIHandler::~GLGUIHandler()
{
	delete gui;
}

void GLGUIHandler::Update(float dt)
{
	newSec += dt;
	if (newSec >= 1)
	{
		time++;
		newSec = 0;
		printText[TIME] = textStart[TIME] + std::to_string(time) + textEnd[TIME];
		textPos[TIME][0] = (window::WIDTH * 0.5) - (gui->getTextLenght(printText[TIME], textScale[TIME]) * 0.5);
	}
}

void GLGUIHandler::Draw(GLShader& shader)
{
	glViewport(0, 0, window::WIDTH, window::HEIGHT);
	glEnable(GL_BLEND);
	for (int i = 0; i < NUM_TEXTS - 1; i++)
	{
		printText[i] = textStart[i] + std::to_string(score[i]) + textEnd[i];
		gui->RenderText(shader, printText[i], textPos[i][0], textPos[i][1], textScale[i], textColor[i]);
	}
	gui->RenderText(shader, printText[TIME], textPos[TIME][0], textPos[TIME][1], textScale[TIME], textColor[TIME]);
	glDisable(GL_BLEND);
}
