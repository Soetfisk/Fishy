#pragma once

#include "GUI.h"

class GLGUIHandler
{
public:
	GLGUIHandler();
	GLGUIHandler(GLShader* shader, GUI* textToScreen);
	virtual ~GLGUIHandler();

	void Update(float dt);
	void Draw();
	void OptimizedDraw();
	void Reset();							// Reset everything

	// Player1
	void AddScorePlayer1(int addVal);		// Adds addVal score for player1 
	void DecreaseScorePlayer1(int decVal);	// Decrease addVal score for player1
	void ResetScorePlayer1();				// Reset score for player1
	void ResetPlayer1();					// Reset player1 to start values
	int GetScorePlayer1();					// Returns player1 score
	void Player1Won();						// Make player1 the winner

	// Player2
	void AddScorePlayer2(int addVal);
	void DecreaseScorePlayer2(int decVal);
	void ResetScorePlayer2();
	void ResetPlayer2();
	int GetScorePlayer2();
	void Player2Won();

	// Time
	void ResetTime();						// Reset time
	int GetTime();							// Return current time

private:
	enum
	{
		PLAYER1,
		PLAYER2,
		TIME,
		FPS,
		WINNER,
		LOSER,
		NUM_TEXTS
	};
	enum GameState
	{
		ACTIVE,
		OVER,
		NUM_STATES
	};

	GUI* gui;
	glm::mat4 projection;
	GLShader* shader;
	bool deleteShader, deleteGUI;

	int score[NUM_TEXTS - 4];				// The players score
	GLfloat textPos[NUM_TEXTS][2];			// Text positions
	GLfloat textScale[NUM_TEXTS];			// Text scale
	glm::vec3 textColor[NUM_TEXTS];			// Text color
	std::string textStart[NUM_TEXTS - 2];	// String that is in the start of the text
	std::string textEnd[NUM_TEXTS - 3];		// String that is in the end of the text
	std::string printText[NUM_TEXTS];		// The print text
	int time;								// Current time
	float newSec;							// Keep track on when it is a new sec
	GameState currentState;

	void InitTextureInfo();
	int nrFramesThisSecond;
};

