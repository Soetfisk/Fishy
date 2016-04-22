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
		MOVING,
		HIT,
		EATING,

		NUM_PLAYERSTATES
	};

	GLPlayer();
	GLPlayer(FishBox& FSH_Loader, char* filePath);
	GLPlayer(FishBox& FSH_Loader, unsigned int modelID);
	~GLPlayer();
	void Update(Events state, glm::vec3 movementVec);
	GLCamera GetCamera();
	glm::vec3& getVelocity() {
		return m_velocity;
	}

	void PlayerEating(float deltaTime);
	void TestDraw(GLShader& shader);
	void HandleCollision(PlayerStates state, glm::vec3 momentum);
	std::vector<GLProjectile*>& GetProjectiles();
	glm::vec3 GetVelocity();
	
private:
	const int DEADZONE = 8000;
	float MOVEMENT_FRICTION = 2.0f;
	const int MAX_SPEED = 10;
	const float MAX_ANGLE = 75;
	const int MAX_INPUT = glm::pow(2, 15);

	float lastHorizontal = 0;
	float lastVertical = 0;
	float lastForward = 0;
	glm::vec3 m_velocity;

	float dashDuration;
	float dashCurrentDuration;
	float dashCooldown;
	float dashCooldownCounter;
	bool isDashing;
	bool dashOnCooldown;

	SDL_GameController *pad;
	int instanceID;
	GLCamera m_camera;
	GLProjectileHandler* m_projectileHandler;

	float rotateSpeed = 2;
	float moveSpeed = 2;

	void AddController(int id);
	void RemoveController(int id);
	void PlayerMove(float x, float y, float z);
	void PlayerUpdate(float deltaTime);
	void PlayerShoot();
	void PlayerDash();

	void CalcVelocity(float& deltaTime);
	void HandleDash(float& deltaTime);
};

