#include "GLNPC_PowerUpHandler.h"

void NpcPowerUpHandler::initiatePowerFishes()
{
	AvailableFishes.clear();
	PowerNPCs.clear();
	for (unsigned int FishIndex = 0; FishIndex < NPCs.size(); FishIndex++)
	{
		AvailableFishes.push_back(FishIndex);
	}
}

void NpcPowerUpHandler::AsssignStartPowerupFishes() {
	if(amountOfPowerUpFishes > NPCs.size())
	{
		amountOfPowerUpFishes = NPCs.size();
		
	}
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

		NPCs.at(Fish)->makePowerUp(powerUpMaterial);

		if(!this->NPCs.at(Fish)->hasEmitter())
			NPCs.at(Fish)->AddEmitter(pHandlerRef->CreateEmitter(EmitterType::GOLDSTREAM, glm::vec4(NPCs.at(Fish)->GetTransform().GetPos(), 1)));
		
		PowerNPCs.push_back(NPCs.at(Fish));

	}
}

NpcPowerUpHandler::NpcPowerUpHandler(std::vector<GLNPC*> NPCList)
{
	this->NPCs = NPCList;
	amountOfPowerUpFishes = 4;
	initiatePowerFishes();

	this->powerUpMaterial = new FSHData::material;

	this->powerUpMaterial->diffuse[0] = 1;
	this->powerUpMaterial->diffuse[1] = 1;
	this->powerUpMaterial->diffuse[2] = 0.4f;

	this->powerUpMaterial->ambient[0] = 0.7f;
	this->powerUpMaterial->ambient[1] = 0.3f;
	this->powerUpMaterial->ambient[2] = 0;

	this->powerUpMaterial->shinyness = 100;
	this->powerUpMaterial->spec[0] = 1;
	this->powerUpMaterial->spec[1] = 0.2f;
	this->powerUpMaterial->spec[2] = 0.2f;
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
			PowerNPCs.at(i)->GetIsPowerUp() = false;
			PowerNPCs.erase(PowerNPCs.begin() + i);
			AvailableFishes.push_back(Fishindex);
			MakePowerUpFish();
			break;
		}

	}
}

NpcPowerUpHandler::~NpcPowerUpHandler()
{
	delete powerUpMaterial;
}

void NpcPowerUpHandler::addParticleHandlerReference(ParticleHandler* pHandler) {
	this->pHandlerRef = pHandler;
}