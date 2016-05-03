#ifndef PARTICLEEMITTER
#define PARTICLEEMITTER
#include "GLUtil.h"
#include "ParticleComputeShader.h"
#include "GLShader.h"
#include "GLtexture.h"

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

	//Particle Data
	glm::mat4* p_transMat;
	glm::vec4* p_pos;
	glm::vec4* p_rot;
	glm::vec4* p_vel;
	glm::vec4* p_acc;
	float* p_scale;
	float* p_ctime;
	float* p_ltime;
	bool* p_alive;

	ParticleRenderingUpdateData data;

	ParticleComputeShader* emitterComputeShader;
	GLuint transformationLocation;

	glm::vec4 positionEmitter;
	GLuint pe_VertexArrayObject;
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
	float spawnTimer;
	float emiterAwakeTime;
	float emiterTimeSinceLastParticle;



	void swapData(int fromID, int destinationID);
	void deactivateParticleAt(int ID);
	void spawnParticle();
	void updateParticles(const float& deltaTime);
	void updateDrawData();
	void updateCompute(const float &deltaTime);


	void InstantiateProjectileEmitter();
	void InstantiateEmitter();
	void InstantiateRenderShader();
	void InstantiateSpaces();

	void setTexture();
	FSHData::texture* texture;
	GLuint textureID;
	GLTexture* tempTexture;

public:
	ParticleEmitter(EmitterType type, glm::mat4*&  transformMatrix, GLuint transformMatrixLocation);
	ParticleEmitter(EmitterType type, glm::vec4 position, GLuint transformMatrixLocation, FSHData::texture* texture);
	~ParticleEmitter();
	void UpdateEmitter(const float& deltaTime);
	void Draw(GLShader* shader);

};

#endif