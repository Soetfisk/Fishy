#include "SeaWeedLeafs.h"

SeaWeedLeafs::SeaWeedLeafs(FishBox* FSH_Loader, unsigned int modelID) : SpecialStaticMesh(FSH_Loader, modelID)
{
	this-> FSH_Loader = FSH_Loader;
	this->modelID = modelID;

	this->transform->SetRot(glm::vec3(20, 20, 0));

	for (size_t i = 0; i < 10; i++)
	{
		this->Leafs.push_back(new GLModel(this->FSH_Loader, this->modelID));

		glm::vec3 randomRotationVector = glm::vec3(RNG::range(-1.1f, 1.1f), RNG::range(0.0f, 3.14f), RNG::range(-1.1f, 1.1f));
		Leafs.at(i)->GetTransform().SetRot(randomRotationVector);
		
	}

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
