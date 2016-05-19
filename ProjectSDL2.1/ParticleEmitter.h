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
	glm::vec4 directionRightEmitter;
	glm::vec4 directionUpEmitter;
	GLuint pe_VertexArrayObject;
	GLuint pe_particleBuffer;
	GLuint pe_VertexArrayBuffers[NUM_BUFFERS];



	int nrActiveParticles;
	int nrMaxParticles;
	float emiterAwakeTime;
	float emiterTimeSinceLastParticle;
	float emiterSpawnTDelay;
	float emiterSpawnTDelayStandard;
	float emiterSpawnTCurrent;
	float emiterCheckDeadTDelay;
	float emiterCheckDeadTCurrent;
	bool emiterMulitbleSpawner;
	float emiterNrToSpawnSimutan;
	float emiterScale;
	bool temporaryEmitter;
	float emiterMaxTime;

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
	void instantiateProjectileFollow();
	void instantiateBlood();
	void changeDirection(glm::vec4 dir);

	Particle particle;

	void Reset();
public:
	ParticleEmitter(EmitterType type, glm::vec4 position, GLuint textureID);
	~ParticleEmitter();
	void UpdateEmitter(const float& deltaTime);
	void Draw(GLShader* shader);

	void updatePosition(glm::vec4 pos);
	void updateDirection(glm::vec4 dir);
	void updateSpawnRate(float rate);
	void updateScale(const float &scale);

	void updateEmitterData(glm::vec4& pos, glm::vec4& dir, glm::vec4& right, glm::vec4& up, float rate, float scale);
	void updateEmitterData(glm::vec4& pos, glm::vec4& dir, glm::vec4& right, glm::vec4& up, float scale);
	
	void clean();
	bool isDead();
};

#endif