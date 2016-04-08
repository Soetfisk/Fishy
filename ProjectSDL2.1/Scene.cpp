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
	tempMesh = *objLoadFromFile("./res/OBJ/box2.obj");
}


Scene::~Scene(){
	for (int i = 0; i < NUM_SHADERS; i++) {
		delete shaders[i];
	}
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
	for(int i = 0; i< this->players.size();i++){
		//Set viewport
		//glViewport(0, window::HEIGHT / (i + 1), window::WIDTH, window::HEIGHT / 2);
		//for(int j = 0; j<this->models.count();j++){
		shaders[MODELS]->Bind();
		shaders[MODELS]->Update(tempMesh, players.at(i).GetCamera());
		tempMesh.Draw();
		//shaders[MODELS].update(models.at(j), player.at(i).getCamera()); 
		//	models.at(j).draw(player.at(i).getCamera());
		//}
	}
	
}

void Scene::HandleEvenet(SDL_Event* e) {
	
}
