#ifndef PARTICLEEMITTER
#define PARTICLEEMITTER
#include "GLUtil.h"
#include "ParticleComputeShader.h"
#include "GLShader.h"
#include "GLtexture.h"


struct Particle {
	float p_lifeTime;
	float p_scale;
	float p_speed;
	glm::vec4 p_vel;
	glm::vec4 p_acc;
	glm::vec4 p_pos;
};

class ParticleEmitter
{
private:



	enum ParticleVB
	{
		POSITION_VB,
		SIZE_VB,

		NUM_BUFFERS
	};

	EmitterType type;

	//ParticleRenderingUpdateData data;

	ParticleComputeShader* emitterComputeShader;
	GLuint transformationLocation;

	glm::vec4 positionEmitter;
	GLuint pe_VertexArrayObject;
	GLuint pe_particleBuffer, pe_particleSpawnBuffer;
	GLuint pe_VertexArrayBuffers[NUM_BUFFERS];

	GLuint pe_posBuf, pe_scaleBuf;


	float distanceFromObject;
	glm::vec3 directionFromObject;
	glm::vec4 particleStartVelocity;
	glm::vec4 particleStartAcceleration;
	float particleStartLifeTime;
	float particleScale;

	int nrActiveParticles;
	int nrMaxParticles;
	float emiterAwakeTime;
	float emiterTimeSinceLastParticle;
	float emiterSpawnTDelay;
	float emiterSpawnTCurrent;


	void updateParticles(const float& deltaTime);
	void updateCompute(const float &deltaTime);

	void setTexture();
	FSHData::texture* texture;
	GLuint textureID;
	GLTexture* tempTexture;

	void instantiateSpawnBuffer();
	void instantiateVertexData();
	void killParticleAtIndex(int index);
	void swapData(int fromID, int destID, struct ParticleStruct* tempParticles);
	void spawnParticle();

	void instantiateVariables();
	Particle generateParticleData();
	void checkDeadParticles();
	

	Particle particle;




public:
	ParticleEmitter(EmitterType type, glm::mat4*&  transformMatrix, GLuint transformMatrixLocation);
	ParticleEmitter(EmitterType type, glm::vec4 position, GLuint transformMatrixLocation, FSHData::texture* texture);
	~ParticleEmitter();
	void UpdateEmitter(const float& deltaTime);
	void Draw(GLShader* shader);

};

#endif