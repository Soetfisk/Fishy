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

	// Title
	text[TITLE] = "Survival of the fishest";
	textScale[TITLE] = 1.0f;
	textColor[TITLE] = glm::vec3(0,1,0);
	textPos[TITLE][0] = window::HALF_WIDTH - (gui->getTextLenght(text[TITLE], textScale[TITLE]) * 0.5);
	textPos[TITLE][1] = window::HALF_HEIGHT + window::QUARTER_HEIGHT;
	
	// Start Game
	text[START_GAME] = "Start Game";
	textScale[START_GAME] = 1.0f;
	textColor[START_GAME] = glm::vec3(0, 1, 0);
	textPos[START_GAME][0] = window::HALF_WIDTH - (gui->getTextLenght(text[START_GAME], textScale[START_GAME]) * 0.5);
	textPos[START_GAME][1] = window::HALF_HEIGHT;

	// Temp
	text[TEMP] = "Temp";
	textScale[TEMP] = 1.0f;
	textColor[TEMP] = glm::vec3(0, 1, 0);
	textPos[TEMP][0] = window::HALF_WIDTH - (gui->getTextLenght(text[TEMP], textScale[TEMP]) * 0.5);
	textPos[TEMP][1] = window::HALF_HEIGHT - window::QUARTER_HEIGHT;

	// Selected
	text[SELECTED] = "$";
	textScale[SELECTED] = 1.0f;
	textColor[SELECTED] = glm::vec3(0, 1, 0);
	textPos[SELECTED][0] = window::HALF_WIDTH - gui->getTextLenght(text[START_GAME], textScale[START_GAME]) - gui->getTextLenght(text[SELECTED], textScale[SELECTED]);
	textPos[SELECTED][1] = window::HALF_HEIGHT;
}

Menu::Menu(GUI * gui)
{
	menuShader = new GLShader("text");
	this->gui = gui;

	// Title
	text[TITLE] = "Survival of the fishest";
	textScale[TITLE] = 1.0f;
	textColor[TITLE] = glm::vec3(0, 1, 0);
	textPos[TITLE][0] = window::HALF_WIDTH - (gui->getTextLenght(text[TITLE], textScale[TITLE]) * 0.5);
	textPos[TITLE][1] = window::HALF_HEIGHT + window::QUARTER_HEIGHT;

	// Start Game
	text[START_GAME] = "Start Game";
	textScale[START_GAME] = 1.0f;
	textColor[START_GAME] = glm::vec3(0, 1, 0);
	textPos[START_GAME][0] = window::HALF_WIDTH - (gui->getTextLenght(text[START_GAME], textScale[START_GAME]) * 0.5);
	textPos[START_GAME][1] = window::HALF_HEIGHT;

	// Temp
	text[TEMP] = "Temp";
	textScale[TEMP] = 1.0f;
	textColor[TEMP] = glm::vec3(0, 1, 0);
	textPos[TEMP][0] = window::HALF_WIDTH - (gui->getTextLenght(text[TEMP], textScale[TEMP]) * 0.5);
	textPos[TEMP][1] = window::HALF_HEIGHT - window::QUARTER_HEIGHT;

	// Selected
	text[SELECTED] = "->";
	textScale[SELECTED] = 1.0f;
	textColor[SELECTED] = glm::vec3(0, 1, 0);
	textPos[SELECTED][0] = window::HALF_WIDTH - gui->getTextLenght(text[SELECTED], textScale[SELECTED]) - gui->getTextLenght(text[SELECTED], textScale[SELECTED]);
	textPos[SELECTED][1] = window::HALF_HEIGHT;
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
}
