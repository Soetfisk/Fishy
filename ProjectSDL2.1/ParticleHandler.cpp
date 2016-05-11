#include "ParticleHandler.h"



ParticleHandler::ParticleHandler(GLShader* renderShader, FishBox *FSH_LoaderReference){
	this->transformationLocation = renderShader->GetUnifromLocation("TransformMatrix");
	this->FSH_LoaderReference = FSH_LoaderReference;

	this->textures = new FSHData::texture*[EmitterType::NREMITERTYPE];

	this->textures[EmitterType::STATICSTREAM] = this->FSH_LoaderReference->loadTexure("./res/DarkBubble.png");
	this->textures[EmitterType::GOLDSTREAM] = this->FSH_LoaderReference->loadTexure("./res/Star.png");
	this->textures[EmitterType::PLAYERFOLLOW] = this->FSH_LoaderReference->loadTexure("./res/BubbleTest.png");
	this->textures[EmitterType::PROJECTILE] = this->FSH_LoaderReference->loadTexure("./res/BubbleTest.png");

	
}


ParticleHandler::~ParticleHandler(){
	for (int i = 0; i < this->emiters.size(); i++) {
		delete emiters.at(i);
	}
	FSH_LoaderReference->clean();
	for (int i = 0; i < EmitterType::NREMITERTYPE; i++) {
		delete textures[i];
	}
	delete[] textures;
	
}

void ParticleHandler::DrawParticles(GLShader* shader/*, GLCamera& camera*/) {
	//shader->Bind();
	//shader->Update(camera);
	for (int i = 0; i < this->emiters.size(); i++) {
		
		this->emiters.at(i)->Draw(shader);
	}
}

void ParticleHandler::UpdateParticles(const float& deltaTime) {

	for (int i = 0; i < this->emiters.size(); i++) {
		this->emiters.at(i)->UpdateEmitter(deltaTime);
	}
}




void ParticleHandler::AddEmiter(EmitterType type, glm::vec4 position) {
	this->emiters.push_back(new ParticleEmitter(type, position, this->textures[type]));
}

ParticleEmitter *ParticleHandler::CreateEmitter(EmitterType type, glm::vec4 position) {
	return new ParticleEmitter(type, position, this->textures[type]);
}