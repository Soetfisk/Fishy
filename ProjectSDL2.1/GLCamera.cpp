#include "GLCamera.h"



GLCamera::GLCamera(const glm::vec3 & pos, float fov, float aspect, float zNear, float zFar)
{
	m_perspective = glm::perspective(fov, aspect, zNear, zFar);
	m_position = pos;
	m_forward = glm::vec3(-0.1, 0, 0);
	m_up = glm::vec3(0, 1, 0);
}

GLCamera::GLCamera()
{
	m_perspective = glm::perspective(70.0f, (float)(1024/768), 0.01f, 1000.0f);
	m_position = glm::vec3(0, 0, 0);
	m_forward = glm::vec3(0, 0, 1);
	m_up = glm::vec3(0, 1, 0);
}

GLCamera::~GLCamera()
{
}

glm::vec3 & GLCamera::Position()
{
	return m_position;
}

glm::mat4 GLCamera::GetViewProjectionMatrix() const
{
	return m_perspective * glm::lookAt(m_position, m_position + m_forward, m_up);
}

void GLCamera::ProcessInput(float x, float y)
{
	float xOffset = x;
	float yOffset = y;

	xOffset *= sensitivity;
	yOffset *= sensitivity;

	angleAroundPlayer += xOffset;
	pitch += yOffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = -cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = -sin(glm::radians(pitch));
	front.z = -cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	m_forward = glm::normalize(front);
}

void GLCamera::calculatePosition(GLTransform transform)
{
	float theta = transform.GetRot().y + angleAroundPlayer;
	float offsetX = (float)((distanceToPlayer * cosf(glm::radians(pitch))) * sinf(glm::radians(theta)));
	float offsetZ = (float)((distanceToPlayer * cosf(glm::radians(pitch))) * cosf(glm::radians(theta)));

	this->m_position.x = transform.GetPos().x - offsetX;
	this->m_position.z = transform.GetPos().z - offsetZ;
	this->m_position.y = transform.GetPos().y + distanceToPlayer * sinf(pitch);
	this->yaw = 180 - (transform.GetRot().y + angleAroundPlayer);
}
