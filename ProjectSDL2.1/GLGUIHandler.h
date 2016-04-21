#pragma once

#include "GUI.h"

class GLGUIHandler
{
public:
	GLGUIHandler();
	GLGUIHandler(GLShader& shader);
	virtual ~GLGUIHandler();

	void Update(float dt);
	void Draw(GLShader& shader);
private:
	enum
	{
		PLAYER1,
		PLAYER2,
		TIME,
		NUM_TEXTS
	};

	GUI* gui;
	glm::mat4 projection;

	int score[NUM_TEXTS - 1];			// The players score
	GLfloat textPos[NUM_TEXTS][2];		// Text positions
	GLfloat textScale[NUM_TEXTS];		// Text scale
	glm::vec3 textColor[NUM_TEXTS];		// Text color
	std::string textStart[NUM_TEXTS];	// String that is in the start of the text
	std::string textEnd[NUM_TEXTS];		// String that is in the end of the text
	std::string printText[NUM_TEXTS];	// The print text
	int time;
	float newSec;
};

