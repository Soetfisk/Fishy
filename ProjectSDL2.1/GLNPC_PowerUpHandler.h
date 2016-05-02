#pragma once
#include "GLNPC.h"


class NpcPowerUpHandler
{

private:

	std::vector<unsigned int> powerFishIndexes;
	std::vector<GLNPC*> NPCs;
	void initiatePowerFishes();
	void AddPowerUpFish();

public:
	
	std::vector<GLNPC*> PowerNPCs;
	NpcPowerUpHandler(std::vector<GLNPC*>);
	void RemovePowerUpFish(GLNPC*);
	
	~NpcPowerUpHandler();


	//function RemoveMefromList(Fish(this)) :
};
