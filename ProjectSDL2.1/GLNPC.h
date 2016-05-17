#pragma once

#include "GLModel.h" 
#include "RNG.h"
//#include "GLNPC_PowerUpHandler.h"

enum NPCStates
{
	NPC_STANDSTILL,
	NPC_BEINGEATEN,
	NPC_INACTIVE,
	NPC_MOVE,
	NPC_AGGRESIVE,
	NPC_FLEEING,
	NPC_SHOOT

};

class GLNPC : public GLModel
{

public:

	enum Animations
	{
		AONE,
		ATWO,

		NUM_ANIMATION
	};

protected:
	FSHData::material* originalMaterial;
	unsigned int currentState;
	float * blendWeights;
	float animationFactors[NUM_ANIMATION];

	ParticleEmitter *npc_emitter;
	ParticleEmitter *npc_blood_emitter;
	const int updateFrames = 3;
	int timeSinceUpdate; 
	float fishSize=1.0f;
	float FishSpeedMultiplier;
	float timeUntilRespawn;
	void RespawnCountdown(float deltaTime);

	bool isPowerUp = false;


	const int DEADZONEX = 124, DEADZONEY = 48, DEADZONEZ = 84;
	const float bloodTime = 3.f;
	const float bloodTimeCurrent;
	bool isBleeding;

	void enableBlood();

public:

	int GetCurrentState();
	void SetCurrentState();
	bool& GetIsPowerUp() { return isPowerUp; };
	void makePowerUp(FSHData::material* powerMaterial);

	GLNPC(FishBox* FSH_Loader, unsigned int modelID);
	~GLNPC();
	virtual void NPCUpdate(float deltaTime) = 0;
	virtual void NPCDraw(GLShader& shader) = 0;
	virtual void gettingEaten(float deltaTime, GLTransform playerTransform) = 0;
	virtual void NPCKill() = 0;
	virtual void initiateFleeingState(glm::vec3 playerForwardVector) = 0;

	virtual void ResetFish() = 0;
	virtual void ResetFish(float scale) = 0;

	float * GetBlendWeights() { return blendWeights; }
	unsigned int GetBlendShapeCount() { return NUM_ANIMATION; }
	void moveAnimation(float deltaTime, float speedFactor);
	void UpdateParticles(float &deltaTime);
	void DrawParticles(GLShader* shader);
	void AddEmitter(ParticleEmitter* emitter);
	bool hasEmitter();


};