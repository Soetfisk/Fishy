#include "Scene.h"
#include "obj_loader.h"
#include "AABB.h"


void Scene::LoadModels()
{
	//models.push_back(new GLModel(FSH_Loader, "Models/tempfish.FSH"));
}

void Scene::LoadModels(char * folder)
{
}

Scene::Scene() {
	
	for (int i = 0; i < 2; i++) {
		this->players.push_back(new GLPlayer(FSH_Loader, "Models/tempfish.FSH"));
	}

	
	for (int i = 0; i < 60; i++) {
		this->NPCs.push_back(new GLNPC(FSH_Loader, "Models/tempfish.FSH"));
	}
	shaders[MODELS] = new GLShader("test");
	shaders[PASS] = new GLShader("pass");

	LoadModels();

	

	this->frameBuffer = new FrameBuffer();
	this->frameBuffer->CreateFrameBuffer(3, SCREEN_WIDTH, SCREEN_HEIGHT);
	this->frameBuffer->UnbindFrameBuffer();
	//tempMesh->GetTransform().SetPos(glm::vec3(3, 0, 3));
	//first make vertex for all vertexes
	filterComputeShader = new FilterComputeShader("derp");
	filterComputeShader->LoadShader("blueFilter.glsl");
	filterComputeShader->CreateShader(filterComputeShader->LoadShader("blueFilter.glsl"));
	this->deltaTime = 0;
}


Scene::~Scene(){
	for (int i = 0; i < NUM_SHADERS; i++) {
		delete shaders[i];
	}
	
	delete this->frameBuffer;
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
}

void Scene::Update(float& deltaTime) {
	this->deltaTime = deltaTime;
	for (int i = 0; i < this->players.size(); i++) {
		this->players.at(i)->Update(GLPlayer::NOTHING ,glm::vec3(deltaTime));
	}

	for (int i = 0; i < this->NPCs.size(); i++) {
		this->NPCs.at(i)->NPCUpdate(deltaTime);

		float PHD = players.at(0)->GetTransform().GetScale().y/2;

		AABB a(NPCs.at(i)->GetTransform().GetPos(), glm::vec3(0.5f, 0.5f, 1));
		AABB NpcSeenSpace(NPCs.at(i)->GetTransform().GetPos(), glm::vec3(5, 5, 5));
		//AABB b(players.at(0)->GetTransform().GetPos(), glm::vec3(0.5f, 0.5f, 0.5f));
		AABB b(players.at(0)->GetTransform().GetPos(), glm::vec3(PHD, PHD, PHD));
		if (a.containsAABB(b))
		{
			
			NPCs.at(i)->gettingEaten(deltaTime);
			players.at(0)->PlayerEating(deltaTime);

			if (NPCs.at(i)->GetTransform().GetScale().y<0.2)
			{
				delete NPCs.at(i);
				NPCs.erase(NPCs.begin() + i);
			}
			
		}
		else if (NpcSeenSpace.containsAABB(b))
		{
			NPCs.at(i)->initiateFleeingState(players.at(0)->GetForward() );
		}
	}

	

	//std::cout << deltaTime << std::endl;
}

//Loads the scene, models, matrices
void Scene::LoadScene() {

}

//Calls the models.draw
void Scene::DrawScene() {
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
		
	
		//models[0]->Draw(*shaders[MODELS]);
		//tempMesh->Draw(*shaders[MODELS], GLTransform());

		


		//tempModel->Draw(*shaders[MODELS]);
		//shaders[PASS]->Bind();
		this->frameBuffer->UnbindFrameBuffer();
		this->filterComputeShader->BindShader();
		this->count += 0.1f * this->deltaTime;
		this->frameBuffer->BindImageTexturesToProgram(glGetUniformLocation(this->cs, "destTex"), 0);
		this->filterComputeShader->UniformVec3("colorVector",glm::vec3(0.0f,0.0f, 1.0f));
		this->filterComputeShader->Uniform1f("number",count);
		//this->filterComputeShader->DispatchCompute(1024 / 32, 768 / 32, 1);
		
		shaders[PASS]->Bind();
		this->frameBuffer->BindTexturesToProgram(shaders[PASS]->GetUnifromLocation("texture"), 0);
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
		if (keyState[SDL_SCANCODE_LSHIFT])
		{
			players.at(0)->Update(GLPlayer::PLAYER_MOVE, glm::vec3(0, 0, (glm::pow(2, 15))));
		}
}