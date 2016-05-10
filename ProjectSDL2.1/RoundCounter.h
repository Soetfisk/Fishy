#pragma once

#include "GUI.h"

class RoundCounter
{
public:
	enum RoundPlayers
	{
		PLAYER1,
		PLAYER2,
		NUM_PLAYERS
	};

	RoundCounter();
	RoundCounter(GUI* gui);
	RoundCounter(GLShader* shader, GUI* gui);
	~RoundCounter();

	void Draw();
	void PlayerWon(RoundPlayers player);

private:
	const float X_OFFSET = 5.0f;
	const float Y_OFFSET = 5.0f;

	GLShader* shader;
	GUI* gui;
	bool deleteShader, deleteGUI;
	glm::mat4 projection;

	int score[NUM_PLAYERS];					// The players score
	GLfloat textPos[NUM_PLAYERS][2];		// Text positions
	GLfloat textScale[NUM_PLAYERS];			// Text scale
	glm::vec3 textColor[NUM_PLAYERS];		// Text color
	std::string textEnd[NUM_PLAYERS];		// String that is in the end of the text
	std::string printText[NUM_PLAYERS];		// The print text

	void Init();
};

