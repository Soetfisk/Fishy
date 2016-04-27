#ifndef SCENE_H
#define SCENE_H

#include "GLUtil.h"
#include "GLPlayer.h"
#include "GLNPC.h"
#include "GLNPC_GoldFish.h"
#include "GLShader.h"
#include "FrameBuffer.h"
#include "GLModel.h"
#include "GLProjectile.h"
#include "FilterComputeShader.h"
#include "RNG.h"
#include "GUI.h"
#include "GLGUIHandler.h"
#include "GLCollisionHandler.h"

class Scene {
private:
	enum ShaderType {
		MODELS,
		//PARTICLES,
		//BLUR,
		PASS,
		LIGHTING,
		TEXT,
		WAVY,
		POST,
		NUM_SHADERS
	};
	enum
	{
		PlayerFish,
		GoldFish
	};
	int SCREEN_WIDTH = window::WIDTH;
	int SCREEN_HEIGHT = window::HEIGHT / 2;
	struct PointLight {
		glm::vec3 position;

		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;

		float constant;
		float linear;
		float quadratic;
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
	FrameBuffer* frameBuffer3;
	FrameBuffer* frameBuffer4;
	FrameBuffer* frameBuffer5;
	GLProjectile* testProj;
	float count = 0;
	FilterComputeShader* filterComputeShader;
	float deltaTime;
	GLCollisionHandler collisionHandler;
	
	GUI* guiTest;
	glm::mat4 projection;
	GLGUIHandler* guih;

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