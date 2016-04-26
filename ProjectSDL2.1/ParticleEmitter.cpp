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
	InstantiateSpaces();
	InstantiateRenderShader();
	



}

void ParticleEmitter::InstantiateSpaces() {
	this->p_pos = new glm::vec4[this->nrMaxParticles];
	this->p_col = new glm::vec4[this->nrMaxParticles];
	this->p_startCol = new glm::vec4[this->nrMaxParticles];
	this->p_endCol = new glm::vec4[this->nrMaxParticles];
	this->p_vel = new glm::vec4[this->nrMaxParticles];
	this->p_acc = new glm::vec4[this->nrMaxParticles];
	this->p_time = new glm::vec4[this->nrMaxParticles];
	this->p_alive = new glm::vec4[this->nrMaxParticles];


	this->p_pos[0] = glm::vec4(0, 0, 3, 1);
}



ParticleEmitter::~ParticleEmitter()
{
	//delete emitterComputeShader;
	delete[]this->p_pos;
	delete[]this->p_col;
	delete[]this->p_startCol;
	delete[]this->p_endCol;
	delete[]this->p_vel;
	delete[]this->p_acc;
	delete[]this->p_time;
	delete[]this->p_alive;
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

	//this->emitterComputeShader = new ParticleComputeShader();
	//this->emitterComputeShader->Initialize(this->type, this->nrMaxParticles, this->particleTransformationMatrices, this->particleVelocities);

}

void ParticleEmitter::InstantiateRenderShader() {

	glGenVertexArrays(1, &this->pe_VertexArrayObject);
	glBindVertexArray(this->pe_VertexArrayObject);

	glGenBuffers(1, &pe_VertexArrayBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, pe_VertexArrayBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * this->nrMaxParticles, nullptr, GL_STREAM_DRAW);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, (4)*sizeof(float), (void *)((0)*sizeof(float)));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	//glGenBuffers(1, &pe_VertexArrayBuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, pe_VertexArrayBuffer);
	//glBufferData(GL_ARRAY_BUFFER, this->nrMaxParticles * sizeof(ParticleTest), &this->particles[0], GL_STATIC_DRAW);


	//glGenVertexArrays(1, &pe_VertexArrayObject);
	//glBindVertexArray(pe_VertexArrayObject);

	//glEnableVertexAttribArray(0);
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
	//this->emitterPosition = glm::vec3(*this->transformLocation * glm::vec4(0, 0, 0, 0)) + (this->directionFromObject * this->distanceFromObject);
	//Update Particle timers

	if (this->nrActiveParticles > 0) {
		glBindBuffer(GL_ARRAY_BUFFER, this->pe_VertexArrayBuffer);
		float* ptr = (float*)(this->p_pos);
		glBufferSubData(GL_ARRAY_BUFFER, 0, this->nrActiveParticles * sizeof(float) * 4, ptr);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void ParticleEmitter::Draw() {

	
	glBindVertexArray(this->pe_VertexArrayObject);

	glDrawArrays(GL_POINTS, 0, this->nrActiveParticles);

	glBindVertexArray(0);
	//glBindVertexArray(pe_VertexArrayObject);

	//glDrawArrays(GL_POINTS, 0, this->nrActiveParticles);
	//glBindVertexArray(0);
}