#include "GLCamera.h"



GLCamera::GLCamera(const glm::vec3 & pos, float fov, float aspect, float zNear, float zFar)
{
	m_perspective = glm::perspective(fov, aspect, zNear, zFar);
	m_position = pos;
	m_forward = glm::vec3(0, 0, 1);
	m_up = glm::vec3(0, 1, 0);
}

GLCamera::GLCamera()
{
	m_perspective = glm::perspective(70.0f, (float)(1024/768), 0.01f, 1000.0f);
	m_position = glm::vec3(0, 1, -3);
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

void GLCamera::ProcessInput(float x, float y, float deltaTime)
{
	float xOffset = x / (glm::pow(2, 15));
	float yOffset = y / (glm::pow(2, 15));

	xOffset *= 20 * deltaTime;
	yOffset *= 20 * deltaTime;


	angleAroundPlayer -= xOffset;
	pitch -= yOffset;

	//std::cout << deltaTime << std::endl;

	//std::cout << "X: "<< (std::to_string(x).c_str()) << " Xoffset: " << (std::to_string(xOffset).c_str()) << " AngleAroundPlayer: " << (std::to_string(angleAroundPlayer).c_str()) << std::endl;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -0.0f)
		pitch = -0.0f;

	//glm::vec3 front;
	//front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	//front.y = sin(glm::radians(pitch));
	//front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	//m_forward = glm::normalize(front);
}

float GLCamera::calcHorizontalDist()
{
	return (float)distanceToPlayer * cosf(glm::radians(pitch));
}

float GLCamera::calcVerticalDist()
{
	return (float)distanceToPlayer * sinf(glm::radians(pitch));
}

void GLCamera::calcCameraPos(float horizDist, float verticDist, GLTransform transform)
{
	float theta = transform.GetRot().y + angleAroundPlayer;
	float offsetX = horizDist * sinf(glm::radians(theta));
	float offsetZ = horizDist * cosf(glm::radians(theta));
	this->m_position.x = transform.GetPos().x - offsetX;
	this->m_position.z = transform.GetPos().z - offsetZ;
	this->m_position.y = transform.GetPos().y + verticDist;
	this->yaw = 180 - (transform.GetRot().y + angleAroundPlayer);
	this->m_forward = transform.GetPos() - this->m_position;
}

void GLCamera::Update(GLTransform transform, float deltaTime)
{
	if (lastX < -DEADZONE || lastX > DEADZONE || lastY < -DEADZONE || lastY > DEADZONE)
	{
		ProcessInput(lastX, lastY, deltaTime);
	}
	
	float horizDist = calcHorizontalDist();
	float verticDist = calcVerticalDist();
	calcCameraPos(horizDist, verticDist, transform);
}

void GLCamera::SetInput(float x, float y)
{
	if ((x < -DEADZONE || x > DEADZONE))
	{
		lastX = x;
	}
	else if (x != -1)
	{
		lastX = 0;
	}
	if ((y < -DEADZONE || y > DEADZONE))
	{
		lastY = y;
	}
	else if (y != -1)
	{
		lastY = 0;
	}
}
