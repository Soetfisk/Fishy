#pragma once
#include "GLUtil.h"
#include "GLCamera.h"
class GLPlayer
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
	SDL_GameController *pad;
	int instanceID;
	glm::vec3 m_velocity;
	GLCamera m_camera;

	void AddController(int id);
	void RemoveController(int id);
};

