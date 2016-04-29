#ifndef SCENE_H
#define SCENE_H

#include "GLUtil.h"
#include "GLPlayer.h"
#include "GLNPC.h"
#include "GLNPC_GoldFish.h"
#include "GLNPC_BlueTang.h"
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
		BORDER,
		NUM_SHADERS
	};
	enum
	{
		PlayerFish,
		GoldFish,
		BlueTang,
		Bubble,
		Aquarium
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
	struct Light
	{
		glm::vec3  dir;

		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};
	//todo implement
	//std::vector<Model> models;
	FishBox FSH_Loader;
	Light dirLight;
	std::vector<PointLight> pointLights;
	std::vector<GLPlayer*> players;
	std::vector<GLNPC*> NPCs;
	std::vector<GLModel*> staticMeshes;
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
	// variables for border shader
	float borderThreshold1, borderThreshold2;
	glm::vec3 borderColor1;
	// wavy
	float wavyAmount;
	float wavyLength;
	//fog
	float fogStart, fogEnd;
	glm::vec3 fogColor;
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