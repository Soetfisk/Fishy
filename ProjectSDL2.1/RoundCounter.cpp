#include "RoundCounter.h"

RoundCounter::RoundCounter()
{
	shader = new GLShader("text");
	deleteShader = true;
	this->gui = new GUI();
	deleteGUI = true;
	
	Init();
}

RoundCounter::RoundCounter(GUI * gui)
{
	shader = new GLShader("text");
	deleteShader = true;
	this->gui = gui;
	deleteGUI = false;

	Init();
}

RoundCounter::RoundCounter(GLShader* shader, GUI * gui)
{
	this->shader = shader;
	deleteShader = false;
	this->gui = gui;
	deleteGUI = false;
	
	Init();
}


RoundCounter::~RoundCounter()
{
	if (deleteShader)
		delete shader;
	if (deleteGUI)
		delete gui;
}

void RoundCounter::Draw()
{
	glViewport(0, 0, window::WIDTH, window::HEIGHT);
	glEnable(GL_BLEND);
	for (int i = 0; i < NUM_PLAYERS; i++)
		gui->RenderText(*shader, printText[i], textPos[i][0], textPos[i][1], textScale[i], textColor[i]);
	glDisable(GL_BLEND);
}

void RoundCounter::PlayerWon(RoundPlayers player)
{
	score[player]++;
	if (score[player] == 1)
		textEnd[player] = " win";
	else
		textEnd[player] = " wins";
	printText[player] = std::to_string(score[player]) + textEnd[player];
}

void RoundCounter::Reset()
{
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		score[i] = 0;
		textEnd[i] = " wins";
		printText[i] = std::to_string(score[i]) + textEnd[i];
	}
}

void RoundCounter::Init()
{
	projection = glm::ortho(0.0f, static_cast<GLfloat>(window::WIDTH), 0.0f, static_cast<GLfloat>(window::HEIGHT));
	shader->Bind();
	glUniformMatrix4fv(shader->GetUnifromLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_BLEND);

	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		score[i] = 0;
		textScale[i] = 0.8f;
		textColor[i] = glm::vec3(0, 1, 0);
		textEnd[i] = " win";
		printText[i] = std::to_string(score[i]) + textEnd[i];
	}
	
	textPos[PLAYER1][0] = X_OFFSET;
	textPos[PLAYER1][1] = window::HALF_HEIGHT + Y_OFFSET;

	textPos[PLAYER2][0] = X_OFFSET;
	textPos[PLAYER2][1] = window::HALF_HEIGHT - gui->GetTextHeight(printText[PLAYER1], textScale[PLAYER1]) - Y_OFFSET;
}
