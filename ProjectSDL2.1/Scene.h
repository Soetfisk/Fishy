#ifndef SCENE_H
#define SCENE_H

#include "GLUtil.h"
#include "GLPlayer.h"
#include "GLShader.h"
#include "FrameBuffer.h"
#include "GLModel.h"
#include "GLProjectile.h"

class Scene {
private:
	enum ShaderType {
		MODELS,
		//PARTICLES,
		//BLUR,
		PASS,
		NUM_SHADERS
	};

	//todo implement
	//std::vector<Model> models;
	std::vector<GLPlayer> players;
	//std::vector<Npc> npc;
	GLShader* shaders[NUM_SHADERS];
	GLMesh* tempMesh;
	GLuint quadVAO = 0;
	GLModel* tempModel;
	GLuint quadVBO;
	GLuint cs;
	FrameBuffer* frameBuffer;
	FrameBuffer* frameBuffer2;
	GLProjectile* testProj;
	GLuint genComputeProg();
	void checkErrors(std::string desc);
	float count = 0;

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