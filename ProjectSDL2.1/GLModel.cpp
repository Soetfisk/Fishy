#include "GLModel.h"



GLModel::GLModel()
{

}

GLModel::GLModel(FishBox* FSH_Loader, char* filePath) //DEPRICATED USE AT OWN RISK
{
	transform = new GLTransform();
	
	FSH_Loader->LoadScene(filePath);
	modelID = (FSH_Loader->GetModelCount() - 1);

	

	for (unsigned int i = 0; i < FSH_Loader->ModelMeshCount(modelID); i++)
	{
		if (FSH_Loader->MeshData(modelID, i)->blendshapesCount > 0)
			meshes.push_back(new GLMeshBS
				(
				FSH_Loader->MeshData(modelID, i),
				FSH_Loader->VertexData(modelID, i),
				FSH_Loader->IndexData(modelID, i),
				FSH_Loader->meshMaterial(modelID, i),
				FSH_Loader->meshTexture(modelID, i),
				FSH_Loader->meshBlendShapes(modelID, i)
				));
		else
			meshes.push_back(new GLMesh
				(
				FSH_Loader->MeshData(modelID, i),
				FSH_Loader->VertexData(modelID, i),
				FSH_Loader->IndexData(modelID, i),
				FSH_Loader->meshMaterial(modelID, i),
				FSH_Loader->meshTexture(modelID, i))
				);
	}
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
								FSH_Loader->meshTexture(modelID, i),
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
								FSH_Loader->meshTexture(modelID, i)
								)
							);
	}

	FSHData::material * test = FSH_Loader->meshMaterial(modelID, 0);
}


GLModel::~GLModel()
{
	for (size_t i = 0; i < meshes.size(); i++)
	{
		delete meshes[i];
	}
	delete transform;
}

void GLModel::Draw(GLShader& shader)
{

	for (size_t i = 0; i < meshes.size(); i++)
	{
		glUniform3fv(shader.GetUnifromLocation("diffuse"), 1, glm::value_ptr(glm::vec3(meshes[i]->GetMaterial()->diffuse[0], meshes[i]->GetMaterial()->diffuse[1], meshes[i]->GetMaterial()->diffuse[2])));
		glUniform3fv(shader.GetUnifromLocation("ambient"), 1, glm::value_ptr(glm::vec3(meshes[i]->GetMaterial()->ambient[0], meshes[i]->GetMaterial()->ambient[1], meshes[i]->GetMaterial()->ambient[2])));
		glUniform3fv(shader.GetUnifromLocation("specular"), 1, glm::value_ptr(glm::vec3(meshes[i]->GetMaterial()->spec[0], meshes[i]->GetMaterial()->spec[1], meshes[i]->GetMaterial()->spec[2])));
		glUniform1f(shader.GetUnifromLocation("shininess"), meshes[i]->GetMaterial()->shinyness);
		meshes[i]->Draw(shader, *transform);
	}
}

void GLModel::Update(float & dt)
{
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
	glm::vec3 front;
	front.x = cos(this->transform->m_rot.x) * sin(this->transform->m_rot.y);
	front.y = -sin(this->transform->m_rot.x);
	front.z = cos(this->transform->m_rot.x) * cos(this->transform->m_rot.y);
	return glm::normalize(front);
}

glm::vec3 GLModel::GetRight()
{
	glm::vec3 right;
	right.x = sin(this->transform->m_rot.y - 3.14f / 2.0f);
	right.y = 0;
	right.z = cos(this->transform->m_rot.y - 3.14f / 2.0f);
	return glm::normalize(right);
}

glm::vec3 GLModel::GetUp()
{
	glm::vec3 up = glm::cross(GetForward(), GetRight());
	return glm::normalize(up);
}

AABB GLModel::GetBoundingBox()
{
	this->boundingBox.center = this->transform->GetPos();
	this->boundingBox.halfDimension = this->transform->GetScale()/2.f;
	return this->boundingBox;
}

void GLModel::SetBoundingBox(glm::vec3 center, glm::vec3 extents)
{
	this->boundingBox.center = center;
	this->boundingBox.halfDimension = extents;
}
