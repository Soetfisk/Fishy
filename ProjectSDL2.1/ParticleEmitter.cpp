#include "ParticleEmitter.h"



ParticleEmitter::ParticleEmitter(EmitterType type, glm::mat4*& transformMatrix, GLuint transformMatrixLocation)
{
	this->type = type;
	this->transformationLocation = transformMatrixLocation;
	this->transformLocation = transformMatrix;

	InstantiateEmitter();
}

ParticleEmitter::ParticleEmitter(EmitterType type, glm::vec3 position, GLuint transformMatrixLocation) {
	this->type = type;
	this->transformationLocation = transformMatrixLocation;
	this->transformLocation = &glm::translate(position);


	InstantiateEmitter();
}




ParticleEmitter::~ParticleEmitter()
{
	delete emitterComputeShader;
}

void ParticleEmitter::InstantiateEmitter() {

	switch (this->type)
	{
	case EmitterType::PROJECTILE:
		InstantiateProjectileEmitter();
		break;
	default:
		std::cout << "Couldnt instantiate emitter, didnt find type: "<< this->type << std::endl;
		break;
	}

	this->emitterComputeShader = new ParticleComputeShader();
	this->emitterComputeShader->Initialize(this->type, this->nrMaxParticles);

}

void ParticleEmitter::InstantiateProjectileEmitter() {
	this->directionFromObject = glm::vec4(0, 0, -1, 1);
	this->distanceFromObject = 2;
	this->nrMaxParticles = 50;
	this->spawnTimer = .1f;
}



void ParticleEmitter::ComputeUpdate() {

}

void ParticleEmitter::UpdateEmitter(const float& deltaTime) {
	this->emitterPosition = glm::vec3(*this->transformLocation * glm::vec4(0, 0, 0, 0));
	//Update Particle timers
}

void ParticleEmitter::Draw() {

}