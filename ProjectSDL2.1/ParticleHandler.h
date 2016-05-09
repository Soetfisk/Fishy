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
	void AddEmiter(EmitterType type, glm::vec4 position);
	void AddEmiter(EmitterType type, FollowParticle* objectToFollow);

};

#endif