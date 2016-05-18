#pragma once

#include "GLNPC.h"

class GLNPC_GoldFish : public GLNPC
{
private:

	
	float fleeingTimer, TimeUntilChange, scaleChange, forwardSpeed;
	glm::vec3 rotationChange;


public:
	GLNPC_GoldFish(FishBox* FSH_Loader, unsigned int modelID);
	void NPCUpdate(float deltaTime);
	void NPCDraw(GLShader& shader);
	bool gettingEaten(bool& isKill, float BiteSize, glm::vec3 PushVector);
	void NPCKill();
	void initiateFleeingState(glm::vec3 playerForwardVector);
	void checkboarderCollision();
	void ResetFish();
	void ResetFish(float size);

};
