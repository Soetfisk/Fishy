#include "GLNPC_PowerUpHandler.h"

void NpcPowerUpHandler::initiatePowerFishes()
{
	for (unsigned int FishIndex = 0; FishIndex < NPCs.size(); FishIndex++)
	{
		AvailableFishes.push_back(FishIndex);
	}

	assert(amountOfPowerUpFishes < NPCs.size());
	for (size_t i = 0; i < amountOfPowerUpFishes; i++)
	{
		MakePowerUpFish();
	}
	


}

void NpcPowerUpHandler::MakePowerUpFish()
{
	if (AvailableFishes.size()>0)
	{
		unsigned int Index = RNG::PickIndexVector(&AvailableFishes);
		unsigned int Fish = AvailableFishes.at(Index); 
		AvailableFishes.erase(AvailableFishes.begin() + Index);
		NPCs.at(Fish)->isPowerUp = true;
		//NPCs.at(Fish)->SetCurrentState();

		PowerNPCs.push_back(NPCs.at(Fish));
	}
}

NpcPowerUpHandler::NpcPowerUpHandler(std::vector<GLNPC*> NPCList)
{
	this->NPCs = NPCList;
	initiatePowerFishes();
}

void NpcPowerUpHandler::RemovePowerUpFish(GLNPC* RemoveThisFish, unsigned int Fishindex)
{
	for (unsigned int  i = 0; i < PowerNPCs.size(); i++)
	{
		if (PowerNPCs.at(i) == RemoveThisFish)
		{
			PowerNPCs.erase(PowerNPCs.begin() + i);
			MakePowerUpFish();
			break;
			
		}
		
	}

}

void NpcPowerUpHandler::RemoveAvailableFish(unsigned int Fishindex)
{
	for (unsigned int i = 0; i < AvailableFishes.size(); i++)
	{
		if (AvailableFishes.at(i) == Fishindex)
		{
			AvailableFishes.erase(AvailableFishes.begin() + i);
		}
	}
}



void NpcPowerUpHandler::MovePowerUpToAnotherFish(GLNPC* RemoveThisFish, unsigned int Fishindex)
{
	for (unsigned int i = 0; i < PowerNPCs.size(); i++)
	{
		if (PowerNPCs.at(i) == RemoveThisFish)
		{
			PowerNPCs.at(i)->isPowerUp = false;
			PowerNPCs.erase(PowerNPCs.begin() + i);
			AvailableFishes.push_back(Fishindex);
			MakePowerUpFish();
			break;
		}

	}
}

NpcPowerUpHandler::~NpcPowerUpHandler()
{
	
}
