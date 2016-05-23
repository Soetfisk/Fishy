#include "GLModel.h"


GLModel::GLModel()
{

}

GLModel::GLModel(FishBox* FSH_Loader, unsigned int modelID)
{
	transform = new GLTransform();
	this->modelID = modelID;

	for (unsigned int i = 0; i < FSH_Loader->ModelMeshCount(modelID); i++)
	{
		if (FSH_Loader->MeshData(modelID, i)->blendshapesCount > 0)
			meshes.push_back(
					new GLMeshBS(
								FSH_Loader->MeshData(modelID, i),
								FSH_Loader->VertexData(modelID, i),
								FSH_Loader->IndexData(modelID, i),
								FSH_Loader->meshMaterial(modelID, i),
								FSH_Loader->meshTextureID(modelID, i),
								FSH_Loader->meshBlendShapes(modelID, i)
								)
							);
		else
			meshes.push_back(
					  new GLMesh(
								FSH_Loader->MeshData(modelID, i),
								FSH_Loader->VertexData(modelID, i),
								FSH_Loader->IndexData(modelID, i),
								FSH_Loader->meshMaterial(modelID, i),
								FSH_Loader->meshTextureID(modelID, i)
								)
							);
	}


	this->UpdateModel();
}


GLModel::~GLModel()
{
	for (size_t i = 0; i < meshes.size(); i++)
	{
		delete meshes[i];
	}
	if(this->transform != nullptr)
	delete transform;
}

void GLModel::Draw(GLShader& shader)
{
	for each (GLMesh * meshi in meshes)
	{
		material * m = meshi->GetMaterial();

		glUniform3fv(shader.GetUnifromLocation("diffuse"), 1, m->diffuse);
		glUniform3fv(shader.GetUnifromLocation("ambient"), 1, m->ambient);
		glUniform3fv(shader.GetUnifromLocation("specular"), 1, m->spec);
		glUniform1f(shader.GetUnifromLocation("shininess"), m->shinyness);

		meshi->Draw(shader, *transform);
	}
}

void GLModel::UpdateModel()
{
	transform->UpdateModel();

	for each (GLMesh * meshi in meshes)
	{
		meshi->GetTransform().UpdateModel();
	}
	//transform->m_pos += glm::vec3(0, 0.001 , 0);
	//transform->m_rot += glm::vec3(0.001, 0.001, 0);
	////transform->m_scale += 0.00001f;

	//meshes[0]->GetTransform().m_pos += glm::vec3(0.0001, 0, 0);
	//meshes[1]->GetTransform().m_pos -= glm::vec3(0.0001, 0, 0);

	//*meshes[0]->GetTransform().m_rot += glm::vec3(0, 0.001, 0);
	//meshes[1]->GetTransform().m_rot -= glm::vec3(0, 0.001, 0);*/

	//meshes[0]->GetTransform().m_scale += 0.00001;
	//meshes[1]->GetTransform().m_scale -= 0.00001;
}

GLTransform& GLModel::GetTransform()
{
	return *transform;
}

glm::vec3 GLModel::GetForward()
{
	this->forward.x = cos(this->transform->m_rot.x) * sin(this->transform->m_rot.y);
	this->forward.y = -sin(this->transform->m_rot.x);
	this->forward.z = cos(this->transform->m_rot.x) * cos(this->transform->m_rot.y);
	return glm::normalize(this->forward);

}

glm::vec3 GLModel::GetRight()
{
	this->right.x = sin(this->transform->m_rot.y - 3.14f / 2.0f);
	this->right.y = 0;
	this->right.z = cos(this->transform->m_rot.y - 3.14f / 2.0f);
	return glm::normalize(this->right);
}

glm::vec3 GLModel::GetUp()
{
	this->up = glm::cross(GetForward(), GetRight());
	return glm::normalize(this->up);
}

AABB GLModel::GetBoundingBox()
{
	AABB aabb;
	aabb.center = this->boundingBox.center + this->transform->GetPos();
	aabb.halfDimension = this->boundingBox.halfDimension * this->transform->GetScale().x;
	return aabb;
}

void GLModel::SetBoundingBox(glm::vec3 center, glm::vec3 extents)
{
	this->boundingBox.center = center;
	this->boundingBox.halfDimension = extents;
}
