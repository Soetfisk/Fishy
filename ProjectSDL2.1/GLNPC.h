#pragma once

#include "GLModel.h" 

class GLNPC : public GLModel
{
	//1First i am going to make an npc character.
	//2 Then i am going to give the npc different functions and states
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
	void update();
	void NPCDraw(GLShader& shader);
	

};