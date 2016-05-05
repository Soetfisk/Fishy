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

	enum PowerUps
	{
		POWER_NEUTRAL,
		POWER_BUBBLESHOTGUN,
		POWER_BUBBLEBIG,
		POWER_BUBBLEFAST,
		POWER_BUBBLESTRONG,
		POWER_HIGH,

		NUM_POWERUPS
	};

	GLPlayer();
	GLPlayer(FishBox * FSH_Loader, char* filePath);
	GLPlayer(FishBox * FSH_Loader, unsigned int modelID);
	GLPlayer(FishBox * FSH_Loader, unsigned int modelID, unsigned int projectileModelID);
	~GLPlayer();
	void Update(Events state, glm::vec3 movementVec);
	GLCamera GetCamera();

	void PlayerEating(float deltaTime);
	void TestDraw(GLShader& shader);
	void HandleCollision(PlayerStates state, float deltaTime, glm::vec3 momentum);
	std::vector<GLProjectile*> GetProjectiles();
	glm::vec3 GetVelocity();
	GLPlayer::PowerUps GetPowerUp();
	void SetPowerUp(GLPlayer::PowerUps power);
	void SetRandomPowerUp();
	void ResetPlayer();
	int GetPoints();
	int GetTotalPoints();

	glm::vec3& getVelocity() {
		return m_velocity;
	}
private:
	const int	DEADZONE = 8000;
	float		MOVEMENT_FRICTION = 2.0f;
	const int	MAX_SPEED = 200;	
	const float MIN_SPEED = 0.1f;
	const int	MAX_DASHSPEED = 400;				
	const float DASH_DURATION = 0.5f;			// Dash duration in sec
	const float DASH_COOLDOWN = 1.0f;			// Dash cooldown in sec
	const float DASH_SCALE = 2.0f;				// 
	const float MOVE_CAM_DISTANCE = 5.0f;		// (MOVE_CAM_DISTANCE * deltaTime) == Distnace camera is moved each update during and after dash
	const float MAX_ANGLE = 75;
	const int	MAX_INPUT = glm::pow(2, 15);

	float lastHorizontal = 0;
	float lastVertical = 0;
	float lastForward = 0;
	glm::vec3 m_velocity;
	unsigned int currentPoints = 0;
	unsigned int totalPoints = 0;

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

	PowerUps currentPowerUp = POWER_NEUTRAL;

	void AddController(int id);
	void RemoveController(int id);
	void PlayerMove(float x, float y, float z);
	void PlayerUpdate(float deltaTime);
	void PlayerShoot();
	void PlayerDash();

	void CalcVelocity(float& deltaTime);
	void HandleDash(float& deltaTime);

	void HandlePowerUps();
	PowerUps getPowerUpByNumber(int power);
};

