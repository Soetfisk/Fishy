#ifndef SCENE_H
#define SCENE_H

#include "GLUtil.h"
#include "GLPlayer.h"
#include "GLShader.h"
#include "GLModel.h"

class Scene {
private:
	enum ShaderType {
		MODELS,
		//PARTICLES,
		//BLUR,
		NUM_SHADERS
	};

	//todo implement
	//std::vector<Model> models;
	std::vector<GLPlayer> players;
	//std::vector<Npc> npc;
	GLShader* shaders[NUM_SHADERS];
	GLMesh* tempMesh;
	GLModel* tempModel;


public:
	Scene();
	~Scene();

	void HandleEvenet(SDL_Event* e);

	void Update(float& deltaTime);
	void LoadScene();
	void DrawScene();
};

#endif