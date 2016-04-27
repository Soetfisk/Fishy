#include "ParticleHandler.h"



ParticleHandler::ParticleHandler(GLShader* renderShader){
	this->transformationLocation = renderShader->GetUnifromLocation("TransformMatrix");
}


ParticleHandler::~ParticleHandler(){
	for (int i = 0; i < this->emiters.size(); i++) {
		delete emiters.at(i);
	}
}

void ParticleHandler::UpdateParticles(const float& deltaTime, GLShader* shader, GLCamera& camera) {

	for (int i = 0; i < this->emiters.size(); i++) {
		this->emiters.at(i)->ComputeUpdate(deltaTime);
		this->emiters.at(i)->UpdateEmitter(deltaTime);
	}

	shader->Bind();
	shader->Update(camera);
	for (int i = 0; i < this->emiters.size(); i++) {
		this->emiters.at(i)->Draw();
		//this->emiters.at(i).Update(deltaTime);
	}
}

void ParticleHandler::AddEmiter(EmitterType type, glm::mat4*& transformMatrix) {
	this->emiters.push_back(new ParticleEmitter(type, transformMatrix, this->transformationLocation));
}

void ParticleHandler::AddEmiter(EmitterType type, glm::vec3 position) {
	this->emiters.push_back(new ParticleEmitter(type, position, this->transformationLocation));
}