#include "ParticleEmitter.h"
#include "RNG.h"
#include "glm\ext.hpp"

ParticleEmitter::ParticleEmitter(EmitterType type, glm::vec4 position, FSHData::texture* texture) {
	this->type = type;
	this->positionEmitter = position;
	this->texture = texture;
	shouldUpdateObject = false;
	setTexture();
	

	instantiateVariables();
	//instantiateSpawnBuffer();
	this->emitterComputeShader = new ParticleComputeShader();
	this->emitterComputeShader->Initialize(this->type, this->nrMaxParticles, this->pe_particleBuffer);
	
	
	instantiateVertexData(); //neeeds to be after c_shader

	//InstantiateEmitter();

	//InstantiateRenderShader();
}

ParticleEmitter::ParticleEmitter(EmitterType type, FollowParticle* objToFollow, FSHData::texture* texture) {
	this->type = type;
	this->objectFollow = objToFollow;
	this->texture = texture;
	shouldUpdateObject = true;
	setTexture();
	
	instantiateVariables();
	//instantiateSpawnBuffer();
	this->emitterComputeShader = new ParticleComputeShader();
	this->emitterComputeShader->Initialize(this->type, this->nrMaxParticles, this->pe_particleBuffer);


	instantiateVertexData(); //neeeds to be after c_shader
}

void ParticleEmitter::instantiateVariables() {
	this->nrActiveParticles = 0;
	this->emiterAwakeTime = 0;
	this->emiterSpawnTCurrent = 0;

	this->emiterCheckDeadTDelay = 1.0f;
	this->emiterCheckDeadTCurrent = 0;

	switch (this->type)
	{
	case EmitterType::STATICSTREAM:
		instantiateStaticStream();
		break;
	case EmitterType::GOLDSTREAM:
		instantiateGoldStream();
		break;
	case EmitterType::PLAYERFOLLOW:
		instantiatePlayerFollow();
		break;
	default:
		break;
	}
}

void ParticleEmitter::instantiatePlayerFollow() {
	this->nrMaxParticles = 500;
	this->emiterSpawnTDelay = .01;
	this->emiterSpawnTDelayStandard = emiterSpawnTDelay;

	this->particle.p_pos = this->positionEmitter;
	this->particle.p_lifeTime = 2;
	this->particle.p_acc = glm::vec4(0, .5f, 0, 0);
	this->particle.p_scale = .05;
	this->particle.p_speed = 1;
	this->particle.p_vel = glm::vec4(0, 0, 0, 0);
}

void ParticleEmitter::instantiateStaticStream() {
	this->nrMaxParticles = 500;
	this->emiterSpawnTDelay = .6f;
	this->emiterSpawnTDelayStandard = emiterSpawnTDelay;

	this->particle.p_pos = this->positionEmitter;
	this->particle.p_lifeTime = 10;
	this->particle.p_acc = glm::vec4(0, 1, 0, 0);
	this->particle.p_scale = .05;
	this->particle.p_speed = 1;
	this->particle.p_vel = glm::vec4(0, 1, 0, 0);
	this->directionEmitter = glm::vec4(1, 0, 0, 1);

}

void ParticleEmitter::instantiateGoldStream() {
	this->nrMaxParticles = 1090;
	this->emiterSpawnTDelay = 1;
	this->emiterSpawnTDelayStandard = emiterSpawnTDelay;

	this->particle.p_pos = this->positionEmitter;
	this->particle.p_lifeTime = 4;
	this->particle.p_acc = glm::vec4(0, -1, 0, 0);
	this->particle.p_scale = 3;
	this->particle.p_speed = 1;
	this->particle.p_vel = glm::vec4(0, 1, 0, 0);

	this->directionEmitter = glm::vec4(1, 0, 0, 1);
}

void ParticleEmitter::changeDirection(glm::vec4 dir) {
	this->directionEmitter = dir;
}

void ParticleEmitter::updateParticles(const float& deltaTime) {
	this->emiterSpawnTCurrent += deltaTime;
	this->emiterAwakeTime += deltaTime;
	this->emiterCheckDeadTCurrent += deltaTime;

	

	if (this->emiterSpawnTCurrent >= this->emiterSpawnTDelay && this->nrActiveParticles < this->nrMaxParticles ) {
		
		this->spawnParticle();
		this->nrActiveParticles++;
		this->emiterSpawnTCurrent = 0;
	}
	
	if (nrActiveParticles > 0 && this->emiterCheckDeadTCurrent >= this->emiterCheckDeadTDelay) {
		this->emiterCheckDeadTCurrent = 0;
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

Particle ParticleEmitter::generateParticleData() {
	Particle returnData;
	returnData = this->particle;
	glm::vec4 data;
	switch (this->type)
	{
	case EmitterType::STATICSTREAM:
		data.x = RNG::range(-0.4f, .4f);
		data.y = RNG::range(0.f, .4f);
		data.z = RNG::range(-.4f, .4f);

		returnData.p_acc = glm::vec4(returnData.p_acc.x + data.x, returnData.p_acc.y + data.y, returnData.p_acc.z + data.z, 0);
		returnData.p_vel = glm::vec4(returnData.p_vel.x + data.x, returnData.p_vel.y + data.y, returnData.p_vel.z + data.z, 0);
		returnData.p_scale = RNG::range(1.f, 1.5f);
		break;
	case EmitterType::GOLDSTREAM:
		returnData.p_acc = glm::vec4(RNG::range(-.5f, .5f), returnData.p_acc.y, RNG::range(-.5f, .5f), 0);
		break;
	case EmitterType::PLAYERFOLLOW:
		data.x = RNG::range(.5f, 1.f);
		data.y = RNG::range(.5f, 1.f);
		data.z = RNG::range(.5f, 1.f);
		returnData.p_acc = this->directionEmitter + glm::vec4(returnData.p_acc.x + data.x, returnData.p_acc.y + data.y, returnData.p_acc.z + data.z, 0);
		returnData.p_pos = this->positionEmitter;
		returnData.p_pos += glm::vec4(*this->objectFollow->o_directionRight*RNG::range(-10.f, 10.f),0);
		returnData.p_pos += glm::vec4(*this->objectFollow->o_directionUp*RNG::range(-10.f, 10.f),0);

		//std::cout << "SPAWNING AT: " << glm::to_string(returnData.p_pos) << std::endl;

		returnData.p_vel = -this->directionEmitter + glm::vec4(returnData.p_acc.x + data.x, returnData.p_acc.y + data.y, returnData.p_acc.z + data.z, 0);
		returnData.p_scale = RNG::range(.1f, .15f);
		returnData.p_lifeTime *= RNG::range(.5f, 1.5f);
		break;
	}

	return returnData;
}

void ParticleEmitter::UpdateParticleObject() {
	this->positionEmitter = glm::vec4(*objectFollow->o_pos,1);
	this->directionEmitter = glm::vec4(*objectFollow->o_direction, 1);
	this->emiterSpawnTDelay = (*objectFollow->o_speed > .1f) ?  (100 / (*objectFollow->o_speed))* emiterSpawnTDelayStandard : 10;
	
	if (*objectFollow->o_speed > .1f)
		std::cout << "RIGHT: " << glm::to_string(*objectFollow->o_directionRight) << std::endl << "UP: " << glm::to_string(*objectFollow->o_directionUp) << std::endl;
		//std::cout << *objectFollow->o_speed<< " : " << this->positionEmitter.x << " : "<< this->directionEmitter.x << std::endl;

	//this->emiterSpawnTDelay = this->emiterSpawnTDelayStandard* *objectFollow->o_speed;
}

bool ParticleEmitter::shouldUpdateTransformation() {
	return shouldUpdateObject;
}

bool ParticleEmitter::followObjectDead() {
	return (objectFollow->o_pos == nullptr);
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

	if(shouldUpdateObject)
		delete objectFollow;
	//delete[]this->p_pos;
	//delete[]this->p_scale;
	//delete[]this->p_vel;
	//delete[]this->p_acc;
	//delete[] this->p_ctime;
	//delete[] this->p_ltime;
	//delete[]this->p_alive;


}
