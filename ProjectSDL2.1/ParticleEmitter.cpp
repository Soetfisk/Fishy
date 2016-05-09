#include "ParticleEmitter.h"
#include "RNG.h"


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

	//InstantiateEmitter();

	//InstantiateRenderShader();

}

void ParticleEmitter::instantiateVariables() {
	this->nrActiveParticles = 0;
	this->emiterAwakeTime = 0;
	this->emiterSpawnTCurrent = 0;

	switch (this->type)
	{
	case EmitterType::STATICSTREAM:
		instantiateStaticStream();
		break;
	case EmitterType::GOLDSTREAM:
		instantiateGoldStream();
		break;
	default:
		break;
	}
}

void ParticleEmitter::instantiateStaticStream() {
	this->nrMaxParticles = 500;
	this->emiterSpawnTDelay = .5;

	this->particle.p_pos = this->positionEmitter;
	this->particle.p_lifeTime = 2;
	this->particle.p_acc = glm::vec4(0, -1, 0, 0);
	this->particle.p_scale = .05;
	this->particle.p_speed = 1;
	this->particle.p_vel = glm::vec4(0, 0, 0, 0);


}

void ParticleEmitter::instantiateGoldStream() {
	this->nrMaxParticles = 1090;
	this->emiterSpawnTDelay = 1;

	this->particle.p_pos = this->positionEmitter;
	this->particle.p_lifeTime = 4;
	this->particle.p_acc = glm::vec4(0, -1, 0, 0);
	this->particle.p_scale = 3;
	this->particle.p_speed = 1;
	this->particle.p_vel = glm::vec4(0, 1, 0, 0);

	this->directionEmitter = glm::vec4(1, 0, 0, 1);
}

void ParticleEmitter::instantiateSpawnBuffer() {
}

void ParticleEmitter::updateParticles(const float& deltaTime) {
	this->emiterSpawnTCurrent += deltaTime;
	this->emiterAwakeTime += deltaTime;
	

	

	if (this->emiterSpawnTCurrent >= this->emiterSpawnTDelay && this->nrActiveParticles < this->nrMaxParticles ) {
		this->emiterSpawnTCurrent = 0;
		this->spawnParticle();
		this->nrActiveParticles++;
	}
	
	if (nrActiveParticles > 0) {
		int k = 0;
		checkDeadParticles();
	}
		
}

void ParticleEmitter::spawnParticle() {

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->pe_particleBuffer);
	GLint bufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT; // the invalidate makes a big difference when re-writing
	struct ParticleStruct* tempParticles;

	tempParticles = (struct ParticleStruct *) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, nrActiveParticles * sizeof(ParticleStruct), sizeof(ParticleStruct), bufMask);

	Particle tempData = generateParticleData();
	ParticleStruct tempData2;
	
	tempData2.acceleration = tempData.p_acc;
	tempData2.customVariables = glm::vec4(tempData.p_scale, tempData.p_lifeTime, tempData.p_speed, 1);    //x= scale, y=lifeTime, z = speed, w = is alive
	tempData2.emiterPosition = this->positionEmitter;
	tempData2.pos = tempData.p_pos;
	tempData2.velocity = tempData.p_vel;
	tempParticles[0] = tempData2;

	//tempParticles[0].acceleration = tempData.p_acc;
	//tempParticles[0].customVariables = glm::vec4(tempData.p_scale, tempData.p_lifeTime, tempData.p_speed, 1);    //x= scale, y=lifeTime, z = speed, w = is alive
	//tempParticles[0].emiterPosition = this->positionEmitter;
	//tempParticles[0].pos = tempData.p_pos;
	//tempParticles[0].velocity = tempData.p_vel;
	
	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

	

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);


	
}


void ParticleEmitter::checkDeadParticles() {

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->pe_particleBuffer);

	//glMemoryBarrier(GL_BUFFER_UPDATE_BARRIER_BIT);	
	ParticleStruct* tempParticlesz = (struct ParticleStruct *) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, nrActiveParticles* sizeof(ParticleStruct), GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);

	ParticleStruct* temp = tempParticlesz;
	for (int i = 0; i < nrActiveParticles; i++) {
		


		if (temp[i].customVariables.y <= 0) {
			//std::cout << "KILL AT: " << i << std::endl;
			killParticleAtIndex(i, tempParticlesz);
		}
	}

	if (glUnmapBuffer(GL_SHADER_STORAGE_BUFFER) == GL_FALSE) {
		int k = 0;
	}
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

}


/*
Kills a particle at given index, re position the buffer to fit the drawing
*/
void ParticleEmitter::killParticleAtIndex(int index, ParticleStruct *& particleDestroyList) {

	if (this->nrActiveParticles > 1) {
		nrActiveParticles -= 1;

		if (nrActiveParticles != index)
			//int k = 0;
			swapData(nrActiveParticles, index, particleDestroyList);
		particleDestroyList[nrActiveParticles].customVariables.w = 0; //Set's alive to false


	}
	else {
		nrActiveParticles -= 1;
		particleDestroyList[index].customVariables.w = 0; //Set's alive to false
	}
}
void ParticleEmitter::swapData(int fromID, int destID, struct ParticleStruct* tempParticles) {
	tempParticles[destID] = tempParticles[fromID];

}


Particle ParticleEmitter::generateParticleData() {
	Particle returnData;
	returnData = this->particle;
	float tempNr;
	float tempNr2;
	glm::vec4 data;
	switch (this->type)
	{
	case EmitterType::STATICSTREAM:
		data.x= (float)(rand() % 5) / 10;
		data.y= (float)(rand() % 5) / 10;
		data.z = (float)(rand() % 5) / 10;

		returnData.p_acc = glm::vec4(returnData.p_acc.x + data.x, returnData.p_acc.y + data.y, returnData.p_acc.z + data.z, 0);
		returnData.p_vel = glm::vec4(returnData.p_acc.x + data.x, returnData.p_acc.y + data.y, returnData.p_acc.z + data.z, 0);
		returnData.p_scale = RNG::range(.05f, .15f);
		break;
	case EmitterType::GOLDSTREAM:
		returnData.p_acc = glm::vec4(RNG::range(-.5f, .5f), returnData.p_acc.y, RNG::range(-.5f, .5f), 0);
		break;
	}
	return returnData;
}
void ParticleEmitter::updateCompute(const float &deltaTime) {
	this->emitterComputeShader->Update(deltaTime, this->nrActiveParticles, this->pe_particleBuffer);
}

void ParticleEmitter::UpdateEmitter(const float& deltaTime) {
	this->emitterComputeShader->bind();
	updateParticles(deltaTime);
	updateCompute(deltaTime);


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




ParticleEmitter::~ParticleEmitter()
{

	delete emitterComputeShader;
	//delete[]this->p_pos;
	//delete[]this->p_scale;
	//delete[]this->p_vel;
	//delete[]this->p_acc;
	//delete[] this->p_ctime;
	//delete[] this->p_ltime;
	//delete[]this->p_alive;


}