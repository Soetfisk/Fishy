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
#include "GameState.h"
#include "SeaWeedLeafs.h"
#include "ParticleHandler.h"
#include <time.h>
#include <SDL2\SDL_mixer.h>
#include "RoundCounter.h"
#include "SeaWeedHandler.h"
#define mSTATIC *shaders[MODELS]
#define mANIMATED *shaders[BLEND_SHAPE]

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
		BLEND_SHAPE,
		PARTICLE,
		NUM_SHADERS
	};
	enum
	{
		PlayerFish,
		GoldFish,
		BlueTang,
		Bubble,
		Aquarium,
		SeaWeedLeaf,
		roughRock,
		smoothRock
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
	enum
	{
		COMBAT_BACKGROUND_MUSIC,
		ATTACK_BACKGROUND_MUSIC,
		ARCADE_BACKGROUND_MUSIC,

		NUM_MUSIC
	};

	Mix_Music *music[NUM_MUSIC];
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
	float count[2] = { 0,0 };
	FilterComputeShader* filterComputeShader;
	float deltaTime;
	GLCollisionHandler collisionHandler;

	GUI* guiTest;
	glm::mat4 projection;
	GLGUIHandler* guih;
	RoundCounter* rc;
	SeaWeedHandler* seaWeedHandler;
	SeaWeedHandler* stoneHandler;


	// variables for border shader
	float borderThreshold1, borderThreshold2;
	glm::vec3 borderColor1;
	// wavy
	float wavyAmount;
	float wavyLength;
	//fog
	float fogStart, fogEnd;
	glm::vec3 fogColor;
	// Player
	GLPlayer::PowerUps currentPowerUp;
	// Timer
	float endTimer; // when we end game
	float endScore; // reach this amount of points and game end
	float endSceneTimer = 0; // private time that is used for ending the game
	bool endGame = false;
	bool winner = false;
	GLOBAL_GameState* gameState;
	int currentSong = 0;

	ParticleHandler* particleHandler;

private:
	void Init();
	void LoadModels();
	void LoadModels(char* folder);
	void UpdatePlayerPowerUp(int player);
	void HandlePlayerPowerUp();
	void CheckWinner();
	void AddScore();
public:
	Scene(GLOBAL_GameState* gameState);
	Scene(GUI* textToScreen, GLOBAL_GameState* gameState);
	~Scene();

	void HandleEvenet(SDL_Event* e);

	void Update(float& deltaTime);
	void LoadScene();
	void DrawScene();
	void RenderQuad();
	void ResetScene();
};

#endif