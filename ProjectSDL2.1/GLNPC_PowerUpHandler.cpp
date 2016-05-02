#include "GLNPC_PowerUpHandler.h"

void NpcPowerUpHandler::initiatePowerFishes()
{
	AddPowerUpFish();

	//unsigned int randomNumber1 = RNG::range(0, NPCs.size()-1);
	//unsigned int randomNumber2 = RNG::range(0, NPCs.size()-1);

	//if (NPCs.size() >= 3)
	//{
	//	/*unsigned int randomNumber1 = NPCs.size()-1;
	//	unsigned int randomNumber2 = NPCs.size()-1;*/

	//	if (randomNumber2 == randomNumber1)
	//	{
	//		if (randomNumber2 < (NPCs.size() / 2))
	//		{
	//			randomNumber2++;
	//		}
	//		else
	//		{
	//			randomNumber2--;
	//		}
	//	}

	//	//printf("%d, %d", randomNumber1, randomNumber2);
	//	NPCs.at(randomNumber1)->isPowerUp = true;
	//	NPCs.at(randomNumber1)->SetCurrentState();
	//	PowerNPCs.push_back(NPCs.at(randomNumber1));

	//	NPCs.at(randomNumber2)->isPowerUp = true;
	//	NPCs.at(randomNumber2)->SetCurrentState();
	//	PowerNPCs.push_back(NPCs.at(randomNumber2));
	//}

}

void NpcPowerUpHandler::AddPowerUpFish()
{
	if (NPCs.size() >= 3)
	{

		//RNG::Pick(0, NPCs.size(), powerFishIndexes);
		unsigned int randomNumber=RNG::Pick(0, 3, powerFishIndexes);



		NPCs.at(randomNumber)->isPowerUp = true;
		NPCs.at(randomNumber)->SetCurrentState();
		PowerNPCs.push_back(NPCs.at(randomNumber));

	



	}
}

NpcPowerUpHandler::NpcPowerUpHandler(std::vector<GLNPC*> NPCList)
{
	this->NPCs = NPCList;
	initiatePowerFishes();
}

void NpcPowerUpHandler::RemovePowerUpFish(GLNPC* RemoveThisFish)
{
	for (unsigned int  i = 0; i < PowerNPCs.size(); i++)
	{
		if (PowerNPCs.at(i) == RemoveThisFish)
		{
			PowerNPCs.erase(PowerNPCs.begin()+i);
			AddPowerUpFish();
			break;
		}
	}

}

NpcPowerUpHandler::~NpcPowerUpHandler()
{
	
}
