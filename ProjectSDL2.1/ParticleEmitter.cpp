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
	
	InstantiateRenderShader();
	



}

void ParticleEmitter::InstantiateSpaces() {
	this->p_transMat = new glm::mat4[this->nrMaxParticles];
	this->p_pos = new glm::vec4[this->nrMaxParticles];
	this->p_col = new glm::vec4[this->nrMaxParticles];
	this->p_startCol = new glm::vec4[this->nrMaxParticles];
	this->p_endCol = new glm::vec4[this->nrMaxParticles];
	this->p_vel = new glm::vec4[this->nrMaxParticles];
	this->p_acc = new glm::vec4[this->nrMaxParticles];
	this->p_time = new glm::vec4[this->nrMaxParticles];
	this->p_alive = new bool[this->nrMaxParticles];



	this->p_pos[0] = glm::vec4(0, 0, 3, 1);
	//Pos should be instantiated at emitters position, p_pos[i] = emitter.pos
	this->p_transMat[0] = glm::mat4(1);

	this->p_pos[1] = glm::vec4(0, 2, 3, 1);
	//Pos should be instantiated at emitters position, p_pos[i] = emitter.pos
	this->p_transMat[1] = glm::mat4(1);


	this->nrActiveParticles = 2;
}



ParticleEmitter::~ParticleEmitter()
{
	//delete emitterComputeShader;
	delete[]this->p_transMat;
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

	InstantiateSpaces();

	this->emitterComputeShader = new ParticleComputeShader();
	this->emitterComputeShader->Initialize(this->type, this->nrMaxParticles,  this->p_transMat, this->particleVelocities, this->p_pos);

}

void ParticleEmitter::InstantiateRenderShader() {

	glGenVertexArrays(1, &this->pe_VertexArrayObject);
	glBindVertexArray(this->pe_VertexArrayObject);

	glGenBuffers(1, &pe_posBuf);
	glBindBuffer(GL_ARRAY_BUFFER, pe_posBuf);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * this->nrMaxParticles, nullptr, GL_STREAM_DRAW);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, (4)*sizeof(float), (void *)((0)*sizeof(float)));


	glGenBuffers(1, &pe_transBuf);
	glBindBuffer(GL_ARRAY_BUFFER, pe_transBuf);
	int m_location = 1;
	for (unsigned int i = 0; i < 4; i++) {
		GLuint index = m_location + i;
		GLsizei stride = sizeof(glm::mat4);
		GLsizei offset = (sizeof(GLfloat)*i * 4);

		glEnableVertexAttribArray(index);

		glVertexAttribPointer(index,
			4, GL_FLOAT, GL_FALSE,
			stride,
			(const GLvoid*)offset);

		//glVertexAttribDivisor(index, 0);
	}

	//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16 * this->nrMaxParticles, nullptr, GL_STREAM_DRAW);
	//glEnableVertexAttribArray(1);

	//glVertexAttribPointer(1, 16, GL_FLOAT, GL_FALSE, (16)*sizeof(float), (void *)((0)*sizeof(float)));



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



void ParticleEmitter::ComputeUpdate(const float&deltaTime) {
	this->emitterComputeShader->Update(deltaTime, this->nrActiveParticles);
}

void ParticleEmitter::UpdateEmitter(const float& deltaTime) {
	//this->emitterPosition = glm::vec3(*this->transformLocation * glm::vec4(0, 0, 0, 0)) + (this->directionFromObject * this->distanceFromObject);
	//Update Particle timers

	if (this->nrActiveParticles > 0) {
		glBindBuffer(GL_ARRAY_BUFFER, this->pe_posBuf);
		float* ptr = (float*)(this->p_pos);
		glBufferSubData(GL_ARRAY_BUFFER, 0, this->nrActiveParticles * sizeof(float) * 4, ptr);

		glBindBuffer(GL_ARRAY_BUFFER, this->pe_transBuf);

		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4)*this->nrActiveParticles, &this->p_transMat[0][0], GL_STATIC_DRAW);
		//ptr = (float*)(this->p_transMat);
		//glBufferSubData(GL_ARRAY_BUFFER, 0, this->nrActiveParticles * sizeof(float) * 16, ptr);

		 
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