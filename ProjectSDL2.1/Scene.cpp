#include "Scene.h"


void Scene::Init()
{
	
	// set player position and rotation to the correct startpositions
	this->players.at(1)->GetTransform().SetPos(glm::vec3(100, 0, 0));
	this->players.at(1)->GetTransform().SetRot(glm::vec3(0, -1.58, 0));
	this->players.at(0)->GetTransform().SetPos(glm::vec3(-100, 0, 0));
	this->players.at(0)->GetTransform().SetRot(glm::vec3(0, 1.58, 0));
	this->staticMeshes.at(0)->GetTransform().SetPos(glm::vec3(0, 0, 0));

	// load the shaders
	shaders[MODELS] = new GLShader("test", true);
	shaders[PASS] = new GLShader("pass");
	shaders[TEXT] = new GLShader("text");
	shaders[WAVY] = new GLShader("wavy");
	shaders[BORDER] = new GLShader("post");
	shaders[LIGHTING] = new GLShader("lighting");
	shaders[BLEND_SHAPE] = new GLShader("blend_shape", true);

	// init all the framebuffers
	this->frameBuffer = new FrameBuffer();
	this->frameBuffer->CreateFrameBuffer(6, SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGBA16F);
	this->frameBuffer->UnbindFrameBuffer();

	this->frameBuffer2 = new FrameBuffer();
	this->frameBuffer2->CreateFrameBuffer(1, SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGB);
	this->frameBuffer2->UnbindFrameBuffer();

	this->frameBuffer3 = new FrameBuffer();
	this->frameBuffer3->CreateFrameBuffer(1, SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGB);
	this->frameBuffer3->UnbindFrameBuffer();

	this->frameBuffer4 = new FrameBuffer();
	this->frameBuffer4->CreateFrameBuffer(1, SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGB);
	this->frameBuffer4->UnbindFrameBuffer();

	this->frameBuffer5 = new FrameBuffer();
	this->frameBuffer5->CreateFrameBuffer(1, SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGB);
	this->frameBuffer5->UnbindFrameBuffer();

	// computeshader off cus crash
	/*filterComputeShader = new FilterComputeShader("derp");
	filterComputeShader->LoadShader("blueFilter.glsl");
	filterComputeShader->CreateShader(filterComputeShader->LoadShader("blueFilter.glsl"));*/

	// lights
	PointLight light1;
	light1.ambient = glm::vec3(0.0f, 0.1f, 0.0f);
	light1.diffuse = glm::vec3(0.65f, 0.0f, 1.0f);
	light1.position = glm::vec3(-3, 0, -3);
	light1.specular = glm::vec3(0.5f, 0.0f, 0.0f);
	light1.constant = 1.0f;
	light1.linear = 0.045f;
	light1.quadratic = 0.0075f;

	this->pointLights.push_back(light1);

	dirLight.ambient = glm::vec3(0.25, 0.61, 1);
	dirLight.diffuse = glm::vec3(0.25, 0.61, 1);
	dirLight.specular = glm::vec3(0.25, 0.61, 1);
	dirLight.dir = glm::vec3(0.01, 1, 0.01);

	this->deltaTime = 0;
	// border shader variables
	this->borderThreshold1 = 0.9f; // variable one must be the bigger otherwise the second will just overwrite it
	this->borderThreshold2 = 0.9f; // values should be between 0-1
	this->borderColor1 = glm::vec3(0, 0, 0);
	// wavy variables
	this->wavyAmount = 0.3f; // how fast the waves will go, higher = faster. Standard = 1
	this->wavyLength = 1.0f; // how long the waves are. Lower = longer waves. standard = 1
							 //fog variables
	this->fogStart = 50.f;
	this->fogEnd = 210.f;
	this->fogColor = glm::vec3(0.1, 0.1, 0.8);
	//player
	this->currentPowerUp = GLPlayer::POWER_NEUTRAL;
	// Ending game options
	this->endTimer = 60;
	this->endScore = 1000;


}

void Scene::LoadModels()
{
	FSH_Loader.LoadScene("Models/fishy.FSH"); //PlayerFish
	FSH_Loader.LoadScene("Models/Goldfish.FSH"); //GoldFish
	FSH_Loader.LoadScene("Models/BlueTang.FSH"); //BlueTang
	FSH_Loader.LoadScene("Models/Bubble2.FSH"); //Bubble
	FSH_Loader.LoadScene("Models/tempAquarium.FSH"); //Aquarium
	FSH_Loader.LoadScene("Models/weed2.FSH"); //SeaWeedLeaf

	
	for (int i = 0; i < 2; i++) {
		this->players.push_back(new GLPlayer(&FSH_Loader, PlayerFish, Bubble));
	}
	for (int i = 0; i < 20; i++) {
		this->NPCs.push_back(new GLNPC_GoldFish(&FSH_Loader, GoldFish));
	}
	for (int i = 0; i < 10; i++) {
		this->NPCs.push_back(new GLNPC_BlueTang(&FSH_Loader, BlueTang));
		this->NPCs.at(i)->GetTransform().SetScale(glm::vec3(2));
	}
	
	this->staticMeshes.push_back(new GLModel(&FSH_Loader, Aquarium));
	this->staticMeshes.push_back(new GLModel(&FSH_Loader, Bubble));
	this->staticMeshes.push_back(new GLModel(&FSH_Loader, Bubble));

	this->specialStaticMeshes.push_back(new SeaWeedLeafs(&FSH_Loader, SeaWeedLeaf));

	this->collisionHandler.AddNPC(NPCs);
	this->collisionHandler.AddPlayer(players);
	this->collisionHandler.AddModel(models);
	this->collisionHandler.InitiatePowerUpHandler();

}

void Scene::LoadModels(char * folder)
{
}

// update currentPowerup variable with value from player i
void Scene::UpdatePlayerPowerUp(int player)
{
	this->currentPowerUp = this->players.at(player)->GetPowerUp();
}

// do stuff with curentPowerup variable
void Scene::HandlePlayerPowerUp()
{
	if (this->currentPowerUp == GLPlayer::POWER_HIGH)
	{
		this->wavyAmount = 10;
		this->wavyLength = 0.5f; // how long the waves are. Lower = longer waves. standard = 1
		this->fogColor = glm::vec3(0.3,0.7,0.3);
		this->fogStart = 1.0f;
		this->fogEnd = 35.0f;
	}
	else
	{
		this->wavyAmount = 0.3f; // how fast the waves will go, higher = faster. Standard = 1
		this->wavyLength = 1.0f; // how long the waves are. Lower = longer waves. standard = 1
		this->fogColor = glm::vec3(0.1,0.1,0.8);
		this->fogStart = 50.f;
		this->fogEnd = 210.f;
	}
}

void Scene::CheckWinner()
{
	// if the timer is out or either player has winning amount of points and no one has won yet
	if (!this->winner && (this->guih->GetTime() >= this->endTimer || this->players.at(0)->GetTotalPoints() >= this->endScore || this->players.at(1)->GetTotalPoints() >= this->endScore))
	{
		this->winner = true;
		
		if (this->players.at(0)->GetTotalPoints() == this->players.at(1)->GetTotalPoints())
			this->guih->Tie();
		else if (this->players.at(0)->GetTotalPoints() > this->players.at(1)->GetTotalPoints())
			this->guih->Player1Won();
		else
			this->guih->Player2Won();
	}
	
	// if we have a winner
	if (this->winner)
	{
		// add to endSceneTimer which will end the scene in a certain amount of time
		this->endSceneTimer += this->deltaTime;
		if (this->endSceneTimer > 3)
		{
			*this->gameState = GLOBAL_GameState::MENU;
			this->ResetScene();
		}		
	}
}

void Scene::AddScore()
{
	this->CheckWinner();
	for (unsigned int i = 0; i < this->players.size(); i++) {
		this->players.at(i)->Update(GLPlayer::NOTHING, glm::vec3(deltaTime));
		if (i == 0)
		{
			guih->AddScorePlayer1(this->players.at(i)->GetPoints());
		}
		else
		{
			guih->AddScorePlayer2(this->players.at(i)->GetPoints());
		}
	}
}

Scene::Scene(GLOBAL_GameState* gameState) {
	LoadModels();
	Init();

	guih = new GLGUIHandler();
	this->gameState = gameState;

}

Scene::Scene(GUI* textToScreen, GLOBAL_GameState* gameState)
{
	LoadModels();
	Init();

	guih = new GLGUIHandler(shaders[TEXT], textToScreen);
	this->gameState = gameState;
}


Scene::~Scene(){
	for (int i = 0; i < NUM_SHADERS; i++) {
		delete shaders[i];
	}
	
	delete this->frameBuffer;
	delete this->frameBuffer2;
	delete this->frameBuffer3;
	delete this->frameBuffer4;
	delete this->frameBuffer5;
	//delete this->filterComputeShader;
	for (size_t i = 0; i < models.size(); i++)
	{
		delete models.at(i);
	}

	for (size_t i = 0; i < players.size(); i++)
	{
		delete players.at(i);
	}

	for (size_t i = 0; i < NPCs.size(); i++)
	{
		delete NPCs.at(i);
	}
	for (size_t i = 0; i < staticMeshes.size(); i++)
	{
		delete staticMeshes.at(i);
	}
	for (int i = 0; i < specialStaticMeshes.size(); i++)
	{
		delete specialStaticMeshes.at(i);
	}

	delete guih;
}

void Scene::Update(float& deltaTime) {
	this->deltaTime = deltaTime;

	guih->Update(deltaTime);

	this->collisionHandler.CheckCollisions(deltaTime);
	this->AddScore();

	for (size_t i = 0; i < this->NPCs.size(); i++)
		this->NPCs.at(i)->NPCUpdate(deltaTime);

	for (size_t i = 0; i < this->players.size(); i++)
		this->players.at(i)->Update(this->deltaTime);
}

//Loads the scene, models, matrices
void Scene::LoadScene() {

}

//Calls the models.draw
void Scene::DrawScene() {
	guih->Draw();

	for (size_t i = 0; i < this->players.size(); i++) {
		// handle player powerup
		this->UpdatePlayerPowerUp(i);
		this->HandlePlayerPowerUp();
		//Set viewport
		glViewport(0, 0, window::WIDTH, window::HEIGHT/ 2);

		shaders[BLEND_SHAPE]->Bind();
		shaders[BLEND_SHAPE]->Update(players.at(i)->GetCamera());
		this->frameBuffer->BindFrameBuffer();

		for (size_t j = 0; j < this->players.size(); j++)
		{
			players.at(j)->TestDraw(*shaders[BLEND_SHAPE]);
			shaders[BLEND_SHAPE]->Uniform1ui("BlendShapeCount", (GLuint)players.at(j)->GetBlendShapeCount());
			shaders[BLEND_SHAPE]->Uniform1fv("Weights", players.at(j)->GetBlendWeights());
		}
		shaders[MODELS]->Bind();
		shaders[MODELS]->Update(players.at(i)->GetCamera());
		for (int j = 0; j < this->players.size(); j++)
		{
			players.at(j)->DrawProjectile(*shaders[MODELS]);
		}
		for (size_t i = 0; i < NPCs.size(); i++)
		{
			NPCs.at(i)->NPCDraw(*shaders[MODELS]);
		}
		for (size_t i = 0; i < staticMeshes.size(); i++)
		{
			staticMeshes.at(i)->Draw(*shaders[MODELS]);
		}
		for (unsigned int i = 0; i < specialStaticMeshes.size(); i++)
		{
			specialStaticMeshes.at(i)->Draw(*shaders[MODELS]);
		}
		this->frameBuffer->UnbindFrameBuffer();
		this->frameBuffer2->BindFrameBuffer();
		shaders[LIGHTING]->Bind();

		for (size_t i = 0; i < pointLights.size(); i++)
		{
			glUniform3fv(shaders[LIGHTING]->GetUnifromLocation("pointLights[" + std::to_string(i) + "].ambient"), 1, glm::value_ptr(pointLights.at(i).ambient));
			glUniform3fv(shaders[LIGHTING]->GetUnifromLocation("pointLights[" + std::to_string(i) + "].diffuse"), 1, glm::value_ptr(pointLights.at(i).diffuse));
			glUniform3fv(shaders[LIGHTING]->GetUnifromLocation("pointLights[" + std::to_string(i) + "].position"), 1, glm::value_ptr(pointLights.at(i).position));
			glUniform3fv(shaders[LIGHTING]->GetUnifromLocation("pointLights[" + std::to_string(i) + "].specular"), 1, glm::value_ptr(pointLights.at(i).specular));
			glUniform1f(shaders[LIGHTING]->GetUnifromLocation("pointLights[" + std::to_string(i) + "].constant"), pointLights.at(i).constant);
			glUniform1f(shaders[LIGHTING]->GetUnifromLocation("pointLights[" + std::to_string(i) + "].linear"), pointLights.at(i).linear);
			glUniform1f(shaders[LIGHTING]->GetUnifromLocation("pointLights[" + std::to_string(i) + "].quadratic"), pointLights.at(i).quadratic);
		}

		glUniform3fv(shaders[LIGHTING]->GetUnifromLocation("dirLight.dir"), 1, glm::value_ptr(dirLight.dir));
		glUniform3fv(shaders[LIGHTING]->GetUnifromLocation("dirLight.ambient"), 1, glm::value_ptr(dirLight.ambient));
		glUniform3fv(shaders[LIGHTING]->GetUnifromLocation("dirLight.diffuse"), 1, glm::value_ptr(dirLight.diffuse));
		glUniform3fv(shaders[LIGHTING]->GetUnifromLocation("dirLight.specular"), 1, glm::value_ptr(dirLight.specular));

		glUniform3fv(shaders[LIGHTING]->GetUnifromLocation("ViewPos"), 1, glm::value_ptr(players.at(i)->GetCamera().Position()));

		shaders[LIGHTING]->Uniform1f("fogStartFloat",this->fogStart);
		shaders[LIGHTING]->Uniform1f("fogEndFloat", this->fogEnd);
		shaders[LIGHTING]->UniformVec3("fogColorVector",this->fogColor);
		this->frameBuffer->BindTexturesToProgram(shaders[LIGHTING]->GetUnifromLocation("colorTexture"), 0);
		this->frameBuffer->BindTexturesToProgram(shaders[LIGHTING]->GetUnifromLocation("posTexture"), 1);
		this->frameBuffer->BindTexturesToProgram(shaders[LIGHTING]->GetUnifromLocation("normalTexture"), 2);
		this->frameBuffer->BindTexturesToProgram(shaders[LIGHTING]->GetUnifromLocation("distTexture"), 3);
		this->frameBuffer->BindTexturesToProgram(shaders[LIGHTING]->GetUnifromLocation("ambientTexture"), 4);
		this->frameBuffer->BindTexturesToProgram(shaders[LIGHTING]->GetUnifromLocation("specularTexture"), 5);
		

		this->RenderQuad();
		this->frameBuffer2->UnbindFrameBuffer();
		

		this->frameBuffer3->BindFrameBuffer();
		shaders[BORDER]->Bind();
		shaders[BORDER]->Uniform1f("width", (float)window::WIDTH);
		shaders[BORDER]->Uniform1f("height", (float)(window::HEIGHT / 2));
		shaders[BORDER]->Uniform1f("thresholdFloat",this->borderThreshold1);
		shaders[BORDER]->UniformVec3("borderColor",this->borderColor1);
		this->frameBuffer2->BindTexturesToProgram(shaders[BORDER]->GetUnifromLocation("texture"), 0);
		this->RenderQuad();
		this->frameBuffer3->UnbindFrameBuffer();

		this->frameBuffer4->BindFrameBuffer();
		shaders[BORDER]->Bind();
		shaders[BORDER]->Uniform1f("width", (float)window::WIDTH);
		shaders[BORDER]->Uniform1f("height", (float)(window::HEIGHT / 2));
		shaders[BORDER]->Uniform1f("thresholdFloat", this->borderThreshold2);
		shaders[BORDER]->UniformVec3("borderColor", this->borderColor1);
		this->frameBuffer3->BindTexturesToProgram(shaders[BORDER]->GetUnifromLocation("texture"), 0);
		this->RenderQuad();
		this->frameBuffer4->UnbindFrameBuffer();

		this->count[i] += this->wavyAmount * this->deltaTime;
		this->frameBuffer5->BindFrameBuffer();
		shaders[WAVY]->Bind();
		shaders[WAVY]->Uniform1f("offset", count[i]);
		shaders[WAVY]->Uniform1f("waveLength", this->wavyLength);
		this->frameBuffer4->BindTexturesToProgram(shaders[WAVY]->GetUnifromLocation("texture"), 0);
		this->RenderQuad();
		this->frameBuffer5->UnbindFrameBuffer();
		

		shaders[PASS]->Bind();
		this->frameBuffer5->BindTexturesToProgram(shaders[PASS]->GetUnifromLocation("texture"), 0);
		glViewport(0, (GLint)(window::HEIGHT - (window::HEIGHT *(.5*(i + 1)))), (GLint)window::WIDTH, (GLint)(window::HEIGHT / 2));
		this->RenderQuad();
	}

}

void Scene::RenderQuad()
{
	if (quadVAO == 0) //init
	{
		GLfloat quadVertices[] = {
			// Positions        // Texture Coords
			-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
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

void Scene::ResetScene()
{
	for (size_t i = 0; i < NPCs.size(); i++)
	{
		NPCs.at(i)->ResetFish();
	}
	guih->Reset();
	for (size_t i = 0; i < players.size(); i++)
	{
		players.at(i)->ResetPlayer();
	}
	this->players.at(1)->GetTransform().SetPos(glm::vec3(100, 0, 0));
	this->players.at(1)->GetTransform().SetRot(glm::vec3(0, -1.58, 0));
	this->players.at(0)->GetTransform().SetPos(glm::vec3(-100, 0, 0));
	this->players.at(0)->GetTransform().SetRot(glm::vec3(0, 1.58, 0));
	this->staticMeshes.at(0)->GetTransform().SetPos(glm::vec3(0, 0, 0));
	this->endSceneTimer = 0;
	this->endGame = false;
	this->winner = false;
	this->guih->Reset();
}

void Scene::HandleEvenet(SDL_Event* e) {

		if (e->type == SDL_CONTROLLERDEVICEADDED)
		{
			players.at(e->cdevice.which)->Update(GLPlayer::JOY_ADDED, glm::vec3((float)e->cdevice.which));
		}
		else if (e->type == SDL_CONTROLLERDEVICEREMOVED)
		{
			players.at(e->cdevice.which)->Update(GLPlayer::JOY_REMOVED, glm::vec3((float)e->cdevice.which));
		}
		else if (e->type == SDL_CONTROLLERAXISMOTION)
		{
			switch (e->caxis.axis)
			{
			case SDL_CONTROLLER_AXIS_RIGHTX:
				players.at(e->caxis.which)->Update(GLPlayer::CAMERA_MOVE, glm::vec3(e->caxis.value, 0, 0));
				break;
			case SDL_CONTROLLER_AXIS_RIGHTY:
				players.at(e->caxis.which)->Update(GLPlayer::CAMERA_MOVE, glm::vec3(0, e->caxis.value, 0));
				break;
			case  SDL_CONTROLLER_AXIS_LEFTX:
				players.at(e->caxis.which)->Update(GLPlayer::PLAYER_MOVE, glm::vec3(e->caxis.value, 0, 0));
				break;
			case SDL_CONTROLLER_AXIS_LEFTY:
				players.at(e->caxis.which)->Update(GLPlayer::PLAYER_MOVE, glm::vec3(0, e->caxis.value, 0));
				break;
			case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
				players.at(e->caxis.which)->Update(GLPlayer::PLAYER_MOVE, glm::vec3(0, 0, e->caxis.value));
				break;
			case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
				players.at(e->caxis.which)->Update(GLPlayer::PLAYER_MOVE, glm::vec3(0, 0, -e->caxis.value));
				break;
			default:
				break;
			}
		}
		else if (e->type == SDL_CONTROLLERBUTTONDOWN)
		{
			switch (e->cbutton.button)
			{
			case SDL_CONTROLLER_BUTTON_A:
				players.at(e->cbutton.which)->Update(GLPlayer::PLAYER_SHOOT, glm::vec3(0));
				break;
			case SDL_CONTROLLER_BUTTON_B:
				players.at(e->cbutton.which)->Update(GLPlayer::PLAYER_DASH, glm::vec3(0));
				break;
			default:
				break;
			}
		}
		else if (e->type == SDL_KEYUP)
		{
			switch (e->key.keysym.scancode)
			{
			case SDL_SCANCODE_UP:
				players.at(1)->Update(GLPlayer::CAMERA_MOVE, glm::vec3(0, 1, 0));
				break;
			case SDL_SCANCODE_DOWN:
				players.at(1)->Update(GLPlayer::CAMERA_MOVE, glm::vec3(0, 1, 0));
				break;
			case SDL_SCANCODE_LEFT:
				players.at(1)->Update(GLPlayer::CAMERA_MOVE, glm::vec3(1, 0, 0));
				break;
			case SDL_SCANCODE_RIGHT:
				players.at(1)->Update(GLPlayer::CAMERA_MOVE, glm::vec3(1, 0, 0));
				break;
			case SDL_SCANCODE_W:
				players.at(1)->Update(GLPlayer::PLAYER_MOVE, glm::vec3(0, 1, 0));
				break;
			case SDL_SCANCODE_S:
				players.at(1)->Update(GLPlayer::PLAYER_MOVE, glm::vec3(0, 1, 0));
				break;
			case SDL_SCANCODE_A:
				players.at(1)->Update(GLPlayer::PLAYER_MOVE, glm::vec3(1, 0, 0));
				break;
			case SDL_SCANCODE_D:
				players.at(1)->Update(GLPlayer::PLAYER_MOVE, glm::vec3(1, 0, 0));
				break;
			case SDL_SCANCODE_LSHIFT:
				players.at(1)->Update(GLPlayer::PLAYER_MOVE, glm::vec3(0, 0, 1));
				break;
			case SDL_SCANCODE_E:
				players.at(1)->Update(GLPlayer::PLAYER_DASH, glm::vec3(0, 0, 1));
				break;
			case SDL_SCANCODE_H:
				players.at(1)->SetPowerUp(GLPlayer::POWER_HIGH);
				guih->Player2SetPowerUp(GLGUIHandler::PlayerPowerUpText::HIGH);
				break;
			case SDL_SCANCODE_Y:
				players.at(1)->SetPowerUp(GLPlayer::POWER_NEUTRAL);
				guih->Player2SetPowerUp(GLGUIHandler::PlayerPowerUpText::NOTHING);
				break;
			case SDL_SCANCODE_J:
				players.at(1)->SetPowerUp(GLPlayer::POWER_BUBBLESHOTGUN);
				guih->Player2SetPowerUp(GLGUIHandler::PlayerPowerUpText::SHOTGUN);
				break;
			case SDL_SCANCODE_K:
				players.at(1)->SetPowerUp(GLPlayer::POWER_BUBBLEBIG);
				guih->Player2SetPowerUp(GLGUIHandler::PlayerPowerUpText::BIG);
				break;
			case SDL_SCANCODE_L:
				ResetScene();
				break;
			default:
				break;
			}
		}
		else if (e->type == SDL_KEYDOWN)
		{
			switch (e->key.keysym.scancode)
			{
			case SDL_SCANCODE_SPACE:
				players.at(1)->Update(GLPlayer::PLAYER_SHOOT, glm::vec3(0));
				break;
			}
		}

		const Uint8* keyState = SDL_GetKeyboardState(NULL);
		if (keyState[SDL_SCANCODE_UP])
		{
			players.at(1)->Update(GLPlayer::CAMERA_MOVE, glm::vec3(0, -(glm::pow(2, 15)), 0));
		}
		if (keyState[SDL_SCANCODE_DOWN])
		{
			players.at(1)->Update(GLPlayer::CAMERA_MOVE, glm::vec3(0, (glm::pow(2, 15)), 0));
		}
		if (keyState[SDL_SCANCODE_LEFT])
		{
			players.at(1)->Update(GLPlayer::CAMERA_MOVE, glm::vec3((glm::pow(2, 15)), 0, 0));
		}
		if (keyState[SDL_SCANCODE_RIGHT])
		{
			players.at(1)->Update(GLPlayer::CAMERA_MOVE, glm::vec3(-(glm::pow(2, 15)), 0, 0));
		}
		if (keyState[SDL_SCANCODE_W])
		{
			players.at(1)->Update(GLPlayer::PLAYER_MOVE, glm::vec3(0, (glm::pow(2, 15)), 0));
		}
		if (keyState[SDL_SCANCODE_A])
		{
			players.at(1)->Update(GLPlayer::PLAYER_MOVE, glm::vec3(-(glm::pow(2, 15)), 0, 0));
		}
		if (keyState[SDL_SCANCODE_S])
		{
			players.at(1)->Update(GLPlayer::PLAYER_MOVE, glm::vec3(0, -(glm::pow(2, 15)), 0));
		}
		if (keyState[SDL_SCANCODE_D])
		{
			players.at(1)->Update(GLPlayer::PLAYER_MOVE, glm::vec3((glm::pow(2, 15)), 0, 0));
		}
		if (keyState[SDL_SCANCODE_E])
		{
			players.at(1)->Update(GLPlayer::PLAYER_DASH, glm::vec3(0, 0, (glm::pow(2, 15))));
		}
		if (keyState[SDL_SCANCODE_LSHIFT])
		{
			players.at(1)->Update(GLPlayer::PLAYER_MOVE, glm::vec3(0, 0, (glm::pow(2, 15))));
		}
}