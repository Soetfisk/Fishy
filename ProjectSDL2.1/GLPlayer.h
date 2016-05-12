#pragma once
#include "GLUtil.h"
#include "GLCamera.h"
#include "GLModel.h"
#include "GLProjectile.h"
#include "GLProjectileHandler.h"
#include "ParticleHandler.h"
#define PI  3.141592

class GLPlayer : public GLModel
{
public:
	enum Events
	{
		NOTHING,
		PLAYER_MOVE_RIGHT,
		PLAYER_MOVE_LEFT,
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
	enum Animations
	{
		AONE,
		ATWO,
		ATHREE,
		AFOUR,
		AFIVE,
		ASIX,
		ASEVEN,

		NUM_ANIMATION
	};

	GLPlayer();
	GLPlayer(FishBox * FSH_Loader, unsigned int modelID, unsigned int projectileModelID);
	~GLPlayer();
	void Update(Events state, glm::vec3 movementVec);
	GLCamera GetCamera();
	void PlayerEating(float deltaTime);
	void TestDraw(GLShader& shader);
	void DrawProjectile(GLShader& shader);
	void HandleCollision(PlayerStates state, float deltaTime, glm::vec3 momentum);
	std::vector<GLProjectile*> GetProjectiles();
	glm::vec3 GetVelocity();
	GLPlayer::PowerUps GetPowerUp();
	void SetPowerUp(GLPlayer::PowerUps power);
	void SetRandomPowerUp();
	void ResetPlayer();
	int GetPoints();
	int GetTotalPoints();
	void Update(float dt);
	float * GetBlendWeights() { return blendWeights; }
	unsigned int GetBlendShapeCount() { return NUM_ANIMATION; }
	glm::vec3& getVelocity() { return m_velocity; }


	void addParticleHandleRefernce(ParticleHandler* pHandlerReference);
	void DrawParticles(GLShader* shader);
	void UpdateParticles(float &deltaTime);

private:
	float speed;
	enum
	{
		SHOOT_SOUND,
		BIG_SHOOT_SOUND,
		SHOTGUN_SHOOT_SOUND,
		DASH_SOUND,
		MOVE_SOUND,
		EAT_SOUND,

		NUM_SOUND
	};
	bool isMoving = false;
	const int	DEADZONE = 10000;
	float		MOVEMENT_FRICTION = 2.0f;
	const int	MAX_SPEED = 200;	
	const float MIN_SPEED = 0.1f;
	int			MAX_DASHSPEED = 800;				
	float		DASH_DURATION = 0.5f;			// Dash duration in sec
	float		DASH_COOLDOWN = 3.0f;			// Dash cooldown in sec
	float		DASH_SCALE = 6.0f;				// 
	const float MOVE_CAM_DISTANCE = 5.0f;		// (MOVE_CAM_DISTANCE * deltaTime) == Distnace camera is moved each update during and after dash
	const float MAX_ANGLE = 75;
	const int	MAX_INPUT = (int)glm::pow(2, 15);

	float size = 1;
	float lastHorizontal = 0;
	float lastVertical = 0;
	float lastForward = 0;
	float lastSide = 0;
	float lastUp = 0;
	glm::vec3 m_velocity;
	int currentPoints = 0;
	unsigned int totalPoints = 0;

	float dashDuration;
	float dashCurrentDuration;
	float dashCooldown;
	float dashCooldownCounter;
	bool isDashing;
	bool dashOnCooldown;
	float powerUpCoolDown = 5;
	float powerUpTimer = 0;

	float * blendWeights;
	float animationFactors[NUM_ANIMATION];
	float deltaTime = -1;
	bool playEat;


	Mix_Chunk *sound[NUM_SOUND];
	SDL_GameController *pad;
	int instanceID;
	GLCamera m_camera;
	GLProjectileHandler* m_projectileHandler;

	float rotateSpeed = 2;
	float moveSpeed = 2;

	PowerUps currentPowerUp = POWER_NEUTRAL;

	void AddController(int id);
	void RemoveController(int id);
	void PlayerMove(float lx, float ly, float z, float rx, float ry);
	void PlayerUpdate(float deltaTime);
	void PlayerShoot();
	void PlayerDash();
	void PowerUpCoolDown();

	void CalcVelocity(float& deltaTime);
	void HandleDash(float& deltaTime);
	
	void moveAnimation(float deltaTime, float speedFactor);
	void resetMoveAnimation(float deltaTime, float speedFactor);
	void headAnimation(float deltaTime, float speedFactor, int direction);
	void resetHeadAnimation(float deltaTime, float speedFactor, int axis);
	void eatAnimation(float deltaTime, float speedFactor);

	void HandlePowerUps();
	PowerUps getPowerUpByNumber(int power);
	
	ParticleHandler *particleHandlerReference;
	ParticleEmitter *player_PartcileEmitter;
};

