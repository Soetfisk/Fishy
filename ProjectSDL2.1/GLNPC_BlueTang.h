#pragma once
#pragma once

#include "GLNPC.h"

class GLNPC_BlueTang : public GLNPC
{
private:

	const int DEADZONEX = 125, DEADZONEY = 48, DEADZONEZ = 86;
	unsigned int currentState;
	float fleeingTimer, TimeUntilChange, forwardSpeed;
	glm::vec3 rotationChange;
	float FishSpeedMultiplier=1.5;


public:
	//GLNPC_BlueTang(void);

	GLNPC_BlueTang(FishBox* FSH_Loader, unsigned int modelID);
	void NPCUpdate(float deltaTime);
	void NPCDraw(GLShader& shader);
	void gettingEaten(float deltaTime, GLTransform playerTransform);
	void NPCKill();
	void initiateFleeingState(glm::vec3 playerForwardVector);
	void checkboarderCollision();
	int GetCurrentState();
	void SetCurrentState();
	bool GetIsPowerUp();
};

