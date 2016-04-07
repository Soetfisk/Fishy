#include "Scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::Update(float& deltaTime) {

}

//Loads the scene, models, matrices
void Scene::LoadScene() {

}

//Calls the models.draw
void Scene::DrawScene() {
	/*
	for(int i = 0; i< this->player.count();i++){
		for(int j = 0; j<this->models.count();j++){
			models.at(j).draw(player.at(i).getCamera());
		}
	}
	
	
	
	*/
}

void Scene::HandleEvenet(SDL_Event* e) {

}
