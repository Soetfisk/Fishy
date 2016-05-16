#pragma once
#include "GLNPC.h"
#include "ParticleHandler.h"

class NpcPowerUpHandler
{


private:

	FSHData::material* powerUpMaterial;
	std::vector<unsigned int> AvailableFishes; //vector of potential powerUpFishes
	std::vector<GLNPC*> NPCs; 

	unsigned int amountOfPowerUpFishes;
	
	void MakePowerUpFish();
	ParticleHandler* pHandlerRef;

public:
	NpcPowerUpHandler(std::vector<GLNPC*>);
	~NpcPowerUpHandler();


	std::vector<GLNPC*> PowerNPCs; //Vector of npc with powerups
	void RemovePowerUpFish(GLNPC*, unsigned int Fishindex);
	void RemoveAvailableFish(unsigned int Fishindex);
	void MovePowerUpToAnotherFish(GLNPC* RemoveThisFish, unsigned int Fishindex); //not used
	void initiatePowerFishes(); //initates the available fishes list
	void AsssignStartPowerupFishes(); //makes the powerFishes

	void addParticleHandlerReference(ParticleHandler* pHandler);
};
