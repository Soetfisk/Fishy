#pragma once

#include "GUI.h"
#include <map>

class GLGUIHandler
{
public:
	enum PlayerPowerUpText
	{
		NOTHING,
		SHOTGUN,
		BIG,
		HIGH,

		NUM_PLAYERPOWERUPTEXTS
	};

	GLGUIHandler();
	GLGUIHandler(GLShader* shader, GUI* textToScreen);
	virtual ~GLGUIHandler();

	void Update(float dt);
	void Draw();
	void OptimizedDraw();
	void Reset();							// Reset everything except rounds
	void ResetRounds();

	void Tie();

	// Player1
	void AddScorePlayer1(int addVal);		// Adds addVal score for player1 
	void DecreaseScorePlayer1(int decVal);	// Decrease addVal score for player1
	void ResetScorePlayer1();				// Reset score for player1
	void ResetPlayer1();					// Reset player1 to start values
	int GetScorePlayer1();					// Returns player1 score
	void Player1Won();						// Make player1 the winner
	void Player1SetPowerUp(PlayerPowerUpText powerUp);

	// Player2
	void AddScorePlayer2(int addVal);
	void DecreaseScorePlayer2(int decVal);
	void ResetScorePlayer2();
	void ResetPlayer2();
	int GetScorePlayer2();
	void Player2Won();
	void Player2SetPowerUp(PlayerPowerUpText powerUp);

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
		P1WINS,
		P2WINS,
		P1POWERUP,
		P2POWERUP,
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

	const float POWER_UP_OFFSET = 5.0f;
	const float ROUND_WIN_X_OFFSET = 5.0f;
	const float ROUND_WIN_Y_OFFSET = 5.0f;

	GUI* gui;
	glm::mat4 projection;
	GLShader* shader;
	bool deleteShader, deleteGUI;

	int score[NUM_TEXTS - 4];				// The players score
	GLfloat textPos[NUM_TEXTS][2];			// Text positions
	GLfloat textScale[NUM_TEXTS];			// Text scale
	glm::vec3 textColor[NUM_TEXTS];			// Text color
	std::string textStart[NUM_TEXTS - 2];	// String that is in the start of the text
	std::string textEnd[NUM_TEXTS - 2];		// String that is in the end of the text
	std::string printText[NUM_TEXTS];		// The print text
	int time;								// Current time
	float newSec;							// Keep track on when it is a new sec
	GameState currentState;
	PlayerPowerUpText p1CurrentPowerUp, p2CurrentPowerUp;
	std::map<PlayerPowerUpText, std::string> powerUpStringMap =
	{
		{ PlayerPowerUpText::NOTHING,	"nothing" },
		{ PlayerPowerUpText::SHOTGUN,	"shotgun" },
		{ PlayerPowerUpText::BIG,		"big bubbles" },
		{ PlayerPowerUpText::HIGH,		"high" }
	};

	void InitTextureInfo();
	int nrFramesThisSecond;
};