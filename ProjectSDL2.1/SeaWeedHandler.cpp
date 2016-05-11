#include "SeaWeedHandler.h"



SeaWeedHandler::SeaWeedHandler(FishBox* FSH_Loader, unsigned int modelID)
{
	this->limitPosX = 0;
	this->limitPosZ = 0;
	this->PosY = -49;

	this->amountOfPlants = 3; // the amount of plants 
	this->leafsMin = 3; // the plants contain this many leafs minimum
	this->leafsMax = 10; // the plants contain this many leafs maximum

	//Where the plants can spawn
	this->xMin = -50;
	this->xMax = 50;
	this->yMin = -50;
	this->yMax = 50;

	//scale
	this->scaleMin = 1;
	this->scaleMax = 10;

	//offset between leafs in same plant
	this->offsetX = 1;
	this->offsetZ = 1;


	this->FSH_Loader = FSH_Loader;
	this->modelID = modelID;

}

void SeaWeedHandler::LoadSeaWeed()
{
	int leafs;
	// Init the leafs
	for (size_t i = 0; i < amountOfPlants; i++)
	{
		this->limitPosX = RNG::range(this->xMin, this->xMax);
		this->limitPosZ = RNG::range(this->yMin, this->yMax);
		leafs = RNG::range(this->leafsMin,this->leafsMax);
		this->specialStaticMeshes.push_back(new SeaWeedLeafs(this->FSH_Loader, this->modelID, this->limitPosX, this->PosY, this->limitPosZ,leafs));
		this->specialStaticMeshes.at(i)->SetScale(this->scaleMin, this->scaleMax);
		this->specialStaticMeshes.at(i)->SetOffset(this->offsetX, this->offsetZ);
		//if (SeaWeedLeafs* temp = dynamic_cast<SeaWeedLeafs*>(this->specialStaticMeshes.at(i))) // if we have a seaweed fix scale and offset
		//{
		//	temp->SetScale(this->scaleMin, this->scaleMax);
		//	temp->SetOffset(this->offsetX,this->offsetZ);
		//	delete temp;
		//}
			
	}

	// load the leafs with the settings from init
	for (size_t i = 0; i < this->specialStaticMeshes.size(); i++)
	{
		this->specialStaticMeshes.at(i)->LoadMesh();
	}
}


SeaWeedHandler::~SeaWeedHandler()
{
	for (size_t i = 0; i < specialStaticMeshes.size(); i++)
	{
		delete specialStaticMeshes.at(i);
	}
}

void SeaWeedHandler::Draw(GLShader * shader)
{
	for (size_t i = 0; i < specialStaticMeshes.size(); i++)
	{
		specialStaticMeshes.at(i)->Draw(*shader);
	}
}

void SeaWeedHandler::SetYLimit(int min, int max)
{
	this->yMin = min;
	this->yMax = max;
}

void SeaWeedHandler::SetXLimit(int min, int max)
{
	this->xMin = min;
	this->xMax = max;
}

void SeaWeedHandler::SetLeafAmount(int min, int max)
{
	this->leafsMin = min;
	this->leafsMax = max;
}

void SeaWeedHandler::SetAmountOfPlants(int plants)
{
	this->amountOfPlants = plants;
}

void SeaWeedHandler::setScale(float min, float max)
{
	this->scaleMax = max;
	this->scaleMin = min;
}

void SeaWeedHandler::setOffset(int x, int z)
{
	this->offsetX = x;
	this->offsetZ = z;
}
