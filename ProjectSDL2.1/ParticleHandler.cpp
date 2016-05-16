#include "ParticleHandler.h"



ParticleHandler::ParticleHandler(GLShader* renderShader, FishBox *FSH_LoaderReference){
	this->transformationLocation = renderShader->GetUnifromLocation("TransformMatrix");
	this->FSH_LoaderReference = FSH_LoaderReference;

	//this->textures = new FSHData::texture*[EmitterType::NREMITERTYPE];

	//this->textures[EmitterType::STATICSTREAM] = this->FSH_LoaderReference->loadTexure("./res/BubbleTest.png");
	//this->textures[EmitterType::GOLDSTREAM] = this->FSH_LoaderReference->loadTexure("./res/Star.png");
	//this->textures[EmitterType::PLAYERFOLLOW] = this->FSH_LoaderReference->loadTexure("./res/BubbleTest.png");
	//this->textures[EmitterType::PROJECTILE] = this->FSH_LoaderReference->loadTexure("./res/BubbleTest.png");
	//textureIDS[EmitterType::GOLDSTREAM] = getTexture(this->FSH_LoaderReference->loadTexure("./res/Star.png"));
	this->textureIDS[EmitterType::STATICSTREAM] = getTexture(this->FSH_LoaderReference->loadTexure("./res/BubbleTest.png"));
	this->textureIDS[EmitterType::GOLDSTREAM] = getTexture(this->FSH_LoaderReference->loadTexure("./res/Star.png"));
	this->textureIDS[EmitterType::PLAYERFOLLOW] = getTexture(this->FSH_LoaderReference->loadTexure("./res/BubbleTest.png"));
	this->textureIDS[EmitterType::PROJECTILE] = getTexture(this->FSH_LoaderReference->loadTexure("./res/BubbleTest.png"));
	
	FSH_LoaderReference->clean();
}

GLuint ParticleHandler::getTexture(FSHData::texture* texture) {

	GLuint returnID;
	for (int i = 0; i < EmitterType::NREMITERTYPE; i++) {

		glGenTextures(1, &returnID);

		glBindTexture(GL_TEXTURE_2D, returnID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->textureData);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}

	return returnID;
	delete texture;
}


ParticleHandler::~ParticleHandler(){
	for (int i = 0; i < this->emiters.size(); i++) {
		delete emiters.at(i);
	}
	//FSH_LoaderReference->clean();
	//for (int i = 0; i < EmitterType::NREMITERTYPE; i++) {
	//	delete textures[i];
	//}
	//delete[] textures;
	
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
	this->emiters.push_back(new ParticleEmitter(type, position, this->textureIDS[type]));
}

ParticleEmitter *ParticleHandler::CreateEmitter(EmitterType type, glm::vec4 position) {
	return new ParticleEmitter(type, position, this->textureIDS[type]);
}