#pragma once
#pragma once

#include "GLNPC.h"

class GLNPC_BlueTang : public GLNPC
{
private:

	
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
	void ResetFish();

	

	
};

