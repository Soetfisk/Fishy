#pragma once
#include "GLUtil.h"
#include "GLCamera.h"
#include "GLModel.h"
#include "GLProjectile.h"
class GLPlayer : public GLModel
{
public:
	enum Events
	{
		NOTHING,
		CAMERA_MOVE,
		PLAYER_MOVE,
		PLAYER_SHOOT,
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
	GLProjectile* tempGetProjectile();
	void Update(Events state, glm::vec3 movementVec);
	GLCamera GetCamera();
private:
	const int DEADZONE = 8000;
	const int MOVEMENT_FRICTION = 100;
	const int MAX_SPEED = 10;
	float lastX = 0;
	float lastY = 0;
	SDL_GameController *pad;
	int instanceID;
	glm::vec3 m_velocity;
	glm::vec3 m_forward;
	GLCamera m_camera;
	GLProjectile *m_projectile;

	void AddController(int id);
	void RemoveController(int id);
	void PlayerMove(float x, float y);
	void PlayerUpdate(float deltaTime);
	void PlayerShoot();
};

