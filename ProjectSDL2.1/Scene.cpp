#include "Scene.h"
#include "obj_loader.h"
#include "LoadMesh.h"


Scene::Scene() {
	for (int i = 0; i < 1; i++) {
		this->players.push_back(new GLPlayer());
	}
	shaders[MODELS] = new GLShader("test");

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
	tempModel = new GLModel();
	tempMesh->GetTransform().SetPos(glm::vec3(3, 0, 3));
	//first make vertex for all vertexes

}


Scene::~Scene(){
	for (int i = 0; i < NUM_SHADERS; i++) {
		delete shaders[i];
	}

	delete tempModel;
	for (int i = 0; i < players.size(); i++)
	{
		delete players.at(i);
	}
	delete tempMesh;
}

void Scene::Update(float& deltaTime) {
	for (int i = 0; i < this->players.size(); i++) {
		this->players.at(i)->Update(GLPlayer::NOTHING ,glm::vec3(deltaTime));
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
		//glUniformMatrix4fv(shaders[MODELS]->GetUnifromLocation("TransformMatrix"), 1, GL_FALSE, glm::value_ptr(tempModel->GetTransform().GetModel());
		//tempModel->Draw(*shaders[MODELS]);
		players.at(0)->Draw(*shaders[MODELS]);
		tempMesh->Draw(*shaders[MODELS], GLTransform());

		//shaders[MODELS].update(models.at(j), player.at(i).getCamera()); 
		//	models.at(j).draw(player.at(i).getCamera());
		//}
	}
	
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
			if (e->caxis.axis == SDL_CONTROLLER_AXIS_RIGHTX)
			{
				players.at(e->caxis.which)->Update(GLPlayer::CAMERA_MOVE, glm::vec3(e->caxis.value, 0, 0));
			}
			if (e->caxis.axis == SDL_CONTROLLER_AXIS_RIGHTY)
			{
				players.at(e->caxis.which)->Update(GLPlayer::CAMERA_MOVE, glm::vec3(0, e->caxis.value, 0));
			}
			if (e->caxis.axis == SDL_CONTROLLER_AXIS_LEFTX)
			{
				players.at(e->caxis.which)->Update(GLPlayer::PLAYER_MOVE, glm::vec3(e->caxis.value, 0, 0));
			}
			if (e->caxis.axis == SDL_CONTROLLER_AXIS_LEFTY)
			{
				players.at(e->caxis.which)->Update(GLPlayer::PLAYER_MOVE, glm::vec3(0, e->caxis.value, 0));
			}
			if (e->caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT)
			{
				players.at(e->caxis.which)->Update(GLPlayer::PLAYER_MOVE, glm::vec3(0, e->caxis.value, 0));
			}
		}
}
