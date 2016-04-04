#pragma once
#include "GLUtil.h"
class GLCamera
{
public:
	enum Keys
	{
		FORWARD,
		LEFT,
		RIGHT,
		BACK,
		UP,
		DOWN
	};

	GLCamera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar);
	GLCamera();
	~GLCamera();

	glm::vec3 GetPos() const;
	glm::mat4 GetViewProjectionMatrix() const;
	void ProcessKeyboard(GLCamera::Keys key,float deltaTime);
	void ProcessMouse(float x, float y, float deltaTime);
	void ProcessScrollWheel(float y, float deltaTime);

	
private:
	

	glm::mat4 m_perspective;
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_up;

	float pitch = 0.0f;
	float yaw = 0.0f;
	float sensitivity = 0.05f;
	float movementSpeed = 5.0f;
};

