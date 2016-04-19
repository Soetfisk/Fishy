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
	void Update(GLTransform transform, float deltaTime);
	void SetInput(float x, float y);
	
private:
	
	const int DEADZONE = 8000;
	float lastX = 0;
	float lastY = 0;
	glm::mat4 m_perspective;
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_up;

	float distanceToPlayer = 5.0f;
	float angleAroundPlayer = 0;
	float pitch = 20.0f;
	float yaw = 0.0f;
	float cameraSpeed = 100;

	void ProcessInput(float x, float y, float deltaTime);

	float CalcHorizontalDist(GLTransform transform);
	float CalcVerticalDist(GLTransform transform);

	void CalcCameraPos(float horizDist, float verticDist, GLTransform transform);
};

