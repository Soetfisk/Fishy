#include "Scene.h"
#include "obj_loader.h"



Scene::Scene(){
	for (int i = 0; i < 1; i++) {
		this->players.push_back(GLPlayer());
	}
	shaders[MODELS] = new GLShader("test");


	//std::vector<Vertex> vertices;

	//vertices.push_back(Vertex(glm::vec3(-.5, .5, 0), glm::vec2(0, 1), glm::vec3(0, 0, 1)));
	//vertices.push_back(Vertex(glm::vec3(-.5, -.5, 0), glm::vec2(0, 0), glm::vec3(0, 0, 1)));
	//vertices.push_back(Vertex(glm::vec3(.5, -.5, 0), glm::vec2(1, 0), glm::vec3(0, 0, 1)));
	//vertices.push_back(Vertex(glm::vec3(.5, .5, 0), glm::vec2(1, 1), glm::vec3(0, 0, 1)));

	//std::vector<unsigned int> indices = {0, 1, 2, 2, 3, 0};
	//
	//tempMesh = GLMesh(vertices, vertices.size(), indices, indices.size(), GLMesh::Material());
	tempMesh = objLoadFromFile("./res/OBJ/box2.obj");
	tempMesh->GetTransform().m_pos.x = 4;
}


Scene::~Scene(){
	for (int i = 0; i < NUM_SHADERS; i++) {
		delete shaders[i];
	}
	delete tempMesh;
}

void Scene::Update(float& deltaTime) {
	for (int i = 0; i < this->players.size(); i++) {
		this->players.at(i).Update(GLPlayer::NOTHING ,glm::vec3(deltaTime));
	}
	//std::cout << deltaTime << std::endl;
}

//Loads the scene, models, matrices
void Scene::LoadScene() {

}

//Calls the models.draw
void Scene::DrawScene() {
	for(int i = 0; i< this->players.size();i++){
		//Set viewport
		//glViewport(0, window::HEIGHT / (i + 1), window::WIDTH, window::HEIGHT / 2);
		//for(int j = 0; j<this->models.count();j++){
		shaders[MODELS]->Bind();
		shaders[MODELS]->Update(*tempMesh, players.at(i).GetCamera());
		tempMesh->Draw();
		shaders[MODELS]->Update(*players.at(i).tempGetMesh(), players.at(i).GetCamera());
		players.at(i).tempGetMesh()->Draw();
		//shaders[MODELS].update(models.at(j), player.at(i).getCamera()); 
		//	models.at(j).draw(player.at(i).getCamera());
		//}
	}
	
}

void Scene::HandleEvenet(SDL_Event* e) {

		if (e->type == SDL_CONTROLLERDEVICEADDED)
		{
			players.at(e->cdevice.which).Update(GLPlayer::JOY_ADDED, glm::vec3(e->cdevice.which));
		}
		else if (e->type == SDL_CONTROLLERDEVICEREMOVED)
		{
			players.at(e->cdevice.which).Update(GLPlayer::JOY_REMOVED, glm::vec3(e->cdevice.which));
		}
		else if (e->type == SDL_CONTROLLERAXISMOTION)
		{
			if (e->caxis.axis == SDL_CONTROLLER_AXIS_RIGHTX)
			{
				players.at(e->caxis.which).Update(GLPlayer::CAMERA_MOVE, glm::vec3(e->caxis.value, 0, 0));
			}
			if (e->caxis.axis == SDL_CONTROLLER_AXIS_RIGHTY)
			{
				players.at(e->caxis.which).Update(GLPlayer::CAMERA_MOVE, glm::vec3(0, e->caxis.value, 0));
			}
			if (e->caxis.axis == SDL_CONTROLLER_AXIS_LEFTX)
			{
				players.at(e->caxis.which).Update(GLPlayer::PLAYER_MOVE, glm::vec3(e->caxis.value, 0, 0));
			}
			if (e->caxis.axis == SDL_CONTROLLER_AXIS_LEFTY)
			{
				players.at(e->caxis.which).Update(GLPlayer::PLAYER_MOVE, glm::vec3(0, e->caxis.value, 0));
			}
		}
}
