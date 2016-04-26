#ifndef PARTICLEEMITTER
#define PARTICLEEMITTER
#include "GLUtil.h"
#include "Particle.h"
#include "ParticleComputeShader.h"

struct ParticleTest {
	glm::vec4 pos;
	glm::vec4 vel;
	float LifetimeMillis;

	ParticleTest(): pos(), vel(), LifetimeMillis(){}
	ParticleTest(glm::vec4 cpos, glm::vec4 cvel, float ctime): pos(cpos), vel(cvel), LifetimeMillis(ctime){}
};


class ParticleEmitter
{
private:
	EmitterType type;
	std::vector<ParticleTest> particles;

	//Particle Data
	glm::vec4* p_pos;
	glm::vec4* p_col;
	glm::vec4* p_startCol;
	glm::vec4* p_endCol;
	glm::vec4* p_vel;
	glm::vec4* p_acc;
	glm::vec4* p_time;
	glm::vec4* p_alive;
	

	ParticleComputeShader* emitterComputeShader;
	GLuint transformationLocation;

	glm::mat4* transformLocation;
	glm::vec3 emitterPosition;
	GLuint pe_VertexArrayObject;
	GLuint pe_VertexArrayBuffer;

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

	void ComputeUpdate();
	void UpdateEmitter(const float& deltaTime);
	void Draw();
	
};

#endif