#include "GLModel.h"
#include "obj_loader.h"


GLModel::GLModel()
{
	transform = new GLTransform();
	meshes.push_back(objLoadFromFile("./res/OBJ/box2.obj"));
	meshes.push_back(objLoadFromFile("./res/OBJ/box2.obj"));

	meshes[0]->GetTransform().m_pos = glm::vec3(-0.5, 0, 0);
	meshes[1]->GetTransform().m_pos = glm::vec3(0.5, 0, 0);

	test = 0;
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

	meshes[0]->GetTransform().m_scale += 0.00001;
	meshes[1]->GetTransform().m_scale += 0.00001;

	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->Draw(shader, *transform);
	}
}

void GLModel::Update(float & dt)
{
	//test++;
	transform->m_pos += glm::vec3(0, 0.001 , 0);
	transform->m_rot += glm::vec3(0.001, 0.001, 0);
	//transform->m_scale += 0.00001f;

	meshes[0]->GetTransform().m_pos += glm::vec3(0.0001, 0, 0);
	meshes[1]->GetTransform().m_pos -= glm::vec3(0.0001, 0, 0);

	/*meshes[0]->GetTransform().m_rot += glm::vec3(0, 0.001, 0);
	meshes[1]->GetTransform().m_rot -= glm::vec3(0, 0.001, 0);*/

	meshes[0]->GetTransform().m_scale += 0.00001;
	meshes[1]->GetTransform().m_scale -= 0.00001;
}

GLTransform& GLModel::GetTransform()
{
	return *transform;
}
