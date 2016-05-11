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
	for (int i = 0; i < meshes.size(); i++)
	{
		glUniform3fv(shader.GetUnifromLocation("diffuse"), 1, glm::value_ptr(glm::vec3(meshes[i]->GetMaterial()->diffuse[0], meshes[i]->GetMaterial()->diffuse[1], meshes[i]->GetMaterial()->diffuse[2])));
		glUniform3fv(shader.GetUnifromLocation("ambient"), 1, glm::value_ptr(glm::vec3(meshes[i]->GetMaterial()->ambient[0], meshes[i]->GetMaterial()->ambient[1], meshes[i]->GetMaterial()->ambient[2])));
		glUniform3fv(shader.GetUnifromLocation("specular"), 1, glm::value_ptr(glm::vec3(meshes[i]->GetMaterial()->spec[0], meshes[i]->GetMaterial()->spec[1], meshes[i]->GetMaterial()->spec[2])));
		glUniform1f(shader.GetUnifromLocation("shininess"), meshes[i]->GetMaterial()->shinyness);
		meshes[i]->Draw(shader, *transform);
	}

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

		glm::vec3 randomRotationVector = glm::vec3(RNG::range(-0.8f, 0.8f), RNG::range(0.0f, 3.14f), RNG::range(-0.8f, 0.8f));
		Leafs.at(i)->GetTransform().SetRot(randomRotationVector);
		Leafs.at(i)->GetTransform().SetScale(glm::vec3(randScale));
		Leafs.at(i)->GetTransform().SetPos(glm::vec3(posX + this->GetRandOffsetX(), posY, posZ + this->getRandOffsetZ()));
		//this->GetTransform().SetPos(glm::vec3(10,10,10));

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
