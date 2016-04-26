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
	//1First i am going to make an npc character.
	//2 Then i am going to give the npc different functions and states
private:
	
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
	void gettingEaten(float deltaTime, GLTransform playerTransform);
	void NPCKill();
	void initiateFleeingState(glm::vec3 playerForwardVector);
	int GetCurrentState();

	

};