#pragma once
#include "GLUtil.h"
class GLTransform
{
public:
	GLTransform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		m_pos = pos;
		m_rot = rot;
		m_scale = scale;
	}

	glm::mat4 GetModel() const
	{
		glm::mat4 posMatrix = glm::translate(m_pos);

		glm::mat4 rotXMatrix = glm::rotate(m_rot.x, glm::vec3(1, 0, 0));
		glm::mat4 rotYMatrix = glm::rotate(m_rot.y, glm::vec3(0, 1, 0));
		glm::mat4 rotZMatrix = glm::rotate(m_rot.z, glm::vec3(0, 0, 1));

		glm::mat4 scaleMatrix = glm::scale(m_scale);

		glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

		return posMatrix * rotMatrix * scaleMatrix;
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