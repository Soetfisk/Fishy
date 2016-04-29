#ifndef PARTICLEEMITTER
#define PARTICLEEMITTER
#include "GLUtil.h"
#include "Particle.h"
#include "ParticleComputeShader.h"


class ParticleEmitter
{
private:
	EmitterType type;

	//Particle Data
	glm::mat4* p_transMat;
	glm::vec4* p_pos;
	glm::vec4* p_col;
	glm::vec4* p_startCol;
	glm::vec4* p_endCol;
	glm::vec4* p_vel;
	glm::vec4* p_acc;
	glm::vec4* p_time;
	bool* p_alive;
	
	ParticleRenderingUpdateData data;

	ParticleComputeShader* emitterComputeShader;
	GLuint transformationLocation;

	glm::mat4* transformLocation;
	glm::vec3 emitterPosition;
	GLuint pe_VertexArrayObject;
	GLuint pe_posBuf, pe_transBuf;

	glm::mat4* particleTransformationMatrices;
	glm::vec4* particleVelocities;

	float distanceFromObject;
	glm::vec3 directionFromObject;


	int nrActiveParticles;
	int nrMaxParticles;
	int nrCurrentParticles;
	float spawnTimer;


	void InstantiateProjectileEmitter();
	void InstantiateEmitter();
	void InstantiateRenderShader();
	void InstantiateSpaces();

	
public:
	ParticleEmitter(EmitterType type, glm::mat4*&  transformMatrix, GLuint transformMatrixLocation);
	ParticleEmitter(EmitterType type, glm::vec3 position, GLuint transformMatrixLocation);
	~ParticleEmitter();

	void ComputeUpdate(const float&deltaTime);
	void UpdateEmitter(const float& deltaTime);
	void Draw();
	
};

#endif