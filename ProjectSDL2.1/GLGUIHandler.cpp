#include "GLGUIHandler.h"

GLGUIHandler::GLGUIHandler()
{
	gui = new GUI();
	deleteGUI = true;

	this->shader = new GLShader("text");
	deleteShader = true;

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
		if (newSec >= 1)
		{
			time++;
			newSec = 0;
			printText[TIME] = textStart[TIME] + std::to_string(time) + textEnd[TIME];
			textPos[TIME][0] = (float)(window::HALF_WIDTH - (gui->GetTextLenght(printText[TIME], textScale[TIME]) * 0.5));

			// Update FPS
			printText[FPS] = textStart[FPS] + std::to_string((int)(1 / dt));
			textPos[FPS][0] = window::WIDTH - (gui->GetTextLenght(printText[FPS], textScale[FPS]));
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

	// Player1 Power Up
	textScale[P1POWERUP] = 0.5f;
	textColor[P1POWERUP] = glm::vec3(0, 1, 0);
	textStart[P1POWERUP] = "Power up: ";
	p1CurrentPowerUp = PlayerPowerUpText::NOTHING;
	textEnd[P1POWERUP] = "nothing";
	printText[P1POWERUP] = textStart[P1POWERUP] + textEnd[P1POWERUP];
	textPos[P1POWERUP][0] = textPos[PLAYER1][0];
	textPos[P1POWERUP][1] = textPos[PLAYER1][1] - gui->GetTextHeight(printText[P1POWERUP], textScale[P1POWERUP]) - POWER_UP_OFFSET;
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

void GLGUIHandler::Player1SetPowerUp(PlayerPowerUpText powerUp)
{
	textEnd[P1POWERUP] = powerUpStringMap[powerUp];
	printText[P1POWERUP] = textStart[P1POWERUP] + textEnd[P1POWERUP];
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
	score[PLAYER1] = 0;
	textPos[PLAYER1][0] = 0;
	textPos[PLAYER1][1] = window::HEIGHT - 40;
	textScale[PLAYER1] = 1;
	textColor[PLAYER1] = glm::vec3(0, 1, 0);
	textStart[PLAYER1] = "Fish1 ";
	textEnd[PLAYER1] = " food";
	printText[PLAYER1] = textStart[PLAYER1] + std::to_string(score[PLAYER1]) + textEnd[PLAYER1];

	// Player2 Power Up
	textPos[P2POWERUP][0] = textPos[PLAYER2][0];
	textPos[P2POWERUP][1] = textPos[PLAYER2][1] + gui->GetTextHeight(printText[PLAYER2], textScale[PLAYER2]) + POWER_UP_OFFSET;
	textScale[P2POWERUP] = 0.5f;
	textColor[P2POWERUP] = glm::vec3(0, 1, 0);
	textStart[P2POWERUP] = "Power up: ";
	textEnd[P2POWERUP] = powerUpStringMap[PlayerPowerUpText::NOTHING];
	printText[P2POWERUP] = textStart[P2POWERUP] + textEnd[P2POWERUP];
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

void GLGUIHandler::Player2SetPowerUp(PlayerPowerUpText powerUp)
{
	textEnd[P2POWERUP] = powerUpStringMap[powerUp];
	printText[P2POWERUP] = textStart[P2POWERUP] + textEnd[P2POWERUP];
}

void GLGUIHandler::ResetTime()
{
	time = 0;
	newSec = 0;
	printText[TIME] = textStart[TIME] + std::to_string(time) + textEnd[TIME];
	textPos[TIME][0] = (float)((window::WIDTH * 0.5) - (gui->GetTextLenght(printText[TIME], textScale[TIME]) * 0.5));
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

	// PLAYER1 POWER UP
	textScale[P1POWERUP] = 0.5f;
	textColor[P1POWERUP] = glm::vec3(0, 1, 0);
	textStart[P1POWERUP] = "Power up: ";
	p1CurrentPowerUp = PlayerPowerUpText::NOTHING;
	textEnd[P1POWERUP] = "nothing";
	printText[P1POWERUP] = textStart[P1POWERUP] + textEnd[P1POWERUP];
	textPos[P1POWERUP][0] = textPos[PLAYER1][0];
	textPos[P1POWERUP][1] = textPos[PLAYER1][1] - gui->GetTextHeight(printText[P1POWERUP], textScale[P1POWERUP]) - POWER_UP_OFFSET;

	// PLAYER2 POWER UP
	textPos[P2POWERUP][0] = textPos[PLAYER2][0];
	textPos[P2POWERUP][1] = textPos[PLAYER2][1] + gui->GetTextHeight(printText[PLAYER2], textScale[PLAYER2]) + POWER_UP_OFFSET;
	textScale[P2POWERUP] = 0.5f;
	textColor[P2POWERUP] = glm::vec3(0, 1, 0);
	textStart[P2POWERUP] = "Power up: ";
	p2CurrentPowerUp = PlayerPowerUpText::NOTHING;
	textEnd[P2POWERUP] = "nothing";
	printText[P2POWERUP] = textStart[P2POWERUP] + textEnd[P2POWERUP];
}

void GLGUIHandler::Reset()
{
	currentState = ACTIVE;

	// Player1
	ResetPlayer1();

	// Player2
	ResetPlayer2();

	// Time
	ResetTime();

	// Winner
	printText[WINNER] = "Won!";
	textPos[WINNER][0] = (float)(window::HALF_WIDTH - (gui->GetTextLenght(printText[WINNER], textScale[WINNER]) * 0.5));
	textPos[WINNER][1] = window::HALF_HEIGHT - 20;

	// Loser
	printText[LOSER] = "Lost!";
	textPos[LOSER][0] = (float)(window::HALF_WIDTH - (gui->GetTextLenght(printText[LOSER], textScale[LOSER]) * 0.5));
	textPos[LOSER][1] = window::HALF_HEIGHT - 20;
}

void GLGUIHandler::Tie()
{
	currentState = OVER;
	
	printText[WINNER] = "Tie!";
	textPos[WINNER][0] = (float)(window::HALF_WIDTH - (gui->GetTextLenght(printText[WINNER], textScale[WINNER]) * 0.5));
	textPos[WINNER][1] -= window::QUARTER_HEIGHT;
	
	printText[LOSER] = "Tie!";
	textPos[LOSER][0] = (float)(window::HALF_WIDTH - (gui->GetTextLenght(printText[LOSER], textScale[LOSER]) * 0.5));
	textPos[LOSER][1] += window::QUARTER_HEIGHT;
}
