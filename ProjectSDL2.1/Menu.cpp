#include "Menu.h"

Menu::Menu()
{
	menuShader = new GLShader("text");
	deleteShader = true;

	gui = new GUI();
	deleteGUI = true;

	gameState = nullptr;

	InitMenuTextureInfo();
	InitModels();

}

Menu::Menu(GLOBAL_GameState* state)
{
	menuShader = new GLShader("text");
	deleteShader = true;

	this->gui = new GUI();
	deleteGUI = true;

	gameState = state;

	InitMenuTextureInfo();
	InitModels();
}

Menu::Menu(GUI* gui, GLOBAL_GameState* state)
{
	menuShader = new GLShader("text");
	deleteShader = true;

	this->gui = gui;
	deleteGUI = false;

	gameState = state;

	InitMenuTextureInfo();
	InitModels();
}

Menu::Menu(GUI* gui, GLOBAL_GameState* state, GLShader* shader)
{
	menuShader = shader;
	deleteShader = false;

	this->gui = gui;
	deleteGUI = false;

	gameState = state;

	InitMenuTextureInfo();
	InitModels();
}

Menu::~Menu()
{
	if(deleteShader)
		delete menuShader;
	if(deleteGUI)
		delete gui;

	delete modelShader;
	delete model;
	delete aquarium;
	delete camera;
	FSH_Loader.clean();
	delete controlsTexture;
	delete textureToQuadShader;
	glDeleteTextures(1, &cTextureID);
}

void Menu::Update(float dt)
{
	model->GetTransform().m_rot.y += dt/2;
	model->UpdateModel();
}

void Menu::Draw()
{
	glViewport(0, 0, window::WIDTH, window::HEIGHT);
	
	modelShader->Bind();
	modelShader->Update(*camera);
	model->Draw(*modelShader);
	aquarium->Draw(*modelShader);

	if (currentMState == MENU)
	{
		projection = glm::ortho(0.0f, static_cast<GLfloat>(window::WIDTH), 0.0f, static_cast<GLfloat>(window::HEIGHT));
		menuShader->Bind();
		glUniformMatrix4fv(menuShader->GetUnifromLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));
		for (int i = 0; i < NUM_MENU_BUTTONS; i++)
			gui->RenderText(*menuShader, text[i], textPos[i][0], textPos[i][1], textScale[i], textColor[i]);
	}
	else
	{
		textureToQuadShader->Bind();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, cTextureID);
		RenderQuad();
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void Menu::HandleEvenet(SDL_Event * e)
{
	if (e->type == SDL_CONTROLLERAXISMOTION)
	{
		switch (e->caxis.axis)
		{
		case SDL_CONTROLLER_AXIS_LEFTY:
			if (e->caxis.value > 10000)
				HandleUp();
			else if (e->caxis.value < -10000)
				HandleDown();
			break;
		default:
			break;
		}
	}
	else if (e->type == SDL_CONTROLLERBUTTONDOWN)
	{
		switch (e->cbutton.button)
		{
		case SDL_CONTROLLER_BUTTON_DPAD_UP:
			HandleUp();
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
			HandleDown();
			break;
		case SDL_CONTROLLER_BUTTON_A:
			HandleSpace();
			break;
		default:
			break;
		}
	}
	else if (e->type == SDL_KEYDOWN)
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
			HandleSpace();
			break;
		case SDL_SCANCODE_RETURN:
			HandleSpace();
			break;
		default:
			break;
		}
	}
}

void Menu::InitMenuTextureInfo()
{
	projection = glm::ortho(0.0f, static_cast<GLfloat>(window::WIDTH), 0.0f, static_cast<GLfloat>(window::HEIGHT));
	menuShader->Bind();
	glUniformMatrix4fv(menuShader->GetUnifromLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_BLEND);

	quadVAO = 0;
	textureToQuadShader = new GLShader("pass");
	controlsTexture = FSH_Loader.loadTexure("./res/Controls.png");
	glGenTextures(1, &cTextureID);
	glBindTexture(GL_TEXTURE_2D, cTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, controlsTexture->width, controlsTexture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, controlsTexture->textureData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glUniform1i(textureToQuadShader->GetUnifromLocation("texture"), 0);

	currentMState = MENU;

	float tempY = window::QUARTER_HEIGHT;
	float extraOffset = 20;

	// Title
	text[TITLE] = "Survival of the fishest";
	textScale[TITLE] = 1.4f;
	textColor[TITLE] = glm::vec3(0, 1, 0);
	textPos[TITLE][0] = (float)(window::HALF_WIDTH - (gui->GetTextLenght(text[TITLE], textScale[TITLE]) * 0.5));
	tempY += gui->GetTextHeight(text[TITLE], textScale[TITLE]) + extraOffset;
	textPos[TITLE][1] = window::HEIGHT - tempY;

	// Start Game
	text[START_GAME] = "Start Game";
	textScale[START_GAME] = 1.0f;
	textColor[START_GAME] = glm::vec3(0, 1, 0);
	textPos[START_GAME][0] = (float)(window::HALF_WIDTH - (gui->GetTextLenght(text[START_GAME], textScale[START_GAME]) * 0.5));
	tempY += gui->GetTextHeight(text[START_GAME], textScale[START_GAME]) + extraOffset;
	textPos[START_GAME][1] = window::HEIGHT - tempY;

	// Rematch
	text[REMATCH] = "Rematch";
	textScale[REMATCH] = 1.0f;
	textColor[REMATCH] = glm::vec3(0, 1, 0);
	textPos[REMATCH][0] = (float)(window::HALF_WIDTH - (gui->GetTextLenght(text[REMATCH], textScale[REMATCH]) * 0.5));
	tempY += gui->GetTextHeight(text[REMATCH], textScale[REMATCH]) + extraOffset;
	textPos[REMATCH][1] = window::HEIGHT - tempY;

	// Controls
	text[CONTROLS] = "Controls";
	textScale[CONTROLS] = 1.0f;
	textColor[CONTROLS] = glm::vec3(0, 1, 0);
	textPos[CONTROLS][0] = (float)(window::HALF_WIDTH - (gui->GetTextLenght(text[CONTROLS], textScale[CONTROLS]) * 0.5));
	tempY += gui->GetTextHeight(text[CONTROLS], textScale[CONTROLS]) + extraOffset;
	textPos[CONTROLS][1] = window::HEIGHT - tempY;

	// Exit
	text[EXIT] = "Exit";
	textScale[EXIT] = 1.0f;
	textColor[EXIT] = glm::vec3(0, 1, 0);
	textPos[EXIT][0] = (float)(window::HALF_WIDTH - (gui->GetTextLenght(text[EXIT], textScale[EXIT]) * 0.5));
	tempY += gui->GetTextHeight(text[EXIT], textScale[EXIT]) + extraOffset;
	textPos[EXIT][1] = window::HEIGHT - tempY;

	// Selected
	text[SELECTED] = "$";
	textScale[SELECTED] = 1.0f;
	textColor[SELECTED] = glm::vec3(0, 1, 0);
	textPos[SELECTED][0] = (float)(window::HALF_WIDTH - gui->GetTextLenght(text[START_GAME], textScale[START_GAME]) * 0.5 - gui->GetTextLenght(text[SELECTED], textScale[SELECTED]) - 20);

	textPos[SELECTED][1] = textPos[START_GAME][1];
	selectedBttn = START_GAME;
}

void Menu::HandleUp()
{
	switch (selectedBttn)
	{
	case START_GAME:
		textScale[selectedBttn] = 1.0f;
		textPos[selectedBttn][0] = (float)(window::HALF_WIDTH - gui->GetTextLenght(text[selectedBttn], textScale[selectedBttn]) * 0.5);

		selectedBttn = EXIT;
		break;
	case REMATCH:
		textScale[selectedBttn] = 1.0f;
		textPos[selectedBttn][0] = (float)(window::HALF_WIDTH - gui->GetTextLenght(text[selectedBttn], textScale[selectedBttn]) * 0.5);

		selectedBttn = START_GAME;
		break;
	case CONTROLS:
		textScale[selectedBttn] = 1.0f;
		textPos[selectedBttn][0] = (float)(window::HALF_WIDTH - gui->GetTextLenght(text[selectedBttn], textScale[selectedBttn]) * 0.5);

		selectedBttn = REMATCH;
		break;
	case EXIT:
		textScale[selectedBttn] = 1.0f;
		textPos[selectedBttn][0] = (float)(window::HALF_WIDTH - gui->GetTextLenght(text[selectedBttn], textScale[selectedBttn]) * 0.5);

		selectedBttn = CONTROLS;
		break;
	default:
		std::cout << "MENUSTATE ERROR FOR SELECTEDBTTN IN HandleUp()!\n";
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
		textPos[selectedBttn][0] = (float)(window::HALF_WIDTH - gui->GetTextLenght(text[selectedBttn], textScale[selectedBttn]) * 0.5);

		selectedBttn = REMATCH;
		break;
	case REMATCH:
		textScale[selectedBttn] = 1.0f;
		textPos[selectedBttn][0] = (float)(window::HALF_WIDTH - gui->GetTextLenght(text[selectedBttn], textScale[selectedBttn]) * 0.5);

		selectedBttn = CONTROLS;
		break;
	case CONTROLS:
		textScale[selectedBttn] = 1.0f;
		textPos[selectedBttn][0] = (float)(window::HALF_WIDTH - gui->GetTextLenght(text[selectedBttn], textScale[selectedBttn]) * 0.5);

		selectedBttn = EXIT;
		break;
	case EXIT:
		textScale[selectedBttn] = 1.0f;
		textPos[selectedBttn][0] = (float)(window::HALF_WIDTH - gui->GetTextLenght(text[selectedBttn], textScale[selectedBttn]) * 0.5);

		selectedBttn = START_GAME;
		break;
	default:
		std::cout << "MENUSTATE ERROR FOR SELECTEDBTTN IN HandleDown()!\n";
		break;
	}

	FixSelected();
}

void Menu::HandleSpace()
{
	switch (selectedBttn)
	{
	case START_GAME:
		*gameState = GLOBAL_GameState::RESET_ROUNDS;
		break;
	case REMATCH:
		*gameState = GLOBAL_GameState::GAME;
		break;
	case CONTROLS:
		if (currentMState == MENU)
			currentMState = SHOW_CONTROLS;
		else
			currentMState = MENU;
		break;
	case EXIT:
		*gameState = GLOBAL_GameState::EXIT;
		break;
	default:
		std::cout << "MENUSTATE ERROR FOR SELECTEDBTTN IN HandleSpace()!\n";
		break;
	}
}

void Menu::FixSelected()
{
	textScale[selectedBttn] = 1.2f;
	textPos[selectedBttn][0] = (float)(window::HALF_WIDTH - gui->GetTextLenght(text[selectedBttn], textScale[selectedBttn]) * 0.5);
	textPos[SELECTED][0] = (float)(window::HALF_WIDTH - gui->GetTextLenght(text[selectedBttn], textScale[selectedBttn]) * 0.5 - gui->GetTextLenght(text[SELECTED], textScale[SELECTED]) - 20);
	textPos[SELECTED][1] = textPos[selectedBttn][1];
}

void Menu::InitModels()
{
	FSH_Loader.LoadScene("Models/fishy.FSH"); //PlayerFish
	FSH_Loader.LoadScene("Models/GoldFishBlend.FSH"); //GoldFish
	FSH_Loader.LoadScene("Models/BlueTang.FSH"); //BlueTang
	FSH_Loader.LoadScene("Models/AquariumRedux.FSH"); //Aquarium

	srand((unsigned int)time(0));
	model = new GLModel(&FSH_Loader, rand() % 3);
	aquarium = new GLModel(&FSH_Loader, Aquarium);
	model->GetTransform().m_pos.z = 5;

	modelShader = new GLShader("draw");
	camera = new GLCamera(glm::vec3(0), 70, window::WIDTH/window::HEIGHT, 0.01f, 1000.0f);
}

void Menu::RenderQuad()
{
	if (quadVAO == 0) //init
	{
		GLfloat quadVertices[] = {
			// Positions        // Texture Coords
			-1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			1.0f, -1.0f, 0.0f, 1.0f, 1.0f,
		};
		// Setup plane VAO
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	}
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}
