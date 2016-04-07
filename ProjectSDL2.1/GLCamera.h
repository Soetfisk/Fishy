#pragma once
#include "GLUtil.h"
#include "GLTransform.h"
class GLCamera
{
public:

	GLCamera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar);
	GLCamera();
	~GLCamera();

	glm::vec3& Position();
	glm::mat4 GetViewProjectionMatrix() const;
	void ProcessInput(float x, float y);
	void calculatePosition(GLTransform transform);
	
private:
	

	glm::mat4 m_perspective;
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_up;

	float distanceToPlayer = 50.0f;
	float angleAroundPlayer = 0;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float sensitivity = 0.05f;
};

