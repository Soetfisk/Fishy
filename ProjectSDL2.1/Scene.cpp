#include "Scene.h"
#include "obj_loader.h"



void Scene::LoadModels()
{
	models.push_back(new GLModel(FSH_Loader, "Models/TestBin.FSH"));
}

void Scene::LoadModels(char * folder)
{
}

Scene::Scene() {
	for (int i = 0; i < 1; i++) {
		this->players.push_back(new GLPlayer());
	}
	for (int i = 0; i < 10; i++) {
		this->NPCs.push_back(new GLNPC());
	}
	shaders[MODELS] = new GLShader("test");
	shaders[PASS] = new GLShader("pass");

	//FishBox FishBoxController;
	//std::vector<FSHVertexData> FSHVertexes = FishBoxController.GetModelList()[0].GetMeshList()[0].GetVertices();
	//std::vector<Vertex> Vertices = ModelDataConvert::convertFSHVertex(FSHVertexes);

	//FSHMaterial Material = FishBoxController.GetModelList()[0].GetMaterialList()[0];
	//GL::Mesh GLMaterial = ModelDataConvert::convertFSHMaterial(Material);
	
	//new GLMesh(Vertices, Vertices.size(), /*indices*/, FishBoxController.GetModelList()[0].GetMeshList()[0].getIndexCount(), GLMaterial)

	//float hello = Material.getAmbient()[0];
	//printf("%f", hello);
	//std::vector<Vertex> vertices;

	//vertices.push_back(Vertex(glm::vec3(-.5, .5, 0), glm::vec2(0, 1), glm::vec3(0, 0, 1)));
	//vertices.push_back(Vertex(glm::vec3(-.5, -.5, 0), glm::vec2(0, 0), glm::vec3(0, 0, 1)));
	//vertices.push_back(Vertex(glm::vec3(.5, -.5, 0), glm::vec2(1, 0), glm::vec3(0, 0, 1)));
	//vertices.push_back(Vertex(glm::vec3(.5, .5, 0), glm::vec2(1, 1), glm::vec3(0, 0, 1)));

	//std::vector<unsigned int> indices = {0, 1, 2, 2, 3, 0};
	//
	//tempMesh = GLMesh(vertices, vertices.size(), indices, indices.size(), GLMesh::Material());
	tempMesh = objLoadFromFile("./res/OBJ/box2.obj");
	this->frameBuffer = new FrameBuffer();
	this->frameBuffer->CreateFrameBuffer(3);
	this->frameBuffer->UnbindFrameBuffer();
	tempMesh->GetTransform().SetPos(glm::vec3(3, 0, 3));
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
	delete tempMesh;
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
		//glViewport(0, window::HEIGHT / (i + 1), window::WIDTH, window::HEIGHT / 2);
		//for(int j = 0; j<this->models.count();j++){
		shaders[MODELS]->Bind();
		shaders[MODELS]->Update(players.at(i)->GetCamera());
		this->frameBuffer->BindFrameBuffer();
		//tempModel->Draw(*shaders[MODELS]);
		players.at(0)->Draw(*shaders[MODELS]);
		players.at(0)->tempGetProjectile()->TestDraw(*shaders[MODELS]);
		for (unsigned int i = 0; i < NPCs.size(); i++)
		{
			NPCs.at(i)->NPCDraw(*shaders[MODELS]);
		}
		

		tempMesh->Draw(*shaders[MODELS], GLTransform());

		


		//tempModel->Draw(*shaders[MODELS]);
		//shaders[PASS]->Bind();
		this->frameBuffer->UnbindFrameBuffer();
		this->filterComputeShader->BindShader();
		this->count += 0.1f * this->deltaTime;
		this->frameBuffer->BindImageTexturesToProgram(glGetUniformLocation(this->cs, "destTex"), 0);
		this->filterComputeShader->UniformVec3("colorVector",glm::vec3(0.0f,0.0f, 1.0f));
		this->filterComputeShader->Uniform1f("number",count);
		this->filterComputeShader->DispatchCompute(1024 / 32, 768 / 32, 1);
		
		shaders[PASS]->Bind();
		this->frameBuffer->BindTexturesToProgram(shaders[PASS]->GetUnifromLocation("texture"), 0);
		//this->frameBuffer->BindTexturesToProgram(shaders[PASS]->GetUnifromLocation("texture2"), 1);
		//this->frameBuffer->BindTexturesToProgram(shaders[PASS]->GetUnifromLocation("texture3"), 2);
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
			players.at(e->cdevice.which)->Update(GLPlayer::JOY_ADDED, glm::vec3(e->cdevice.which));
		}
		else if (e->type == SDL_CONTROLLERDEVICEREMOVED)
		{
			players.at(e->cdevice.which)->Update(GLPlayer::JOY_REMOVED, glm::vec3(e->cdevice.which));
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