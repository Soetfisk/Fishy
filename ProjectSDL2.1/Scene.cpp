#include "Scene.h"
#include "obj_loader.h"
#include "LoadMesh.h"


Scene::Scene() {
	for (int i = 0; i < 1; i++) {
		this->players.push_back(GLPlayer());
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
	tempModel = new GLModel();
	//first make vertex for all vertexes
}


Scene::~Scene(){
	for (int i = 0; i < NUM_SHADERS; i++) {
		delete shaders[i];
	}
	delete tempMesh;
	delete this->frameBuffer;
	delete tempModel;
}

void Scene::Update(float& deltaTime) {
	//for (int i = 0; i < this->player.count(); i++) {
		//this->player.at(i).update(deltTime);
	//}
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
		shaders[MODELS]->Update(players.at(i).GetCamera());
		this->frameBuffer->BindFrameBuffer();
		tempModel->Draw(*shaders[MODELS]);
		//tempModel->Draw(*shaders[MODELS]);
		shaders[PASS]->Bind();
		this->frameBuffer->BindTexturesToProgram(shaders[PASS]->GetUnifromLocation("texture"), 0);
		this->frameBuffer->BindTexturesToProgram(shaders[PASS]->GetUnifromLocation("texture2"), 1);
		this->frameBuffer->BindTexturesToProgram(shaders[PASS]->GetUnifromLocation("texture3"), 2);
		this->frameBuffer->UnbindFrameBuffer();
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
	
}
