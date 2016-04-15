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

GLModel::GLModel(std::string & filePath)
{
	// Load model from file
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
