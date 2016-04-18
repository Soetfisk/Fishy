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
		DEAD,
		NOTHING,
		NPCMOVE,
		AGGRESIVE,
		NPC_SHOOT
	};
	unsigned int currentState;
	float TimeUntilChange, scaleChange,forwardSpeed;
	glm::vec3 rotationChange;
private:
	//Dash();
	//Eat();
	;


public:	
	GLNPC(void);
	void NPCUpdate(float deltaTime);
	void NPCDraw(GLShader& shader);

	

};