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
	glm::vec4 directionEmitter;
	GLuint pe_VertexArrayObject;
	GLuint pe_particleBuffer, pe_particleSpawnBuffer;
	GLuint pe_VertexArrayBuffers[NUM_BUFFERS];

	GLuint pe_posBuf, pe_scaleBuf;



	int nrActiveParticles;
	int nrMaxParticles;
	float emiterAwakeTime;
	float emiterTimeSinceLastParticle;
	float emiterSpawnTDelay;
	float emiterSpawnTCurrent;
	float emiterCheckDeadTDelay;
	float emiterCheckDeadTCurrent;


	void updateParticles(const float& deltaTime);
	void updateCompute(const float &deltaTime);

	void setTexture();
	FSHData::texture* texture;
	GLuint textureID;
	GLTexture* tempTexture;

	void instantiateVertexData();
	void killParticleAtIndex(int index, ParticleStruct *& particleDestroyList);
	void swapData(int fromID, int destID, struct ParticleStruct* tempParticles);
	void spawnParticle();

	void instantiateVariables();
	Particle generateParticleData();
	void checkDeadParticles();

	void instantiateStaticStream();
	void instantiateGoldStream();
	void instantiatePlayerFollow();
	
	void changeDirection(glm::vec4 dir);

	Particle particle;



public:
	ParticleEmitter(EmitterType type, glm::mat4*&  transformMatrix, GLuint transformMatrixLocation);
	ParticleEmitter(EmitterType type, glm::vec4 position, GLuint transformMatrixLocation, FSHData::texture* texture);
	~ParticleEmitter();
	void UpdateEmitter(const float& deltaTime);
	void Draw(GLShader* shader);

};

#endif