#include "ParticleEmitter.h"



ParticleEmitter::ParticleEmitter(EmitterType type, glm::mat4*& transformMatrix, GLuint transformMatrixLocation)
{
	this->type = type;
	this->transformationLocation = transformMatrixLocation;

	InstantiateEmitter();
}

ParticleEmitter::ParticleEmitter(EmitterType type, glm::vec4 position, GLuint transformMatrixLocation) {
	this->type = type;
	this->transformationLocation = transformMatrixLocation;
	this->positionEmitter = position;
	InstantiateEmitter();
	
	InstantiateRenderShader();
	
}



void ParticleEmitter::spawnParticle()
{
	glm::vec4 ranStuff = (glm::vec4(rand() % 10, rand() % 10, rand() % 10, 0)*.1f);
	this->p_transMat[nrActiveParticles] = glm::mat4(1);
	this->p_pos[nrActiveParticles] = this->positionEmitter + ranStuff;
	this->p_scale[nrActiveParticles] = glm::vec4(1);
	this->p_rot[nrActiveParticles] = glm::vec4(1);
	this->p_vel[nrActiveParticles] = this->particleStartVelocity + ranStuff;
	this->p_acc[nrActiveParticles] = this->particleStartAcceleration;
	this->p_ctime[nrActiveParticles] = 0;
	this->p_ltime[nrActiveParticles] = this->particleStartLifeTime;
	this->p_alive[nrActiveParticles] = true;
	

	this->nrActiveParticles++;
}

void ParticleEmitter::InstantiateSpaces() {


	this->p_transMat = new glm::mat4[this->nrMaxParticles];
	this->p_pos = new glm::vec4[this->nrMaxParticles];
	this->p_scale = new glm::vec4[this->nrMaxParticles];
	this->p_rot = new glm::vec4[this->nrMaxParticles];
	this->p_vel = new glm::vec4[this->nrMaxParticles];
	this->p_acc = new glm::vec4[this->nrMaxParticles];
	this->p_ctime = new float[this->nrMaxParticles];
	this->p_ltime = new float[this->nrMaxParticles];
	this->p_alive = new bool[this->nrMaxParticles];

	nrActiveParticles = 0;

	//for (int i = 0; i < this->nrMaxParticles; i++) {
	//	spawnParticle();
	//}

	data.position = p_pos;
	data.rotation = p_rot;
	data.scaling = p_scale;
	data.transformMatrix = p_transMat;
	data.velocity = p_vel;

	
}



ParticleEmitter::~ParticleEmitter()
{
	delete emitterComputeShader;
	delete[]this->p_transMat;
	delete[]this->p_pos;
	delete[]this->p_scale;
	delete[]this->p_rot;
	delete[]this->p_vel;
	delete[]this->p_acc;
	delete[] this->p_ctime;
	delete[] this->p_ltime;
	delete[]this->p_alive;

	//for (int i = 0; i < this->nrActiveParticles; i++) {
	//	deleteParticleAtID(i);
	//}

}


void ParticleEmitter::InstantiateEmitter() {
	
	this->emiterAwakeTime = 0.f;
	this->emiterTimeSinceLastParticle = 0.f;

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
	this->emitterComputeShader->Initialize(this->type, this->nrMaxParticles, this->data);

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
	this->nrMaxParticles = 100;
	this->spawnTimer = .1f;
	this->particleStartVelocity = glm::vec4(1, 0, 0, 1);
	this->particleStartAcceleration = glm::vec4(.1, 0, 0, 0);
	this->particleStartLifeTime = 6.f;


	//this->nrActiveParticles = 0;
}



void ParticleEmitter::updateDrawData() {
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
void ParticleEmitter::updateCompute(const float &deltaTime) {
	this->emitterComputeShader->Update(deltaTime, this->nrActiveParticles, data);
}

void ParticleEmitter::updateParticles(const float& deltaTime) {

	for (int i = 0; i < this->nrActiveParticles; i++) {
		this->p_ctime[i] += deltaTime;
		if (this->p_ctime[i] >= this->p_ltime[i]) {
			deactivateParticleAt(i);
			
		}
	}

	this->emiterTimeSinceLastParticle += deltaTime;

	if (this->emiterTimeSinceLastParticle >= this->spawnTimer) {
		if (this->nrActiveParticles < this->nrMaxParticles) {
			spawnParticle();
			this->emiterTimeSinceLastParticle = 0.f;
		}
		
	}

}

void ParticleEmitter::deactivateParticleAt(int ID) {


	if (nrActiveParticles > 1) {
		this->nrActiveParticles--;

		this->p_alive[ID] = false;
		swapData(nrActiveParticles, ID);
		
	}
	else {
		this->nrActiveParticles--;

		this->p_alive[ID] = false;
	}
}

void ParticleEmitter::swapData(int fromID, int destinationID) {
	this->p_transMat[destinationID] = this->p_transMat[fromID];
	this->p_pos[destinationID] = this->p_pos[fromID];
	this->p_vel[destinationID] = this->p_vel[fromID];
	this->p_acc[destinationID] = this->p_acc[fromID];
	this->p_ctime[destinationID] = this->p_ctime[fromID];
	this->p_ltime[destinationID] = this->p_ltime[fromID];
	this->p_alive[destinationID] = this->p_alive[fromID];
}

void ParticleEmitter::UpdateEmitter(const float& deltaTime) {
	//this->emitterPosition = glm::vec3(*this->transformLocation * glm::vec4(0, 0, 0, 0)) + (this->directionFromObject * this->distanceFromObject);
	//Update Particle timers
	updateParticles(deltaTime);

	updateCompute(deltaTime);

	updateDrawData();

	
}

void ParticleEmitter::Draw() {

	
	glBindVertexArray(this->pe_VertexArrayObject);

	glDrawArrays(GL_POINTS, 0, this->nrActiveParticles);

	glBindVertexArray(0);
	//glBindVertexArray(pe_VertexArrayObject);

	//glDrawArrays(GL_POINTS, 0, this->nrActiveParticles);
	//glBindVertexArray(0);
}