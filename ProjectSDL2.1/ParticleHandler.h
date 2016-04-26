#ifndef PARTICILEHANDLER_H
#define PARTICILEHANDLER_H
#include "ParticleEmitter.h"

#include "GLShader.h"
class ParticleHandler
{
private:
	std::vector<ParticleEmitter*> emiters;
	GLuint transformationLocation;
public:
	ParticleHandler(GLShader* renderShader);
	~ParticleHandler();

	void UpdateParticles(const float& deltaTime, GLShader* shader, GLCamera& camera);
	void AddEmiter(EmitterType type, glm::mat4*& transformMatrix);
	void AddEmiter(EmitterType type, glm::vec3 position);

};

#endif