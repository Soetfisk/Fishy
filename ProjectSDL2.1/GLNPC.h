#pragma once

#include "GLModel.h" 
#include "RNG.h"

class GLNPC : public GLModel
{
	//1First i am going to make an npc character.
	//2 Then i am going to give the npc different functions and states
private:
	enum NPCStates
	{
		BEINGEATEN,
		NOTHING,
		NPCMOVE,
		AGGRESIVE,
		FLEEING,
		NPC_SHOOT

	};
	const int DEADZONEX = 200, DEADZONEY = 200, DEADZONEZ = 200;
	unsigned int currentState;
	float fleeingTimer,TimeUntilChange, scaleChange,forwardSpeed;
	glm::vec3 rotationChange;

private:
	//Dash();
	//Eat();
	;


public:	
	GLNPC(void);
	GLNPC(FishBox& FSH_Loader, char* filePath);
	GLNPC(FishBox& FSH_Loader, unsigned int modelID);
	void NPCUpdate(float deltaTime);
	void NPCDraw(GLShader& shader);
	void gettingEaten(float deltaTime);
	void initiateFleeingState(glm::vec3 playerForwardVector);

	

};