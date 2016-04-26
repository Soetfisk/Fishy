#pragma once

#include "GLModel.h" 
#include "RNG.h"

enum NPCStates
{
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
	//GLNPC(void);
	//GLNPC(FishBox& FSH_Loader, char* filePath);
	GLNPC(FishBox& FSH_Loader, unsigned int modelID);
	virtual void NPCUpdate(float deltaTime)=0;
	virtual void NPCDraw(GLShader& shader)=0;
	virtual void gettingEaten(float deltaTime, GLTransform playerTransform)=0;
	virtual void NPCKill()=0;
	virtual void initiateFleeingState(glm::vec3 playerForwardVector)=0;
	virtual int GetCurrentState()=0;
};