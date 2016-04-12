#pragma once
#include "GLUtil.h"
#include "GLCamera.h"
#include "GLModel.h"
class GLPlayer : public GLModel
{
public:
	enum Events
	{
		NOTHING,
		CAMERA_MOVE,
		PLAYER_MOVE,
		JOY_ADDED,
		JOY_REMOVED,
		NUM_EVENTSTATES
	};
	enum PlayerStates
	{
		NUM_PLAYERSTATES
	};

	GLPlayer();
	~GLPlayer();
	void tempDraw();
	void Update(Events state, glm::vec3 movementVec);
	GLCamera GetCamera();

	void tempEvent();
private:
	const int DEADZONE = 8000;
	const int FRICTION = 50;
	float lastX = 0;
	float lastY = 0;
	SDL_GameController *pad;
	int instanceID;
	glm::vec3 m_velocity;
	glm::vec3 m_forward;
	GLCamera m_camera;

	void AddController(int id);
	void RemoveController(int id);
	void PlayerMove(float x, float y);
	void PlayerUpdate(float deltaTime);
};

