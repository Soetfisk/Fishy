#include "ParticleHandler.h"



ParticleHandler::ParticleHandler(GLShader* renderShader, FishBox *FSH_LoaderReference){
	this->transformationLocation = renderShader->GetUnifromLocation("TransformMatrix");
	this->FSH_LoaderReference = FSH_LoaderReference;

	this->textures = new FSHData::texture*[1];
	this->textures[0] = this->FSH_LoaderReference->loadTexure("res/Fishy.FST");
}


ParticleHandler::~ParticleHandler(){
	for (int i = 0; i < this->emiters.size(); i++) {
		delete emiters.at(i);
	}
}

void ParticleHandler::DrawParticles(GLShader* shader, GLCamera& camera) {
	
	for (int i = 0; i < this->emiters.size(); i++) {
		shader->Bind();
		shader->Update(camera);
		this->emiters.at(i)->Draw(shader);
		//this->emiters.at(i).Update(deltaTime);
	}
}

void ParticleHandler::UpdateParticles(const float& deltaTime) {

	for (int i = 0; i < this->emiters.size(); i++) {
		this->emiters.at(i)->UpdateEmitter(deltaTime);
		
	}

	
}

void ParticleHandler::AddEmiter(EmitterType type, glm::mat4*& transformMatrix) {
	this->emiters.push_back(new ParticleEmitter(type, transformMatrix, this->transformationLocation));
}

void ParticleHandler::AddEmiter(EmitterType type, glm::vec4 position) {
	this->emiters.push_back(new ParticleEmitter(type, position, this->transformationLocation, this->textures[0]));
}