#include "Menu.h"

Menu::Menu()
{
	menuShader = new GLShader("text");
	gui = new GUI();

	projection = glm::ortho(0.0f, static_cast<GLfloat>(window::WIDTH), 0.0f, static_cast<GLfloat>(window::HEIGHT));
	menuShader->Bind();
	glUniformMatrix4fv(menuShader->GetUnifromLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_BLEND);

	float tempY = window::QUARTER_HEIGHT;
	float extraOffset = 20;

	// Title
	text[TITLE] = "Survival of the fishest";
	textScale[TITLE] = 1.4f;
	textColor[TITLE] = glm::vec3(0,1,0);
	textPos[TITLE][0] = window::HALF_WIDTH - (gui->GetTextLenght(text[TITLE], textScale[TITLE]) * 0.5);
	tempY += gui->GetTextHeight(text[TITLE], textScale[TITLE]) + extraOffset;
	textPos[TITLE][1] = window::HEIGHT - tempY;

	// Start Game
	text[START_GAME] = "Start Game";
	textScale[START_GAME] = 1.0f;
	textColor[START_GAME] = glm::vec3(0, 1, 0);
	textPos[START_GAME][0] = window::HALF_WIDTH - (gui->GetTextLenght(text[START_GAME], textScale[START_GAME]) * 0.5);
	tempY += gui->GetTextHeight(text[TITLE], textScale[TITLE]) + extraOffset;
	textPos[START_GAME][1] = window::HEIGHT - tempY;

	// Controls
	text[CONTROLS] = "Controls";
	textScale[CONTROLS] = 1.0f;
	textColor[CONTROLS] = glm::vec3(0, 1, 0);
	textPos[CONTROLS][0] = window::HALF_WIDTH - (gui->GetTextLenght(text[CONTROLS], textScale[CONTROLS]) * 0.5);
	tempY += gui->GetTextHeight(text[TITLE], textScale[TITLE]) + extraOffset;
	textPos[CONTROLS][1] = window::HEIGHT - tempY;

	// Exit
	text[EXIT] = "Exit";
	textScale[EXIT] = 1.0f;
	textColor[EXIT] = glm::vec3(0, 1, 0);
	textPos[EXIT][0] = window::HALF_WIDTH - (gui->GetTextLenght(text[EXIT], textScale[EXIT]) * 0.5);
	tempY += gui->GetTextHeight(text[TITLE], textScale[TITLE]) + extraOffset;
	textPos[EXIT][1] = window::HEIGHT - tempY;

	// Selected
	text[SELECTED] = "$";
	textScale[SELECTED] = 1.0f;
	textColor[SELECTED] = glm::vec3(0, 1, 0);
	textPos[SELECTED][0] = window::HALF_WIDTH - gui->GetTextLenght(text[START_GAME], textScale[START_GAME]) * 0.5 - gui->GetTextLenght(text[SELECTED], textScale[SELECTED]) - 20;

	textPos[SELECTED][1] = textPos[START_GAME][1];
	selectedBttn = START_GAME;
}

Menu::Menu(GLOBAL_GameState & state)
{
	menuShader = new GLShader("text");
	this->gui = new GUI();
	gameState = state;

	projection = glm::ortho(0.0f, static_cast<GLfloat>(window::WIDTH), 0.0f, static_cast<GLfloat>(window::HEIGHT));
	menuShader->Bind();
	glUniformMatrix4fv(menuShader->GetUnifromLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_BLEND);

	float tempY = window::QUARTER_HEIGHT;
	float extraOffset = 20;

	// Title
	text[TITLE] = "Survival of the fishest";
	textScale[TITLE] = 1.4f;
	textColor[TITLE] = glm::vec3(0, 1, 0);
	textPos[TITLE][0] = window::HALF_WIDTH - (gui->GetTextLenght(text[TITLE], textScale[TITLE]) * 0.5);
	tempY += gui->GetTextHeight(text[TITLE], textScale[TITLE]) + extraOffset;
	textPos[TITLE][1] = window::HEIGHT - tempY;

	// Start Game
	text[START_GAME] = "Start Game";
	textScale[START_GAME] = 1.0f;
	textColor[START_GAME] = glm::vec3(0, 1, 0);
	textPos[START_GAME][0] = window::HALF_WIDTH - (gui->GetTextLenght(text[START_GAME], textScale[START_GAME]) * 0.5);
	tempY += gui->GetTextHeight(text[TITLE], textScale[TITLE]) + extraOffset;
	textPos[START_GAME][1] = window::HEIGHT - tempY;

	// Controls
	text[CONTROLS] = "Controls";
	textScale[CONTROLS] = 1.0f;
	textColor[CONTROLS] = glm::vec3(0, 1, 0);
	textPos[CONTROLS][0] = window::HALF_WIDTH - (gui->GetTextLenght(text[CONTROLS], textScale[CONTROLS]) * 0.5);
	tempY += gui->GetTextHeight(text[TITLE], textScale[TITLE]) + extraOffset;
	textPos[CONTROLS][1] = window::HEIGHT - tempY;

	// Exit
	text[EXIT] = "Exit";
	textScale[EXIT] = 1.0f;
	textColor[EXIT] = glm::vec3(0, 1, 0);
	textPos[EXIT][0] = window::HALF_WIDTH - (gui->GetTextLenght(text[EXIT], textScale[EXIT]) * 0.5);
	tempY += gui->GetTextHeight(text[TITLE], textScale[TITLE]) + extraOffset;
	textPos[EXIT][1] = window::HEIGHT - tempY;

	// Selected
	text[SELECTED] = "$";
	textScale[SELECTED] = 1.0f;
	textColor[SELECTED] = glm::vec3(0, 1, 0);
	textPos[SELECTED][0] = window::HALF_WIDTH - gui->GetTextLenght(text[START_GAME], textScale[START_GAME]) * 0.5 - gui->GetTextLenght(text[SELECTED], textScale[SELECTED]) - 20;

	textPos[SELECTED][1] = textPos[START_GAME][1];
	selectedBttn = START_GAME;
}

Menu::Menu(GUI * gui, GLOBAL_GameState& state)
{
	menuShader = new GLShader("text");
	this->gui = gui;
	gameState = state;

	projection = glm::ortho(0.0f, static_cast<GLfloat>(window::WIDTH), 0.0f, static_cast<GLfloat>(window::HEIGHT));
	menuShader->Bind();
	glUniformMatrix4fv(menuShader->GetUnifromLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_BLEND);

	float tempY = window::QUARTER_HEIGHT;
	float extraOffset = 20;

	// Title
	text[TITLE] = "Survival of the fishest";
	textScale[TITLE] = 1.4f;
	textColor[TITLE] = glm::vec3(0, 1, 0);
	textPos[TITLE][0] = window::HALF_WIDTH - (gui->GetTextLenght(text[TITLE], textScale[TITLE]) * 0.5);
	tempY += gui->GetTextHeight(text[TITLE], textScale[TITLE]) + extraOffset;
	textPos[TITLE][1] = window::HEIGHT - tempY;

	// Start Game
	text[START_GAME] = "Start Game";
	textScale[START_GAME] = 1.0f;
	textColor[START_GAME] = glm::vec3(0, 1, 0);
	textPos[START_GAME][0] = window::HALF_WIDTH - (gui->GetTextLenght(text[START_GAME], textScale[START_GAME]) * 0.5);
	tempY += gui->GetTextHeight(text[TITLE], textScale[TITLE]) + extraOffset;
	textPos[START_GAME][1] = window::HEIGHT - tempY;

	// Controls
	text[CONTROLS] = "Controls";
	textScale[CONTROLS] = 1.0f;
	textColor[CONTROLS] = glm::vec3(0, 1, 0);
	textPos[CONTROLS][0] = window::HALF_WIDTH - (gui->GetTextLenght(text[CONTROLS], textScale[CONTROLS]) * 0.5);
	tempY += gui->GetTextHeight(text[TITLE], textScale[TITLE]) + extraOffset;
	textPos[CONTROLS][1] = window::HEIGHT - tempY;

	// Exit
	text[EXIT] = "Exit";
	textScale[EXIT] = 1.0f;
	textColor[EXIT] = glm::vec3(0, 1, 0);
	textPos[EXIT][0] = window::HALF_WIDTH - (gui->GetTextLenght(text[EXIT], textScale[EXIT]) * 0.5);
	tempY += gui->GetTextHeight(text[TITLE], textScale[TITLE]) + extraOffset;
	textPos[EXIT][1] = window::HEIGHT - tempY;

	// Selected
	text[SELECTED] = "$";
	textScale[SELECTED] = 1.0f;
	textColor[SELECTED] = glm::vec3(0, 1, 0);
	textPos[SELECTED][0] = window::HALF_WIDTH - gui->GetTextLenght(text[START_GAME], textScale[START_GAME]) * 0.5 - gui->GetTextLenght(text[SELECTED], textScale[SELECTED]) - 20;

	textPos[SELECTED][1] = textPos[START_GAME][1];
	selectedBttn = START_GAME;
}

Menu::~Menu()
{
	delete gui;
	delete menuShader;
}

void Menu::Update(float dt)
{

}

void Menu::Draw()
{
	glViewport(0, 0, window::WIDTH, window::HEIGHT);
	for (int i = 0; i < NUM_MENU_BUTTONS; i++)
	{
		gui->RenderText(*menuShader, text[i], textPos[i][0], textPos[i][1], textScale[i], textColor[i]);
	}
}

void Menu::HandleEvenet(SDL_Event * e)
{
	if (e->type == SDL_KEYDOWN)
	{
		switch (e->key.keysym.scancode)
		{
		case SDL_SCANCODE_UP:
			HandleUp();
			break;
		case SDL_SCANCODE_DOWN:
			HandleDown();
			break;
		case SDL_SCANCODE_SPACE:

			break;
		default:
			break;
		}
	}
}

void Menu::HandleUp()
{
	switch (selectedBttn)
	{
	case START_GAME:
		textScale[selectedBttn] = 1.0f;
		textPos[selectedBttn][0] = window::HALF_WIDTH - gui->GetTextLenght(text[selectedBttn], textScale[selectedBttn]) * 0.5;

		selectedBttn = EXIT;
		break;
	case CONTROLS:
		textScale[selectedBttn] = 1.0f;
		textPos[selectedBttn][0] = window::HALF_WIDTH - gui->GetTextLenght(text[selectedBttn], textScale[selectedBttn]) * 0.5;

		selectedBttn = START_GAME;
		break;
	case EXIT:
		textScale[selectedBttn] = 1.0f;
		textPos[selectedBttn][0] = window::HALF_WIDTH - gui->GetTextLenght(text[selectedBttn], textScale[selectedBttn]) * 0.5;

		selectedBttn = CONTROLS;
		break;
	default:
		break;
	}

	FixSelected();
}

void Menu::HandleDown()
{
	switch (selectedBttn)
	{
	case START_GAME:
		textScale[selectedBttn] = 1.0f;
		textPos[selectedBttn][0] = window::HALF_WIDTH - gui->GetTextLenght(text[selectedBttn], textScale[selectedBttn]) * 0.5;

		selectedBttn = CONTROLS;
		break;
	case CONTROLS:
		textScale[selectedBttn] = 1.0f;
		textPos[selectedBttn][0] = window::HALF_WIDTH - gui->GetTextLenght(text[selectedBttn], textScale[selectedBttn]) * 0.5;

		selectedBttn = EXIT;
		break;
	case EXIT:
		textScale[selectedBttn] = 1.0f;
		textPos[selectedBttn][0] = window::HALF_WIDTH - gui->GetTextLenght(text[selectedBttn], textScale[selectedBttn]) * 0.5;

		selectedBttn = START_GAME;
		break;
	default:
		break;
	}

	FixSelected();
}

void Menu::FixSelected()
{
	textScale[selectedBttn] = 1.2f;
	textPos[selectedBttn][0] = window::HALF_WIDTH - gui->GetTextLenght(text[selectedBttn], textScale[selectedBttn]) * 0.5;
	textPos[SELECTED][0] = window::HALF_WIDTH - gui->GetTextLenght(text[selectedBttn], textScale[selectedBttn]) * 0.5 - gui->GetTextLenght(text[SELECTED], textScale[SELECTED]) - 20;;
	textPos[SELECTED][1] = textPos[selectedBttn][1];
}

