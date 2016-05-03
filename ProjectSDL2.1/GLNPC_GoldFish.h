#pragma once

#include "GLNPC.h"

class GLNPC_GoldFish : public GLNPC
{
private:

	const int DEADZONEX = 125, DEADZONEY = 48, DEADZONEZ = 86;
	unsigned int currentState;
	float fleeingTimer, TimeUntilChange, scaleChange, forwardSpeed;
	glm::vec3 rotationChange;


public:
	//GLNPC_GoldFish(void);

	GLNPC_GoldFish(FishBox* FSH_Loader, unsigned int modelID);
	void NPCUpdate(float deltaTime);
	void NPCDraw(GLShader& shader);
	void gettingEaten(float deltaTime, GLTransform playerTransform);
	void NPCKill();
	void initiateFleeingState(glm::vec3 playerForwardVector);
	void checkboarderCollision();
	int GetCurrentState();
	void ResetFish();
};
