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




	ParticleTest test = ParticleTest(glm::vec4(0, 0, 3, 1), glm::vec4(0, 0, 1, 1), 5);
	this->particles.push_back(test);
	this->nrActiveParticles = 1;

	InstantiateEmitter();
	InstantiateRenderShader();



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
	this->emitterComputeShader->Initialize(this->type, this->nrMaxParticles, this->particleTransformationMatrices, this->particleVelocities);

}

void ParticleEmitter::InstantiateRenderShader() {
	glGenBuffers(1, &pe_VertexArrayBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, pe_VertexArrayBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->nrMaxParticles * sizeof(ParticleTest), &this->particles[0], GL_STATIC_DRAW);


	glGenVertexArrays(1, &pe_VertexArrayObject);
	glBindVertexArray(pe_VertexArrayObject);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(ParticleTest), 0);
}

void ParticleEmitter::InstantiateProjectileEmitter() {
	this->directionFromObject = glm::vec3(0, 0, -1);
	this->distanceFromObject = 2;
	this->nrMaxParticles = 50;
	this->spawnTimer = .1f;
	//this->nrActiveParticles = 0;
}



void ParticleEmitter::ComputeUpdate() {

}

void ParticleEmitter::UpdateEmitter(const float& deltaTime) {
	this->emitterPosition = glm::vec3(*this->transformLocation * glm::vec4(0, 0, 0, 0)) + (this->directionFromObject * this->distanceFromObject);
	//Update Particle timers
}

void ParticleEmitter::Draw() {

	
	glBindVertexArray(pe_VertexArrayObject);

	glDrawArrays(GL_POINTS, 0, this->nrActiveParticles);
	glBindVertexArray(0);
}