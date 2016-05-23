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
	this->zMin = -50;
	this->zMax = 50;

	//scale
	this->scaleMin = 1;
	this->scaleMax = 10;

	//offset between leafs in same plant
	this->offsetX = 1;
	this->offsetZ = 1;



	this->FSH_Loader = FSH_Loader;
	this->modelID = modelID;

	//blendShapes
	this->blendWeights = new float[SW_NUM_ANIMATION];
	for (int i = 0; i < SW_NUM_ANIMATION; i++)
	{
		blendWeights[i] = 0.0f;
		animationFactors[i] = 0.0f;
	}

}

void SeaWeedHandler::LoadSeaWeed()
{
	int leafs;
	// Init the leafs
	for (int i = 0; i < amountOfPlants; i++)
	{
		this->limitPosX = RNG::range(this->xMin, this->xMax);
		this->limitPosZ = RNG::range(this->zMin, this->zMax);
		leafs = RNG::range(this->leafsMin,this->leafsMax);
		this->specialStaticMeshes.push_back(new SeaWeedLeafs(this->FSH_Loader, this->modelID, this->limitPosX, this->PosY, this->limitPosZ,leafs));
		this->specialStaticMeshes.at(i)->SetScale(this->scaleMin, this->scaleMax);
		this->specialStaticMeshes.at(i)->SetOffset(this->offsetX, this->offsetZ);
		this->specialStaticMeshes.at(i)->SetRotation(this->randomRot);
		this->specialStaticMeshes.at(i)->SetBoundingBox(boundingBox.center, boundingBox.halfDimension);
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
	delete blendWeights;
	for (size_t i = 0; i < specialStaticMeshes.size(); i++)
	{
		delete specialStaticMeshes.at(i);
	}
}

void SeaWeedHandler::Draw(GLShader * shader)
{
	for each (SeaWeedLeafs * leaf in specialStaticMeshes)
	{
		leaf->Draw(*shader);
	}
}

void SeaWeedHandler::DrawWithFrustrum(GLShader * shader, GLFrustum& frustrum)
{
	for each (SeaWeedLeafs * leaf in specialStaticMeshes)
	{
		leaf->Draw(*shader, frustrum);
	}
}

void SeaWeedHandler::SetZLimit(float min, float max)
{
	this->zMin = min;
	this->zMax = max;
}

void SeaWeedHandler::SetXLimit(float min, float max)
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

void SeaWeedHandler::SetScale(float min, float max)
{
	this->scaleMax = max;
	this->scaleMin = min;
}

void SeaWeedHandler::SetOffset(float x, float z)
{
	this->offsetX = x;
	this->offsetZ = z;
}

void SeaWeedHandler::SetBoundingBox(glm::vec3 & center, glm::vec3 & extents)
{
	AABB b;
	b.center = center;
	b.halfDimension = extents;
	boundingBox = b;
}

void SeaWeedHandler::Reset()
{
	for (int i = 0; i < this->amountOfPlants; i++)
	{
		this->specialStaticMeshes.at(i)->Reset();
	}
}

void SeaWeedHandler::moveAnimation(float deltaTime, float speedFactor)
{
	float speed = abs(deltaTime * speedFactor), y;

	animationFactors[SWONE] += speed;

	y = sin(animationFactors[SWONE]);

	if (y > 0.0)
		this->blendWeights[SWONE] = y;
	if (y < 0.0)
		this->blendWeights[SWTWO] = abs(y);
}

void SeaWeedHandler::Update(float deltaTime)
{
	if (this->isBlendShape == true)
	{
		moveAnimation(deltaTime, 0.5f);
	}
}

std::vector<GLModel*> SeaWeedHandler::GetMeshes()
{
	std::vector<GLModel*> finalModels;

	for (size_t i = 0; i < this->specialStaticMeshes.size(); i++)
	{
		finalModels.insert(finalModels.end(), this->specialStaticMeshes.at(i)->GetModels().begin(), this->specialStaticMeshes.at(i)->GetModels().end());
	}

	return finalModels;
}
void SeaWeedHandler::SetRandomRotation(float radian)
{
	this->randomRot = radian;
}



