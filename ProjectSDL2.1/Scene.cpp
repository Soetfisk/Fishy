#include "Scene.h"
#include "obj_loader.h"


void Scene::LoadModels()
{
	FSH_Loader.LoadScene("Models/tempfishTex.FSH"); //PlayerFish
	FSH_Loader.LoadScene("Models/Goldfish.FSH"); //PlayerFish
	
	for (int i = 0; i < 2; i++) {
		this->players.push_back(new GLPlayer(FSH_Loader, PlayerFish));
	}
	for (int i = 0; i < 50; i++) {
		this->NPCs.push_back(new GLNPC_GoldFish(FSH_Loader, GoldFish));
	}

	this->collisionHandler.AddNPC(NPCs);
	this->collisionHandler.AddPlayer(players);
	this->collisionHandler.AddModel(models);
}

void Scene::LoadModels(char * folder)
{
}

Scene::Scene() {
	
	LoadModels();
	
	this->players.at(1)->GetTransform().SetPos(glm::vec3(3, 3, 3));
	this->players.at(0)->GetTransform().SetPos(glm::vec3(0, 0, 0));
	
	shaders[MODELS] = new GLShader("test", true);
	shaders[PASS] = new GLShader("pass");
	shaders[TEXT] = new GLShader("text");
	shaders[WAVY] = new GLShader("wavy");
	shaders[POST] = new GLShader("post");
	shaders[LIGHTING] = new GLShader("lighting");

	guih = new GLGUIHandler(*shaders[TEXT]);

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
	//tempMesh->GetTransform().SetPos(glm::vec3(3, 0, 3));
	//first make vertex for all vertexes
	filterComputeShader = new FilterComputeShader("derp");
	filterComputeShader->LoadShader("blueFilter.glsl");
	filterComputeShader->CreateShader(filterComputeShader->LoadShader("blueFilter.glsl"));
	this->deltaTime = 0;

	//GLfloat fogColor[4] = { 1.0f,1.0f,1.0f,1.0f };

	//glFogi(GL_FOG_MODE, GL_LINEAR);
	//glFogfv(GL_FOG_COLOR, fogColor);
	//glFogf(GL_FOG_DENSITY, 1.0f);
	//glHint(GL_FOG_HINT, GL_DONT_CARE); glFogf(GL_FOG_START, 2.0f); // Fog Start Depth 
	//glFogf(GL_FOG_END, 8.0f); // Fog End Depth
	//glEnable(GL_FOG);
	//glEnable(GL_DEPTH_TEST);
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
	delete this->filterComputeShader;
	for (int i = 0; i < models.size(); i++)
	{
		delete models.at(i);
	}

	for (int i = 0; i < players.size(); i++)
	{
		delete players.at(i);
	}

	for (int i = 0; i < NPCs.size(); i++)
	{
		delete NPCs.at(i);
	}

	delete guih;
}

void Scene::Update(float& deltaTime) {
	this->deltaTime = deltaTime;

	guih->Update(deltaTime);

	this->collisionHandler.CheckCollisions(deltaTime);

	for (int i = 0; i < this->players.size(); i++) {
		this->players.at(i)->Update(GLPlayer::NOTHING ,glm::vec3(deltaTime));
		if (i == 0)
		{
			guih->AddScorePlayer1(this->players.at(i)->point);
			this->players.at(i)->point = 0;
		}
		else
		{
			guih->AddScorePlayer2(this->players.at(i)->point);
			this->players.at(i)->point = 0;
		}
	}

	for (int i = 0; i < this->NPCs.size(); i++) {
		this->NPCs.at(i)->NPCUpdate(deltaTime);
	}
}

//Loads the scene, models, matrices
void Scene::LoadScene() {

}

//Calls the models.draw
void Scene::DrawScene() {

	guih->Draw(*shaders[TEXT]);

	for (int i = 0; i < this->players.size(); i++) {
		//Set viewport
		glViewport(0, 0, window::WIDTH, window::HEIGHT/ 2);

		//for(int j = 0; j<this->models.count();j++){
		shaders[MODELS]->Bind();
		shaders[MODELS]->Update(players.at(i)->GetCamera());
		this->frameBuffer->BindFrameBuffer();

		//tempModel->Draw(*shaders[MODELS]);
		for (int j = 0; j < this->players.size(); j++) {
			players.at(j)->TestDraw(*shaders[MODELS]);
		}
		for (unsigned int i = 0; i < NPCs.size(); i++)
		{
			NPCs.at(i)->NPCDraw(*shaders[MODELS]);
		}
		this->frameBuffer->UnbindFrameBuffer();
		//models[0]->Draw(*shaders[MODELS]);
		//tempMesh->Draw(*shaders[MODELS], GLTransform());
		this->frameBuffer2->BindFrameBuffer();
		shaders[LIGHTING]->Bind();

		glUniform3fv(shaders[LIGHTING]->GetUnifromLocation("pointLights[" + std::to_string(0) + "].ambient"), 1, glm::value_ptr(glm::vec3(0.0f, 0.1f, 0.0f)));
		glUniform3fv(shaders[LIGHTING]->GetUnifromLocation("pointLights[" + std::to_string(0) + "].diffuse"), 1, glm::value_ptr(glm::vec3(0.65f, 0.0f, 1.0f)));
		glUniform3fv(shaders[LIGHTING]->GetUnifromLocation("pointLights[" + std::to_string(0) + "].position"), 1, glm::value_ptr(glm::vec3(-3, 0, -3)));
		glUniform3fv(shaders[LIGHTING]->GetUnifromLocation("pointLights[" + std::to_string(0) + "].specular"), 1, glm::value_ptr(glm::vec3(0.5f, 0.0f, 0.0f)));
		glUniform1f(shaders[LIGHTING]->GetUnifromLocation("pointLights[" + std::to_string(0) + "].constant"), 1.0f);
		glUniform1f(shaders[LIGHTING]->GetUnifromLocation("pointLights[" + std::to_string(0) + "].linear"), 0.045f);
		glUniform1f(shaders[LIGHTING]->GetUnifromLocation("pointLights[" + std::to_string(0) + "].quadratic"), 0.0075);

		glUniform3fv(shaders[LIGHTING]->GetUnifromLocation("ViewPos"), 1, glm::value_ptr(players.at(i)->GetCamera().Position()));

		glUniform3fv(shaders[LIGHTING]->GetUnifromLocation("dirLight.dir"), 1, glm::value_ptr(glm::vec3(0.5, 1, 0.5)));
		glUniform3fv(shaders[LIGHTING]->GetUnifromLocation("dirLight.ambient"), 1, glm::value_ptr(glm::vec3(0.1f, 0.1f, 0.1f)));
		glUniform3fv(shaders[LIGHTING]->GetUnifromLocation("dirLight.diffuse"), 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniform3fv(shaders[LIGHTING]->GetUnifromLocation("dirLight.specular"), 1, glm::value_ptr(glm::vec3(0.5f, 0.0f, 0.0f)));
		// IMPORTANT!!!!! projectiles do not have material and it is crashing
		this->frameBuffer->BindTexturesToProgram(shaders[LIGHTING]->GetUnifromLocation("colorTexture"), 0);
		this->frameBuffer->BindTexturesToProgram(shaders[LIGHTING]->GetUnifromLocation("posTexture"), 1);
		this->frameBuffer->BindTexturesToProgram(shaders[LIGHTING]->GetUnifromLocation("normalTexture"), 2);
		this->frameBuffer->BindTexturesToProgram(shaders[LIGHTING]->GetUnifromLocation("distTexture"), 3);
		this->frameBuffer->BindTexturesToProgram(shaders[LIGHTING]->GetUnifromLocation("ambientTexture"), 4);
		this->frameBuffer->BindTexturesToProgram(shaders[LIGHTING]->GetUnifromLocation("specularTexture"), 5);
		

		this->RenderQuad();
		this->frameBuffer2->UnbindFrameBuffer();
		//tempModel->Draw(*shaders[MODELS]);
		//shaders[PASS]->Bind();
		
		//this->filterComputeShader->BindShader();
		this->count += 0.5f * this->deltaTime;
		//this->frameBuffer->BindImageTexturesToProgram(glGetUniformLocation(this->cs, "destTex"), 0);
		//this->filterComputeShader->UniformVec3("colorVector",glm::vec3(0.0f,0.0f, 1.0f));
		//this->filterComputeShader->Uniform1f("number",count);
		//this->filterComputeShader->DispatchCompute(1024 / 32, 768 / 32, 1);
		

		this->frameBuffer3->BindFrameBuffer();
		shaders[POST]->Bind();
		shaders[POST]->Uniform1f("width", window::WIDTH);
		shaders[POST]->Uniform1f("height", window::HEIGHT / 2);
		this->frameBuffer2->BindTexturesToProgram(shaders[POST]->GetUnifromLocation("texture"), 0);
		this->RenderQuad();
		this->frameBuffer3->UnbindFrameBuffer();

		this->frameBuffer4->BindFrameBuffer();
		shaders[POST]->Bind();
		shaders[POST]->Uniform1f("width", window::WIDTH);
		shaders[POST]->Uniform1f("height", window::HEIGHT / 2);
		this->frameBuffer3->BindTexturesToProgram(shaders[POST]->GetUnifromLocation("texture"), 0);
		this->RenderQuad();
		this->frameBuffer4->UnbindFrameBuffer();

		this->frameBuffer5->BindFrameBuffer();
		shaders[WAVY]->Bind();
		shaders[WAVY]->Uniform1f("offset", count);
		this->frameBuffer2->BindTexturesToProgram(shaders[WAVY]->GetUnifromLocation("texture"), 0);
		this->RenderQuad();
		this->frameBuffer5->UnbindFrameBuffer();
		

		shaders[PASS]->Bind();
		this->frameBuffer2->BindTexturesToProgram(shaders[PASS]->GetUnifromLocation("texture"), 0);
		//this->frameBuffer->BindTexturesToProgram(shaders[PASS]->GetUnifromLocation("texture2"), 1);
		//this->frameBuffer->BindTexturesToProgram(shaders[PASS]->GetUnifromLocation("texture3"), 2);
		glViewport(0, window::HEIGHT - (window::HEIGHT / (i + 1)), window::WIDTH, window::HEIGHT / 2);
		this->RenderQuad();

		//shaders[MODELS].update(models.at(j), player.at(i).getCamera()); 
		//	models.at(j).draw(player.at(i).getCamera());
		//}
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

void Scene::HandleEvenet(SDL_Event* e) {

		if (e->type == SDL_CONTROLLERDEVICEADDED)
		{
			players.at(e->cdevice.which+1)->Update(GLPlayer::JOY_ADDED, glm::vec3(e->cdevice.which));
		}
		else if (e->type == SDL_CONTROLLERDEVICEREMOVED)
		{
			players.at(e->cdevice.which + 1)->Update(GLPlayer::JOY_REMOVED, glm::vec3(e->cdevice.which));
		}
		else if (e->type == SDL_CONTROLLERAXISMOTION)
		{
			switch (e->caxis.axis)
			{
			case SDL_CONTROLLER_AXIS_RIGHTX:
				players.at(e->caxis.which + 1)->Update(GLPlayer::CAMERA_MOVE, glm::vec3(e->caxis.value, 0, 0));
				break;
			case SDL_CONTROLLER_AXIS_RIGHTY:
				players.at(e->caxis.which + 1)->Update(GLPlayer::CAMERA_MOVE, glm::vec3(0, e->caxis.value, 0));
				break;
			case  SDL_CONTROLLER_AXIS_LEFTX:
				players.at(e->caxis.which + 1)->Update(GLPlayer::PLAYER_MOVE, glm::vec3(e->caxis.value, 0, 0));
				break;
			case SDL_CONTROLLER_AXIS_LEFTY:
				players.at(e->caxis.which + 1)->Update(GLPlayer::PLAYER_MOVE, glm::vec3(0, e->caxis.value, 0));
				break;
			case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
				players.at(e->caxis.which + 1)->Update(GLPlayer::PLAYER_MOVE, glm::vec3(0, 0, e->caxis.value));
				break;
			case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
				players.at(e->caxis.which + 1)->Update(GLPlayer::PLAYER_MOVE, glm::vec3(0, 0, -e->caxis.value));
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
				players.at(e->cbutton.which + 1)->Update(GLPlayer::PLAYER_SHOOT, glm::vec3(0));
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
				players.at(0)->Update(GLPlayer::CAMERA_MOVE, glm::vec3(0, 1, 0));
				break;
			case SDL_SCANCODE_DOWN:
				players.at(0)->Update(GLPlayer::CAMERA_MOVE, glm::vec3(0, 1, 0));
				break;
			case SDL_SCANCODE_LEFT:
				players.at(0)->Update(GLPlayer::CAMERA_MOVE, glm::vec3(1, 0, 0));
				break;
			case SDL_SCANCODE_RIGHT:
				players.at(0)->Update(GLPlayer::CAMERA_MOVE, glm::vec3(1, 0, 0));
				break;
			case SDL_SCANCODE_W:
				players.at(0)->Update(GLPlayer::PLAYER_MOVE, glm::vec3(0, 1, 0));
				break;
			case SDL_SCANCODE_S:
				players.at(0)->Update(GLPlayer::PLAYER_MOVE, glm::vec3(0, 1, 0));
				break;
			case SDL_SCANCODE_A:
				players.at(0)->Update(GLPlayer::PLAYER_MOVE, glm::vec3(1, 0, 0));
				break;
			case SDL_SCANCODE_D:
				players.at(0)->Update(GLPlayer::PLAYER_MOVE, glm::vec3(1, 0, 0));
				break;
			case SDL_SCANCODE_LSHIFT:
				players.at(0)->Update(GLPlayer::PLAYER_MOVE, glm::vec3(0, 0, 1));
				break;
			case SDL_SCANCODE_E:
				players.at(0)->Update(GLPlayer::PLAYER_DASH, glm::vec3(0, 0, 1));
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
				players.at(0)->Update(GLPlayer::PLAYER_SHOOT, glm::vec3(0));
				break;
			}
		}

		const Uint8* keyState = SDL_GetKeyboardState(NULL);
		if (keyState[SDL_SCANCODE_UP])
		{
			players.at(0)->Update(GLPlayer::CAMERA_MOVE, glm::vec3(0, -(glm::pow(2, 15)), 0));
		}
		if (keyState[SDL_SCANCODE_DOWN])
		{
			players.at(0)->Update(GLPlayer::CAMERA_MOVE, glm::vec3(0, (glm::pow(2, 15)), 0));
		}
		if (keyState[SDL_SCANCODE_LEFT])
		{
			players.at(0)->Update(GLPlayer::CAMERA_MOVE, glm::vec3((glm::pow(2, 15)), 0, 0));
		}
		if (keyState[SDL_SCANCODE_RIGHT])
		{
			players.at(0)->Update(GLPlayer::CAMERA_MOVE, glm::vec3(-(glm::pow(2, 15)), 0, 0));
		}
		if (keyState[SDL_SCANCODE_W])
		{
			players.at(0)->Update(GLPlayer::PLAYER_MOVE, glm::vec3(0, (glm::pow(2, 15)), 0));
		}
		if (keyState[SDL_SCANCODE_A])
		{
			players.at(0)->Update(GLPlayer::PLAYER_MOVE, glm::vec3(-(glm::pow(2, 15)), 0, 0));
		}
		if (keyState[SDL_SCANCODE_S])
		{
			players.at(0)->Update(GLPlayer::PLAYER_MOVE, glm::vec3(0, -(glm::pow(2, 15)), 0));
		}
		if (keyState[SDL_SCANCODE_D])
		{
			players.at(0)->Update(GLPlayer::PLAYER_MOVE, glm::vec3((glm::pow(2, 15)), 0, 0));
		}
		if (keyState[SDL_SCANCODE_E])
		{
			players.at(0)->Update(GLPlayer::PLAYER_DASH, glm::vec3(0, 0, (glm::pow(2, 15))));
		}
		if (keyState[SDL_SCANCODE_LSHIFT])
		{
			players.at(0)->Update(GLPlayer::PLAYER_MOVE, glm::vec3(0, 0, (glm::pow(2, 15))));
		}
}