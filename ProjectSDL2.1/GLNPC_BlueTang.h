#pragma once
#pragma once

#include "GLNPC.h"

class GLNPC_BlueTang : public GLNPC
{
private:

	float originalFishSpeedMultiplier = 3;
	float fleeingTimer, TimeUntilChange, forwardSpeed;
	glm::vec3 rotationChange;
	


public:
	//GLNPC_BlueTang(void);

	GLNPC_BlueTang(FishBox* FSH_Loader, unsigned int modelID);
	void NPCUpdate(float deltaTime);
	void NPCDraw(GLShader& shader);
	bool gettingEaten(bool& isKill ,float BiteSize, glm::vec3 PushVector);
	void NPCKill();
	void initiateFleeingState(glm::vec3 playerForwardVector);
	void checkboarderCollision();
	void ResetFish();
	void ResetFish(float size);

	

	
};

