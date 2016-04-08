#include "Scene.h"



Scene::Scene(){
}


Scene::~Scene(){
}

void Scene::Update(float& deltaTime) {
	//for (int i = 0; i < this->player.count(); i++) {
		//this->player.at(i).update(deltTime);
	//}
	std::cout << deltaTime << std::endl;
}

//Loads the scene, models, matrices
void Scene::LoadScene() {

}

//Calls the models.draw
void Scene::DrawScene() {
	
	/*
	for(int i = 0; i< this->player.count();i++){
		//Set viewport
		glViewport(0, window::HEIGHT / (i + 1), window::WIDTH, window::HEIGHT / 2);
		for(int j = 0; j<this->models.count();j++){
			shaders[MODELS].Bind();
			shaders[MODELS].update(models.at(j), player.at(i).getCamera()); 
			models.at(j).draw(player.at(i).getCamera());
		}
	}
	
	
	*/
}

void Scene::HandleEvenet(SDL_Event* e) {

}
