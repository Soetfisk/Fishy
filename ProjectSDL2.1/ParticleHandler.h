#ifndef PARTICILEHANDLER_H
#define PARTICILEHANDLER_H
#include "ParticleEmitter.h"

#include "GLShader.h"
class ParticleHandler
{
private:
	std::vector<ParticleEmitter*> emiters;
	GLuint transformationLocation;
	FishBox *FSH_LoaderReference;
	FSHData::texture** textures;
public:
	ParticleHandler(GLShader* renderShader, FishBox *FSH_LoaderReference);
	~ParticleHandler();

	void UpdateParticles(const float& deltaTime);
	void DrawParticles(GLShader* shader, GLCamera& camera);
	void AddEmiter(EmitterType type, glm::mat4*& transformMatrix);
	void AddEmiter(EmitterType type, glm::vec4 position);

};

#endif