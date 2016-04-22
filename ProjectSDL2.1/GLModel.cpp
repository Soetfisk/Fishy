#include "GLModel.h"
#include "obj_loader.h"


GLModel::GLModel()
{
	//Test
	transform = new GLTransform();
	meshes.push_back(objLoadFromFile("./res/OBJ/box2.obj"));
	meshes.push_back(objLoadFromFile("./res/OBJ/box2.obj"));

	meshes[0]->GetTransform().m_pos = glm::vec3(0, 0, 0.8);
	meshes[1]->GetTransform().m_pos = glm::vec3(0, 0, 0);

	meshes[0]->GetTransform().m_scale = glm::vec3(0.8);
}

GLModel::GLModel(FishBox& FSH_Loader, char* filePath) //DEPRICATED USE AT OWN RISK
{
	transform = new GLTransform();
	
	FSH_Loader.LoadScene(filePath);
	modelID = (FSH_Loader.GetModelCount() - 1);

	

	for (unsigned int i = 0; i < FSH_Loader.ModelMeshCount(modelID); i++)
	{
		meshes.push_back(new GLMesh(FSH_Loader.MeshData(modelID, i), FSH_Loader.VertexData(modelID, i), FSH_Loader.IndexData(modelID, i), FSH_Loader.meshMaterial(modelID, i)));
	}
}

GLModel::GLModel(FishBox& FSH_Loader, unsigned int modelID)
{
	transform = new GLTransform();
	this->modelID = modelID;

	for (unsigned int i = 0; i < FSH_Loader.ModelMeshCount(modelID); i++)
	{
		meshes.push_back(new GLMesh(FSH_Loader.MeshData(modelID, i), FSH_Loader.VertexData(modelID, i), FSH_Loader.IndexData(modelID, i), FSH_Loader.meshMaterial(modelID, i)));
	}

	FSHData::material * test = FSH_Loader.meshMaterial(modelID, 0);
}


GLModel::~GLModel()
{
	for (int i = 0; i < meshes.size(); i++)
	{
		delete meshes[i];
	}
	delete transform;
}

void GLModel::Draw(GLShader& shader)
{

	//transform->m_pos += glm::vec3(0, 0.0001, 0);
	//transform->m_rot += glm::vec3(0.001, 0.001, 0);
	//transform->m_scale += 0.00001f;

	/*meshes[0]->GetTransform().m_pos += glm::vec3(0.0001, 0, 0);
	meshes[1]->GetTransform().m_pos -= glm::vec3(0.0001, 0, 0);*/

	/*meshes[0]->GetTransform().m_rot += glm::vec3(0, 0.001, 0);
	meshes[1]->GetTransform().m_rot -= glm::vec3(0, 0.001, 0);*/

	/*meshes[0]->GetTransform().m_scale += 0.00001;
	meshes[1]->GetTransform().m_scale += 0.00001;*/


	for (int i = 0; i < meshes.size(); i++)
	{
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

	///*meshes[0]->GetTransform().m_rot += glm::vec3(0, 0.001, 0);
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
