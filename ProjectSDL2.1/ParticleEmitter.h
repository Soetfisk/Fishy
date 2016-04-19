#ifndef PARTICLEEMITTER
#define PARTICLEEMITTER
#include "GLUtil.h"
#include "Particle.h"
#include "ParticleComputeShader.h"




class ParticleEmitter
{
private:
	EmitterType type;
	std::vector<Particle*> particles;
	ParticleComputeShader* emitterComputeShader;
	GLuint transformationLocation;
	glm::mat4* transformLocation;
	glm::vec3 emitterPosition;


	float distanceFromObject;
	glm::vec4 directionFromObject;
	int nrMaxParticles;
	float spawnTimer;


	void InstantiateProjectileEmitter();
	void InstantiateEmitter();

	
public:
	ParticleEmitter(EmitterType type, glm::mat4*&  transformMatrix, GLuint transformMatrixLocation);
	ParticleEmitter(EmitterType type, glm::vec3 position, GLuint transformMatrixLocation);
	~ParticleEmitter();

	void ComputeUpdate();
	void UpdateEmitter(const float& deltaTime);
	void Draw();
	
};

#endif