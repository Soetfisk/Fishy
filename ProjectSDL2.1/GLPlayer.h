#pragma once
#include "GLUtil.h"
#include "GLCamera.h"
class GLPlayer
{
public:
	enum PlayerState
	{
		CAMERA_MOVE,
		PLAYER_MOVE,
		NUM_STATES
	};

	GLPlayer();
	~GLPlayer();
	void tempDraw();
	void Update(PlayerState state, glm::vec3 movementVec);
	GLCamera GetCamera();
private:
	glm::vec3 m_velocity;
	GLCamera m_camera;
};

