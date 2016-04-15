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

	float lastHorizontal = 0;
	float lastVertical = 0;
	float lastForward = 0;
	glm::vec3 m_velocity;

	SDL_GameController *pad;
	int instanceID;
	GLCamera m_camera;
	GLProjectile *m_projectile;

	float rotateSpeed = 2;
	float moveSpeed = 2;

	void AddController(int id);
	void RemoveController(int id);
	void PlayerMove(float x, float y, float z);
	void PlayerUpdate(float deltaTime);
	void PlayerShoot();
};

