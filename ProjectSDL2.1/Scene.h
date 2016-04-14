#ifndef SCENE_H
#define SCENE_H

#include "GLUtil.h"
#include "GLPlayer.h"
#include "GLShader.h"
#include "FrameBuffer.h"
#include "GLModel.h"
#include "GLProjectile.h"
#include "Particles.h"

class Scene {
private:
	enum ShaderType {
		MODELS,
		//PARTICLES,
		//BLUR,
		PASS,
		PARTICLE,
		NUM_SHADERS
	};

	//todo implement
	//std::vector<Model> models;
	std::vector<GLPlayer*> players;
	//std::vector<Npc> npc;
	GLShader* shaders[NUM_SHADERS];
	GLMesh* tempMesh;
	GLuint quadVAO = 0;
	GLModel* tempModel;
	GLuint quadVBO;
	FrameBuffer* frameBuffer;
	GLProjectile* testProj;
	Particles* testParticle;

public:
	Scene();
	~Scene();

	void HandleEvenet(SDL_Event* e);

	void Update(float& deltaTime);
	void LoadScene();
	void DrawScene();
	void RenderQuad();
};

#endif