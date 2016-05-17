#include "SeaWeedLeafs.h"

float SeaWeedLeafs::GetRandOffsetX()
{
	if (this->offsetX >= 1)
		return RNG::range(-this->offsetX, this->offsetX);
	else
		return 0.0f;
}

float SeaWeedLeafs::getRandOffsetZ()
{
	if (this->offsetZ >= 1)
		return RNG::range(-this->offsetZ, this->offsetZ);
	else
		return 0.0f;
}

SeaWeedLeafs::SeaWeedLeafs(FishBox* FSH_Loader, unsigned int modelID, float posX, float posY, float posZ, int leafs)
{
	this->FSH_Loader = FSH_Loader;
	this->modelID = modelID;

	int randScale = -1;
	this->scaleMin = 1;
	this->scaleMax = 10;
	this->posX = posX;
	this->posY = posY;
	this->posZ = posZ;
	this->leafsAmount = leafs;

	this->offsetX = 30;
	this->offsetZ = 30;

}

SeaWeedLeafs::~SeaWeedLeafs()
{

	for (size_t i = 0; i < Leafs.size(); i++)
	{
		delete Leafs.at(i);

	}

}

void SeaWeedLeafs::Draw(GLShader & shader)
{

	for (size_t i = 0; i < Leafs.size(); i++)
	{
		Leafs.at(i)->Draw(shader);
	}
}

void SeaWeedLeafs::LoadMesh()
{
	int randScale;
	for (size_t i = 0; i < this->leafsAmount; i++)
	{

		randScale = RNG::range(this->scaleMin, this->scaleMax);
		this->Leafs.push_back(new GLModel(this->FSH_Loader, this->modelID));

		glm::vec3 randomRotationVector = glm::vec3(RNG::range(-this->rotation, this->rotation), RNG::range(0.0f, 3.14f), RNG::range(-this->rotation, this->rotation));
		Leafs.at(i)->GetTransform().SetRot(randomRotationVector);
		Leafs.at(i)->GetTransform().SetScale(glm::vec3(randScale));
		Leafs.at(i)->GetTransform().SetPos(glm::vec3(posX + this->GetRandOffsetX(), posY, posZ + this->getRandOffsetZ()));
		Leafs.at(i)->SetBoundingBox(glm::vec3(0), glm::vec3(1.25));
		Leafs.at(i)->UpdateModel();
	}
}

void SeaWeedLeafs::reset()
{
	this->transform->SetRot(glm::vec3(20, 20, 0));
	for (size_t i = 0; i < 3; i++)
	{
		this->Leafs.push_back(new GLModel(this->FSH_Loader, this->modelID));
		glm::vec3 randomRotationVector = glm::vec3(RNG::range(0.0f, 30.0f), RNG::range(0.0f, 30.0f), RNG::range(0.0f, 30.0f));
		Leafs.at(i)->GetTransform().SetRot(randomRotationVector);
	}
}

void SeaWeedLeafs::SetScale(float min, float max)
{
	this->scaleMin = min;
	this->scaleMax = max;
}

void SeaWeedLeafs::SetOffset(int x, int y)
{
	this->offsetX = x;
	this->offsetZ = y;
}

void SeaWeedLeafs::Reset()
{
	int randScale;
	for (size_t i = 0; i < this->leafsAmount; i++)
	{
		randScale = RNG::range(this->scaleMin, this->scaleMax);

		glm::vec3 randomRotationVector = glm::vec3(RNG::range(-this->rotation, this->rotation), RNG::range(0.0f, 3.14f), RNG::range(-this->rotation, this->rotation));
		Leafs.at(i)->GetTransform().SetRot(randomRotationVector);
		Leafs.at(i)->GetTransform().SetScale(glm::vec3(randScale));
		Leafs.at(i)->GetTransform().SetPos(glm::vec3(posX + this->GetRandOffsetX(), posY, posZ + this->getRandOffsetZ()));
		Leafs.at(i)->SetBoundingBox(glm::vec3(0), glm::vec3(1.25));
		Leafs.at(i)->UpdateModel();
	}
}

std::vector<GLModel*>& SeaWeedLeafs::GetModels()
{
	return Leafs;
}
// The random rotation in radians
void SeaWeedLeafs::SetRotation(float X_Z)
{
	this->rotation = X_Z;
}
