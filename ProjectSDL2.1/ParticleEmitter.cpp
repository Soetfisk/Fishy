#include "ParticleEmitter.h"



ParticleEmitter::ParticleEmitter(EmitterType type, glm::mat4*& transformMatrix, GLuint transformMatrixLocation)
{
	this->type = type;
	this->transformationLocation = transformMatrixLocation;

}

ParticleEmitter::ParticleEmitter(EmitterType type, glm::vec4 position, GLuint transformMatrixLocation, FSHData::texture* texture) {
	this->type = type;
	//this->transformationLocation = transformMatrixLocation;
	this->positionEmitter = position;
	this->texture = texture;
	setTexture();

	instantiateVariables();
	//instantiateSpawnBuffer();
	this->emitterComputeShader = new ParticleComputeShader();
	this->emitterComputeShader->Initialize(this->type, this->nrMaxParticles, this->pe_particleBuffer);
	
	
	instantiateVertexData(); //neeeds to be after c_shader
	this->spawnParticle();
	//InstantiateEmitter();

	//InstantiateRenderShader();

}

void ParticleEmitter::instantiateVariables() {
	this->nrMaxParticles = 1;
	this->nrActiveParticles = 0;
	this->emiterAwakeTime = 0;
	this->emiterSpawnTCurrent = 0;
	this->emiterSpawnTDelay = 1;


	this->particle.p_pos = this->positionEmitter;
	this->particle.p_lifeTime = 5;
	this->particle.p_acc = glm::vec4(0, 1, 0, 0);
	this->particle.p_scale = .5;
	this->particle.p_speed = 1;
	this->particle.p_vel = glm::vec4(0, 0, 0, 0);
}

void ParticleEmitter::instantiateSpawnBuffer() {
	//glGenBuffers(1, &this->pe_particleSpawnBuffer);
	//glBindBuffer(GL_SHADER_STORAGE_BUFFER, pe_particleSpawnBuffer);
	//glBufferData(GL_SHADER_STORAGE_BUFFER, nrMaxParticles*sizeof(ParticleSpawnStruct), NULL, GL_STATIC_DRAW);
	//GLint bufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT; // the invalidate makes a big difference when re-writing
	//struct ParticleSpawnStruct* particlesSpawn;

	//particlesSpawn = (struct ParticleSpawnStruct *) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, nrMaxParticles * sizeof(ParticleSpawnStruct), bufMask);
	//
	//

	//for (float i = 0; i < nrMaxParticles; i++) {
	//	
	//	int index = i;
	//	particlesSpawn[index].customVariables = glm::vec4(); //Scale, Lifetime, Speed, IsAlive(1,0)
	//	particlesSpawn[index].velocity = glm::vec4();
	//	particlesSpawn[index].emiterPosition = glm::vec4();
	//	particlesSpawn[index].acceleration = glm::vec4();
	//}

	//glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

	//glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void ParticleEmitter::updateParticles(const float& deltaTime) {
	this->emiterSpawnTCurrent += deltaTime;

	

	if (this->emiterSpawnTCurrent >= this->emiterSpawnTDelay && this->nrActiveParticles < this->nrMaxParticles) {
		this->emiterSpawnTCurrent = 0;
		this->spawnParticle();

		this->nrActiveParticles++;
	}
	
	if (nrActiveParticles > 0)
		int k = 0;
		//checkDeadParticles();
}

void ParticleEmitter::spawnParticle() {
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->pe_particleBuffer);
	GLint bufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT; // the invalidate makes a big difference when re-writing
	struct ParticleStruct* tempParticles;

	tempParticles = (struct ParticleStruct *) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, nrActiveParticles * sizeof(ParticleStruct), sizeof(ParticleStruct), bufMask);

	Particle tempData;
	generateParticleData(tempData);

	tempParticles[0].acceleration = tempData.p_acc;
	tempParticles[0].customVariables = glm::vec4(tempData.p_scale, tempData.p_lifeTime, tempData.p_speed, 1);    //x= scale, y=lifeTime, z = speed, w = is alive
	tempParticles[0].emiterPosition = this->positionEmitter;
	tempParticles[0].pos = tempData.p_pos;
	tempParticles[0].velocity = tempData.p_vel;
	
	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

}

void ParticleEmitter::checkDeadParticles() {
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->pe_particleBuffer);
	struct ParticleStruct* tempParticlesz;

	tempParticlesz = (struct ParticleStruct *) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, nrActiveParticles * sizeof(ParticleStruct), GL_MAP_READ_BIT );

	if (tempParticlesz != NULL || tempParticlesz != nullptr) {
		ParticleStruct temp;

		if(nrActiveParticles == nrMaxParticles)
			int k = 0;
		for (int i = 0; i < nrActiveParticles; i++) {
			temp = tempParticlesz[0];
		}
	}
	

	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

	
}

void ParticleEmitter::generateParticleData(Particle tempData) {
	tempData = this->particle;
	//tempData.p_pos = glm::vec4(tempData.p_pos.x + this->nrActiveParticles, tempData.p_pos.y + this->nrActiveParticles, tempData.p_pos.z + this->nrActiveParticles, 0);
}

void ParticleEmitter::updateCompute(const float &deltaTime) {
	this->emitterComputeShader->Update(deltaTime, this->nrActiveParticles, this->pe_particleBuffer);
}

void ParticleEmitter::UpdateEmitter(const float& deltaTime) {
	this->emitterComputeShader->bind();
	updateParticles(deltaTime);
	//updateCompute(deltaTime);


}

void ParticleEmitter::Draw(GLShader* shader) {

	GLuint INDEX = shader->GetUnifromLocation("particle_tex");
	GLuint testing = GL_TEXTURE0 + 0;
	glActiveTexture(GL_TEXTURE0 + 0);
	glUniform1i(shader->GetUnifromLocation("particle_tex"), 0);
	glBindTexture(GL_TEXTURE_2D, this->textureID);
	glBindVertexArray(this->pe_VertexArrayObject);

	glDrawArrays(GL_POINTS, 0, nrActiveParticles);

	glBindVertexArray(0);
} 



void ParticleEmitter::setTexture() {
	glGenTextures(1, &this->textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->texture->width, this->texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->texture->textureData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void ParticleEmitter::instantiateVertexData() {
	glGenVertexArrays(1, &pe_VertexArrayObject);
	glBindVertexArray(pe_VertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, this->pe_particleBuffer);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(ParticleStruct), (void*)offsetof(struct ParticleStruct, pos));

	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleStruct), (void*)(offsetof(struct ParticleStruct, customVariables)));
	glBindVertexArray(0);
}

void ParticleEmitter::killParticleAtIndex(int index) {

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->pe_particleBuffer);
	GLint bufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT; // the invalidate makes a big difference when re-writing
	struct ParticleStruct* tempParticles;

	tempParticles = (struct ParticleStruct *) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, nrActiveParticles * sizeof(ParticleStruct), bufMask);

	if (this->nrActiveParticles > 1) {
		nrActiveParticles -= 1;

		if(nrActiveParticles != index)
			swapData(nrActiveParticles, index, tempParticles);
		tempParticles[nrActiveParticles].customVariables.w = 0; //Set's alive to false
		 
		
	}
	else {
		nrActiveParticles -= 1;
		tempParticles[index].customVariables.w = 0; //Set's alive to false
	}

	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}
void ParticleEmitter::swapData(int fromID, int destID, struct ParticleStruct* tempParticles) {
	tempParticles[destID] = tempParticles[fromID];

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


}
