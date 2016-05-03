#include "ParticleEmitter.h"



ParticleEmitter::ParticleEmitter(EmitterType type, glm::mat4*& transformMatrix, GLuint transformMatrixLocation)
{
	this->type = type;
	this->transformationLocation = transformMatrixLocation;

	InstantiateEmitter();
}

ParticleEmitter::ParticleEmitter(EmitterType type, glm::vec4 position, GLuint transformMatrixLocation, FSHData::texture* texture) {
	this->type = type;
	//this->transformationLocation = transformMatrixLocation;
	this->positionEmitter = position;
	this->texture = texture;
	setTexture();
	this->nrMaxParticles = 1;
	this->nrActiveParticles = 1;

	this->emitterComputeShader = new ParticleComputeShader();
	this->emitterComputeShader->Initialize(this->type, this->nrMaxParticles, this->pe_particleBuffer);

	glGenVertexArrays(1, &pe_VertexArrayObject);
	glBindVertexArray(pe_VertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, this->pe_particleBuffer);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(ParticleStruct), 0);
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleStruct), (void*)16);
	glBindVertexArray(0);

	//InstantiateEmitter();

	//InstantiateRenderShader();

}

void ParticleEmitter::setTexture() {
	glGenTextures(1, &this->textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->texture->width, this->texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->texture->textureData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}



void ParticleEmitter::spawnParticle()
{
	glm::vec4 ranStuff = (glm::vec4(rand() % 10, rand() % 10, rand() % 10, 0)*.1f);
	this->p_pos[nrActiveParticles] = this->positionEmitter; //+ ranStuff;
	this->p_scale[nrActiveParticles] = this->particleScale;
	this->p_vel[nrActiveParticles] = this->particleStartVelocity + ranStuff;
	this->p_acc[nrActiveParticles] = this->particleStartAcceleration;
	this->p_ctime[nrActiveParticles] = 0;
	this->p_ltime[nrActiveParticles] = this->particleStartLifeTime;
	this->p_alive[nrActiveParticles] = true;


	this->nrActiveParticles++;
}

void ParticleEmitter::InstantiateSpaces() {


	this->p_pos = new glm::vec4[this->nrMaxParticles];
	this->p_vel = new glm::vec4[this->nrMaxParticles];
	this->p_acc = new glm::vec4[this->nrMaxParticles];
	this->p_scale = new float[this->nrMaxParticles];
	this->p_ctime = new float[this->nrMaxParticles];
	this->p_ltime = new float[this->nrMaxParticles];
	this->p_alive = new bool[this->nrMaxParticles];

	nrActiveParticles = 0;

	//for (int i = 0; i < this->nrMaxParticles; i++) {
	//	spawnParticle();
	//}

	data.position = p_pos;
	data.velocity = p_vel;
	data.scaling = p_scale;

}



ParticleEmitter::~ParticleEmitter()
{
	//delete emitterComputeShader;
	//delete[]this->p_pos;
	//delete[]this->p_scale;
	//delete[]this->p_vel;
	//delete[]this->p_acc;
	//delete[] this->p_ctime;
	//delete[] this->p_ltime;
	//delete[]this->p_alive;

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
		std::cout << "Couldnt instantiate emitter, didnt find type: " << this->type << std::endl;
		break;
	}



	InstantiateSpaces();

	//this->emitterComputeShader = new ParticleComputeShader();
	//this->emitterComputeShader->Initialize(this->type, this->nrMaxParticles, this->data);

}

void ParticleEmitter::InstantiateRenderShader() {
	glGenVertexArrays(1, &this->pe_VertexArrayObject);
	glBindVertexArray(this->pe_VertexArrayObject);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glGenBuffers(NUM_BUFFERS, pe_VertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, pe_VertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, this->nrMaxParticles * (sizeof(float) * 4), p_pos, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, pe_VertexArrayBuffers[SIZE_VB]);
	glBufferData(GL_ARRAY_BUFFER, this->nrMaxParticles * sizeof(float), p_scale, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

void ParticleEmitter::InstantiateProjectileEmitter() {
	this->directionFromObject = glm::vec3(0, 0, -1);
	this->distanceFromObject = 2;
	this->nrMaxParticles = 500;
	this->spawnTimer = .1f;
	this->particleStartVelocity = glm::vec4(1, 0, 0, 1);
	this->particleStartAcceleration = glm::vec4(.1, 0, 0, 0);
	this->particleStartLifeTime = 5.f;
	this->particleScale = 1.f;


	//this->nrActiveParticles = 0;
}



void ParticleEmitter::updateDrawData() {
	if (this->nrActiveParticles > 0) {

		glBindBuffer(GL_ARRAY_BUFFER, pe_VertexArrayBuffers[POSITION_VB]);
		glBufferData(GL_ARRAY_BUFFER, this->nrMaxParticles * (sizeof(float) * 4), p_pos, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, pe_VertexArrayBuffers[SIZE_VB]);
		glBufferData(GL_ARRAY_BUFFER, this->nrMaxParticles * sizeof(float), p_scale, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}
void ParticleEmitter::updateCompute(const float &deltaTime) {
	this->emitterComputeShader->Update(deltaTime, this->nrActiveParticles, this->pe_particleBuffer);
}

void ParticleEmitter::updateParticles(const float& deltaTime) {

	for (int i = 0; i < this->nrActiveParticles; i++) {
		this->p_ctime[i] += deltaTime;
		std::cout << i << " :::: SCALE: " << p_scale[i]<< "| x."<<p_pos[i].x<<", y." << p_pos[i].y << ", z." << p_pos[i].z << ", w." << p_pos[i].w << std::endl;
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

		swapData(ID);
		this->p_alive[nrActiveParticles] = false;

	}
	else {
		this->nrActiveParticles--;

		this->p_alive[ID] = false;
	}
}

void ParticleEmitter::swapData(int ID) {
	this->p_pos[ID] = this->p_pos[nrActiveParticles];
	this->p_vel[ID] = this->p_vel[nrActiveParticles];
	this->p_acc[ID] = this->p_acc[nrActiveParticles];
	this->p_ctime[ID] = this->p_ctime[nrActiveParticles];
	this->p_ltime[ID] = this->p_ltime[nrActiveParticles];
	
	this->p_scale[ID] = this->p_scale[nrActiveParticles];
	this->p_alive[ID] = this->p_alive[nrActiveParticles];
	
}

void ParticleEmitter::UpdateEmitter(const float& deltaTime) {
	//this->emitterPosition = glm::vec3(*this->transformLocation * glm::vec4(0, 0, 0, 0)) + (this->directionFromObject * this->distanceFromObject);
	//Update Particle timers
	//updateParticles(deltaTime);

	updateCompute(deltaTime);

	//updateDrawData();


}

void ParticleEmitter::Draw(GLShader* shader) {

	GLuint INDEX = shader->GetUnifromLocation("particle_tex");
	GLuint testing = GL_TEXTURE0 + 0;
	glActiveTexture(GL_TEXTURE0 + 0);
	glUniform1i(shader->GetUnifromLocation("particle_tex"), 0);
	glBindTexture(GL_TEXTURE_2D, this->textureID);
	glBindVertexArray(this->pe_VertexArrayObject);

	glDrawArrays(GL_POINTS, 0, this->nrMaxParticles);

	glBindVertexArray(0);
	//glBindVertexArray(pe_VertexArrayObject);

	//glDrawArrays(GL_POINTS, 0, this->nrActiveParticles);
	//glBindVertexArray(0);
}