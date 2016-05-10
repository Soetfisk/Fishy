#include "GLGUIHandler.h"

GLGUIHandler::GLGUIHandler()
{
	gui = new GUI();
	deleteGUI = true;

	this->shader = new GLShader("text");
	deleteShader = true;
	this->nrFramesThisSecond = 0;
	InitTextureInfo();
}

GLGUIHandler::GLGUIHandler(GLShader* shader, GUI* textToScreen)
{
	gui = textToScreen;
	deleteGUI = false;

	this->shader = shader;
	deleteShader = false;

	InitTextureInfo();
}


GLGUIHandler::~GLGUIHandler()
{
	if (deleteGUI)
		delete gui;
	if (deleteShader)
		delete shader;
}

void GLGUIHandler::Update(float dt)
{
	switch (currentState)
	{
	case ACTIVE:
		newSec += dt;
		this->nrFramesThisSecond++;
		if (newSec >= 1)
		{
			time++;
			newSec = 0;
			printText[TIME] = textStart[TIME] + std::to_string(time) + textEnd[TIME];
			textPos[TIME][0] = (float)(window::HALF_WIDTH - (gui->GetTextLenght(printText[TIME], textScale[TIME]) * 0.5));

			// Update FPS
			printText[FPS] = textStart[FPS] + std::to_string(nrFramesThisSecond);
			textPos[FPS][0] = window::WIDTH - (gui->GetTextLenght(printText[FPS], textScale[FPS]));
			this->nrFramesThisSecond = 0;
		}
		break;
	case OVER:
		newSec += dt;
		if (newSec >= 1)
		{
			newSec = 0;
			// Update FPS
			printText[FPS] = textStart[FPS] + std::to_string((int)(1 / dt));
			textPos[FPS][0] = window::WIDTH - (gui->GetTextLenght(printText[FPS], textScale[FPS]));
		}
		break;
	}
}

void GLGUIHandler::Draw()
{
	glViewport(0, 0, window::WIDTH, window::HEIGHT);
	glEnable(GL_BLEND);
	switch (currentState)
	{
	case ACTIVE:
		for (int i = 0; i < NUM_TEXTS - 2; i++)
		{
			gui->RenderText(*shader, printText[i], textPos[i][0], textPos[i][1], textScale[i], textColor[i]);
		}
		break;
	case OVER:
		for(int i = 0; i < NUM_TEXTS; i++)
		{
			gui->RenderText(*shader, printText[i], textPos[i][0], textPos[i][1], textScale[i], textColor[i]);
		}
		break;
	}
	glDisable(GL_BLEND);
}

void GLGUIHandler::OptimizedDraw()
{
	glViewport(0, 0, window::WIDTH, window::HEIGHT);
	glEnable(GL_BLEND);
	switch (currentState)
	{
	case ACTIVE:
		for (int i = 0; i < NUM_TEXTS - 2; i++)
		{
			gui->OptimizedRenderText(*shader, printText[i], textPos[i][0], textPos[i][1], textScale[i], textColor[i]);
		}
		break;
	case OVER:
		for (int i = 0; i < NUM_TEXTS; i++)
		{
			gui->OptimizedRenderText(*shader, printText[i], textPos[i][0], textPos[i][1], textScale[i], textColor[i]);
		}
		break;
	}
	glDisable(GL_BLEND);
}

void GLGUIHandler::AddScorePlayer1(int addVal)
{
	score[PLAYER1] += addVal;
	printText[PLAYER1] = textStart[PLAYER1] + std::to_string(score[PLAYER1]) + textEnd[PLAYER1];
}

void GLGUIHandler::DecreaseScorePlayer1(int decVal)
{
	score[PLAYER1] -= decVal;
	printText[PLAYER1] = textStart[PLAYER1] + std::to_string(score[PLAYER1]) + textEnd[PLAYER1];
	textPos[PLAYER1][0] = window::WIDTH - gui->GetTextLenght(printText[PLAYER1], textScale[PLAYER1]);
}

void GLGUIHandler::ResetScorePlayer1()
{
	score[PLAYER1] = 0;
	printText[PLAYER1] = textStart[PLAYER1] + std::to_string(score[PLAYER1]) + textEnd[PLAYER1];
}

void GLGUIHandler::ResetPlayer1()
{
	score[PLAYER1] = 0;
	textPos[PLAYER1][0] = 0;
	textPos[PLAYER1][1] = window::HEIGHT - 40;
	textScale[PLAYER1] = 1;
	textColor[PLAYER1] = glm::vec3(0, 1, 0);
	textStart[PLAYER1] = "Fish1 ";
	textEnd[PLAYER1] = " food";
	printText[PLAYER1] = textStart[PLAYER1] + std::to_string(score[PLAYER1]) + textEnd[PLAYER1];
}

int GLGUIHandler::GetScorePlayer1()
{
	return score[PLAYER1];
}

void GLGUIHandler::Player1Won()
{
	currentState = OVER;
	textPos[WINNER][1] += window::QUARTER_HEIGHT;
	textPos[LOSER][1] -= window::QUARTER_HEIGHT;
}

void GLGUIHandler::AddScorePlayer2(int addVal)
{
	score[PLAYER2] += addVal;
	printText[PLAYER2] = textStart[PLAYER2] + std::to_string(score[PLAYER2]) + textEnd[PLAYER2];
	textPos[PLAYER2][0] = window::WIDTH - gui->GetTextLenght(printText[PLAYER2], textScale[PLAYER2]);
}

void GLGUIHandler::DecreaseScorePlayer2(int decVal)
{
	score[PLAYER2] -= decVal;
	printText[PLAYER2] = textStart[PLAYER2] + std::to_string(score[PLAYER2]) + textEnd[PLAYER2];
	textPos[PLAYER2][0] = window::WIDTH - gui->GetTextLenght(printText[PLAYER2], textScale[PLAYER2]);
}

void GLGUIHandler::ResetScorePlayer2()
{
	score[PLAYER2] = 0;
	printText[PLAYER2] = textStart[PLAYER2] + std::to_string(score[PLAYER2]) + textEnd[PLAYER2];
	textPos[PLAYER2][0] = window::WIDTH - gui->GetTextLenght(printText[PLAYER2], textScale[PLAYER2]);
}

void GLGUIHandler::ResetPlayer2()
{
	score[PLAYER2] = 0;
	textScale[PLAYER2] = 1;
	textColor[PLAYER2] = glm::vec3(0, 1, 0);
	textStart[PLAYER2] = "Fish2 ";
	textEnd[PLAYER2] = " food";
	printText[PLAYER2] = textStart[PLAYER2] + std::to_string(score[PLAYER2]) + textEnd[PLAYER2];
	textPos[PLAYER2][0] = window::WIDTH - gui->GetTextLenght(printText[PLAYER2], textScale[PLAYER2]);
	textPos[PLAYER2][1] = 0;
}

int GLGUIHandler::GetScorePlayer2()
{
	return score[PLAYER2];
}

void GLGUIHandler::Player2Won()
{
	currentState = OVER;
	textPos[WINNER][1] -= window::QUARTER_HEIGHT;
	textPos[LOSER][1] += window::QUARTER_HEIGHT;
}

void GLGUIHandler::ResetTime()
{
	time = 0;
	newSec = 0;
	printText[TIME] = textStart[TIME] + std::to_string(time) + textEnd[TIME];
	textPos[TIME][0] = window::HALF_WIDTH - (gui->GetTextLenght(printText[TIME], textScale[TIME]) * 0.5);
}

int GLGUIHandler::GetTime()
{
	return time;
}

void GLGUIHandler::InitTextureInfo()
{
	projection = glm::ortho(0.0f, static_cast<GLfloat>(window::WIDTH), 0.0f, static_cast<GLfloat>(window::HEIGHT));
	shader->Bind();
	glUniformMatrix4fv(shader->GetUnifromLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_BLEND);

	currentState = ACTIVE;

	// Player1
	score[PLAYER1] = 0;
	textPos[PLAYER1][0] = 0;
	textPos[PLAYER1][1] = window::HEIGHT - 40;
	textScale[PLAYER1] = 1;
	textColor[PLAYER1] = glm::vec3(0, 1, 0);
	textStart[PLAYER1] = "Fish1 ";
	textEnd[PLAYER1] = " food";
	printText[PLAYER1] = textStart[PLAYER1] + std::to_string(score[PLAYER1]) + textEnd[PLAYER1];

	// Player2
	score[PLAYER2] = 0;
	textPos[PLAYER2][0] = 0;
	textPos[PLAYER2][1] = 0;
	textScale[PLAYER2] = 1;
	textColor[PLAYER2] = glm::vec3(0, 1, 0);
	textStart[PLAYER2] = "Fish2 ";
	textEnd[PLAYER2] = " food";
	// Just to fix start pos
	printText[PLAYER2] = textStart[PLAYER2] + std::to_string(score[PLAYER2]) + textEnd[PLAYER2];
	textPos[PLAYER2][0] = window::WIDTH - gui->GetTextLenght(printText[PLAYER2], textScale[PLAYER2]);

	// Time
	time = 0;
	newSec = 0;
	textPos[TIME][0] = window::HALF_WIDTH;
	textPos[TIME][1] = window::HALF_HEIGHT - 20;
	textScale[TIME] = 1;
	textColor[TIME] = glm::vec3(0, 1, 0);;
	textStart[TIME] = "Time: ";
	textEnd[TIME] = " sec";
	printText[TIME] = "";

	// Winner
	printText[WINNER] = "Won!";
	textScale[WINNER] = 2;
	textPos[WINNER][0] = (float)(window::HALF_WIDTH - (gui->GetTextLenght(printText[WINNER], textScale[WINNER]) * 0.5));
	textPos[WINNER][1] = window::HALF_HEIGHT - 20;
	textColor[WINNER] = glm::vec3(0, 1, 0);

	// Loser
	printText[LOSER] = "Lost!";
	textScale[LOSER] = 2;
	textPos[LOSER][0] = (float)(window::HALF_WIDTH - (gui->GetTextLenght(printText[LOSER], textScale[LOSER]) * 0.5));
	textPos[LOSER][1] = window::HALF_HEIGHT - 20;
	textColor[LOSER] = glm::vec3(0, 1, 0);

	// FPS
	textScale[FPS] = 0.8f;
	textColor[FPS] = glm::vec3(0, 1, 0);
	textStart[FPS] = "FPS: ";
	printText[FPS] = "";
	textPos[FPS][0] = window::WIDTH;
	textPos[FPS][1] = window::HEIGHT - 40;
}

void GLGUIHandler::Reset()
{
	currentState = ACTIVE;

	// Player1
	ResetScorePlayer1();

	// Player2
	ResetScorePlayer2();

	// Time
	ResetTime();

	// Winner
	textPos[WINNER][1] = window::HALF_HEIGHT - 20;

	// Loser
	textPos[LOSER][1] = window::HALF_HEIGHT - 20;
}
