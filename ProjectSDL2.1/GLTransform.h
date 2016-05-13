#pragma once
#include "GLUtil.h"
class GLTransform
{
private:
	glm::mat4 posMatrix;
	glm::mat4 rotXMatrix;
	glm::mat4 rotYMatrix;
	glm::mat4 rotZMatrix;
	glm::mat4 scaleMatrix;
	glm::mat4 rotMatrix;
	glm::mat4 modelMatrix;
	glm::vec3 vecX = glm::vec3(1, 0, 0);
	glm::vec3 vecY = glm::vec3(0, 1, 0);
	glm::vec3 vecZ = glm::vec3(0, 0, 1);
public:
	GLTransform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		m_pos = pos;
		m_rot = rot;
		m_scale = scale;
	}

	void UpdateModel()
	{
		posMatrix = glm::translate(m_pos);

		rotXMatrix = glm::rotate(m_rot.x, vecX);
		rotYMatrix = glm::rotate(m_rot.y, vecY);
		rotZMatrix = glm::rotate(m_rot.z, vecZ);

		scaleMatrix = glm::scale(m_scale);

		rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

		modelMatrix = posMatrix * rotMatrix * scaleMatrix;
	}


	glm::mat4& GetModel() 
	{


		return modelMatrix;
	}

	glm::vec3& GetPos() { return m_pos; }
	glm::vec3& GetRot() { return m_rot; }
	glm::vec3& GetScale() { return m_scale; }

	void SetPos(glm::vec3& pos) { m_pos = pos; }
	void SetRot(glm::vec3& rot) { m_rot = rot; }
	void SetScale(glm::vec3& scale) { m_scale = scale; }
public:
	glm::vec3 m_pos;
	glm::vec3 m_rot;
	glm::vec3 m_scale;
};