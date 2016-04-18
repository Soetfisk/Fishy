#pragma once
#include "GLUtil.h"
#include "GLCamera.h"
#include "GLModel.h"
#include "GLProjectile.h"
#include "GLProjectileHandler.h"

class GLPlayer : public GLModel
{
public:
	enum Events
	{
		NOTHING,
		CAMERA_MOVE,
		PLAYER_MOVE,
		PLAYER_SHOOT,
		PLAYER_DASH,
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

	void TestDraw(GLShader& shader);
	
private:
	const int DEADZONE = 8000;
	const float MOVEMENT_FRICTION = 8.0f;
	const int MAX_SPEED = 10;
	const float MAX_ANGLE = 75;

	float lastHorizontal = 0;
	float lastVertical = 0;
	float lastForward = 0;
	glm::vec3 m_velocity;

	float dashDuration;
	float dashCurrentDuration;
	float dashMultiplier;
	bool isDashing;

	SDL_GameController *pad;
	int instanceID;
	GLCamera m_camera;
	GLProjectile *m_projectile;
	GLProjectileHandler* m_projectileHandler;

	float rotateSpeed = 2;
	float moveSpeed = 2;

	void AddController(int id);
	void RemoveController(int id);
	void PlayerMove(float x, float y, float z);
	void PlayerUpdate(float deltaTime);
	void PlayerShoot();
	void PlayerDash();
};

