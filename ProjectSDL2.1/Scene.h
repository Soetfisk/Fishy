#ifndef SCENE_H
#define SCENE_H

#include "GLUtil.h"
#include "GLPlayer.h"
#include "GLNPC.h"
#include "GLShader.h"
#include "FrameBuffer.h"
#include "GLModel.h"
#include "GLProjectile.h"
#include "Particles.h"
#include "FilterComputeShader.h"
#include "RNG.h"
#include "ParticleHandler.h"

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
	FishBox FSH_Loader;
	std::vector<GLPlayer*> players;
	std::vector<GLNPC*> NPCs;
	GLShader* shaders[NUM_SHADERS];
	GLMesh* tempMesh;
	GLuint quadVAO = 0;
	std::vector<GLModel*> models;
	GLuint quadVBO;
	GLuint cs;
	FrameBuffer* frameBuffer;
	FrameBuffer* frameBuffer2;
	GLProjectile* testProj;
	Particles* testParticle;
	float count = 0;
	FilterComputeShader* filterComputeShader;
	float deltaTime;
	ParticleHandler *pHandler;
	
private:
	void LoadModels();
	void LoadModels(char* folder);
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