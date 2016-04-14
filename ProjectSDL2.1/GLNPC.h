#pragma once

#include "GLModel.h" 
#include "RNG.h"

class GLNPC : public GLModel
{
	//1 First i am going to make an npc character. v/DONE
	//2 Change the position of the NPC
	//3 Make a move around functions 
	//4 Then i am going to give the npc different functions and states
private:
	enum NpcStates
	{
		DEAD,
		NOTHING,
		NPCMOVE,
		NPC_SHOOT
	};

	//void NpcDraw();

public:	
	GLNPC();
	void update();
	void NPCDraw(GLShader& shader);
	

};