#include "GLPlayer.h"
#include <math.h>
#include "RNG.h"

GLPlayer::GLPlayer() : GLModel() //NEVER USE
{
	this->m_camera;
	this->m_projectileHandler = new GLProjectileHandler();
	this->m_velocity = glm::vec3(0);
	
	this->dashCurrentDuration = 0.0f;
	this->dashDuration = 0.2f;
	this->dashCooldown = 5;
	this->dashCooldownCounter = 0;
	this->isDashing = false;
	this->dashOnCooldown = false;
	this->currentPowerUp = POWER_NEUTRAL;
}

GLPlayer::GLPlayer(FishBox* FSH_Loader, char* filePath) : GLModel(FSH_Loader, filePath) //DEPRICATED USE AT OWN RISK
{
	this->m_camera;
	this->m_projectileHandler = new GLProjectileHandler(FSH_Loader, 2, 1, 20, 10.0f);
	this->m_velocity = glm::vec3(0);
}

GLPlayer::GLPlayer(FishBox * FSH_Loader, unsigned int modelID) : GLModel(FSH_Loader, modelID)
{
	this->m_camera;
	this->m_projectileHandler = new GLProjectileHandler(FSH_Loader, 2, 1, 20, 20.0f);
	this->m_velocity = glm::vec3(0);
	
	this->dashCurrentDuration = 0.0f;
	this->dashCooldownCounter = 0;
	this->isDashing = false;
	this->dashOnCooldown = false;
	blendWeights = new float[NUM_ANIMATION];
	for (int i = 0; i < NUM_ANIMATION; i++)
	{
		blendWeights[i] = 0.0f;
		animationFactors[i] = 0.0f;
	}
}

GLPlayer::GLPlayer(FishBox * FSH_Loader, unsigned int modelID, unsigned int projectileModelID) : GLModel(FSH_Loader, modelID)
{
	this->m_camera;
	this->m_projectileHandler = new GLProjectileHandler(FSH_Loader, projectileModelID, 1, 2, 20.0f);
	this->m_velocity = glm::vec3(0);

	this->dashCurrentDuration = 0.0f;
	this->dashCooldownCounter = 0;
	this->isDashing = false;
	this->dashOnCooldown = false;
	blendWeights = new float[NUM_ANIMATION];
	for (int i = 0; i < NUM_ANIMATION; i++)
		blendWeights[i] = 0.0f;
}


GLPlayer::~GLPlayer()
{
	delete this->m_projectileHandler;
	delete[] this->blendWeights;
}

//handles events sent too the player // movement.x = deltaTime
void GLPlayer::Update(Events state, glm::vec3 movementVec)
{
	switch (state)
	{
	case CAMERA_MOVE:
		m_camera.SetInput((movementVec.x == 0) ? -1 : movementVec.x, (movementVec.y == 0)? -1: movementVec.y);
		break;
	case PLAYER_MOVE:
		this->PlayerMove((movementVec.x == 0) ? -1 : movementVec.x, (movementVec.y == 0) ? -1 : movementVec.y, (movementVec.z == 0) ? -1 : movementVec.z);
		break;
	case PLAYER_SHOOT:
		this->PlayerShoot();
		break;
	case PLAYER_DASH:
		this->PlayerDash();
		break;
	case JOY_ADDED:
		this->AddController((int)movementVec.x);
		break;
	case JOY_REMOVED:
		this->RemoveController((int)movementVec.x);
		break;
	case NOTHING:
		this->PlayerUpdate(movementVec.x);
		break;
	default:
		break;
	}
	
}

GLCamera GLPlayer::GetCamera()
{
	return this->m_camera;
}

void GLPlayer::TestDraw(GLShader & shader)
{
	this->Draw(shader);
	
}

void GLPlayer::DrawProjectile(GLShader & shader)
{
	this->m_projectileHandler->Draw(shader);
}

void GLPlayer::HandleCollision(PlayerStates state, float deltaTime, glm::vec3 momentum)
{
	switch (state)
	{
	case MOVING:
		this->m_velocity = momentum;
	break;
	case EATING:
		if (momentum.x > 0)
		{
			this->transform->SetScale(this->transform->GetScale() + (deltaTime / 4));
			totalPoints += (int)(100 * momentum.x);
			currentPoints += (int)(100 * momentum.x);
		}
		if (momentum.x < 0 && (totalPoints + 100 * momentum.x) >= 0)
		{
			this->transform->SetScale(this->transform->GetScale() + (deltaTime / 4));
			totalPoints += (int)(100 * momentum.x);
			currentPoints += (int)(100 * momentum.x);
			std::cout << totalPoints << " : " << 100 * momentum.x << std::endl;
		}
		break;
	case HIT:
		this->m_velocity += momentum;
		break;
	break;
	}
}

std::vector<GLProjectile*> GLPlayer::GetProjectiles()
{
	return this->m_projectileHandler->GetActiveProjectiles();
}

glm::vec3 GLPlayer::GetVelocity()
{
	return this->m_velocity;
}

GLPlayer::PowerUps GLPlayer::GetPowerUp()
{
	return this->currentPowerUp;
}

void GLPlayer::SetPowerUp(GLPlayer::PowerUps power)
{
	this->currentPowerUp = power;
	this->HandlePowerUps();
	this->powerUpTimer = 0.0f;
}

void GLPlayer::SetRandomPowerUp()
{
	int random = RNG::range(0,2);
	this->currentPowerUp = this->getPowerUpByNumber(random);
	this->HandlePowerUps();
	this->powerUpTimer = 0.0f;
}

void GLPlayer::ResetPlayer()
{
	this->m_velocity = glm::vec3(0);

	this->dashCurrentDuration = 0.0f;
	this->dashDuration = 0.2f;
	this->dashCooldown = 5;
	this->dashCooldownCounter = 0;
	this->isDashing = false;
	this->dashOnCooldown = false;
	this->currentPowerUp = POWER_NEUTRAL;
	this->HandlePowerUps();
	this->totalPoints = 0;

	this->lastForward = 0;
	this->lastHorizontal = 0;
	this->lastVertical = 0;

	this->powerUpTimer = 0.0f;
}

int GLPlayer::GetPoints()
{
	if (currentPoints > 0)
	{
		if (currentPoints % 10 == 0)
		{
			currentPoints -= 10;
			return 10;
		}
		else
		{
			currentPoints -= 1;
			return 1;
		}

	}
	if (currentPoints < 0)
	{
		if (currentPoints % 10 == 0)
		{
			currentPoints += 10;
			return -10;
		}
		else
		{
			currentPoints += 1;
			return -1;
		}

	}
	return 0;
}

int GLPlayer::GetTotalPoints()
{
	return this->totalPoints;
}

void GLPlayer::Update(float dt)
{
	this->deltaTime = dt;
	this->PowerUpCoolDown();
}


void GLPlayer::moveAnimation(float deltaTime, float speedFactor)
{
	float speed = abs(deltaTime * speedFactor), y;

	//static float x = 0.0f;
	animationFactors[AONE] += speed;

	y = sin(animationFactors[AONE]);
	if (y > 0.0)
		this->blendWeights[ASIX] = y;
	if (y < 0.0)
		this->blendWeights[ASEVEN] = abs(y);
	//if (fabs(x - PI) <= FLT_EPSILON)
	//	x = 0.0;

	blendWeights[AFIVE] = 1.0f;
}

void GLPlayer::idleAnimation(float deltaTime, float speedFactor)
{
	float speed = deltaTime * speedFactor;

	for (size_t i = 0; i < NUM_ANIMATION; i++)
	{
		if (blendWeights[i] > 0.0f)
		{
			blendWeights[i] -= speed;
			animationFactors[i] = 0.0f;
		}
	}
}

//adds a controller too the player
void GLPlayer::AddController(int id)
{
	if (SDL_IsGameController(id)) {
		pad = SDL_GameControllerOpen(id);
		if (pad)
		{
			_SDL_Joystick *joy = SDL_GameControllerGetJoystick(pad);
			instanceID = SDL_JoystickInstanceID(joy);
		}
	}
}
//removes the controller
void GLPlayer::RemoveController(int id)
{
	SDL_GameControllerFromInstanceID(id);
}

void GLPlayer::PlayerMove(float x, float y, float z)
{
	if ((x < -DEADZONE || x > DEADZONE))
	{
		lastHorizontal = -x;
	}
	else if (x != -1)
	{
		lastHorizontal = 0;
	}
	if ((y < -DEADZONE || y > DEADZONE))
	{
		lastVertical = y;
	}
	else if (y != -1)
	{
		lastVertical = 0;
	}
	if ((z < -DEADZONE || z > DEADZONE))
	{
		lastForward = z;
	}
	else if (z != -1)
	{
		lastForward = 0;
	}
}

void GLPlayer::PlayerUpdate(float deltaTime)
{
	//player update
	glm::vec3 v = glm::vec3((lastVertical / (MAX_INPUT)), (lastHorizontal / (MAX_INPUT)),0);
	this->transform->m_rot += (v * rotateSpeed * deltaTime);

	if (this->transform->m_rot.x > glm::radians(MAX_ANGLE))
		this->transform->m_rot.x = glm::radians(MAX_ANGLE);
	if (this->transform->m_rot.x < -glm::radians(MAX_ANGLE))
		this->transform->m_rot.x = -glm::radians(MAX_ANGLE);

	float maxAngle = 0.785398f;

	if (this->meshes[0]->GetTransform().m_rot.z <= maxAngle && this->meshes[0]->GetTransform().m_rot.z >= -maxAngle)
	{
		this->meshes[0]->GetTransform().m_rot.z += -(lastHorizontal / (MAX_INPUT)) * deltaTime;
		//this->meshes[1]->GetTransform().m_rot.z += -(lastHorizontal / (glm::pow(2, 15))) * deltaTime;
	}
		
	this->meshes[0]->GetTransform().m_rot.z -= this->meshes[0]->GetTransform().m_rot.z * deltaTime;
	//this->meshes[1]->GetTransform().m_rot.z -= this->meshes[0]->GetTransform().m_rot.z * deltaTime;
	
	//std::cout << "X: " << this->m_velocity.x << " Y: " << this->m_velocity.y << " Z: " << this->m_velocity.z << std::endl;

	if (lastForward > DEADZONE)
		moveAnimation(deltaTime, sqrt(glm::dot(m_velocity, m_velocity)));

	CalcVelocity(deltaTime);
	HandleDash(deltaTime);

	idleAnimation(deltaTime, 2.0f);

	//camera update
	this->m_camera.Update(this->GetTransform(), deltaTime);

	this->m_projectileHandler->Update(deltaTime);
}

void GLPlayer::PlayerShoot()
{
	this->m_projectileHandler->Shoot(GetForward(), transform->m_pos, transform->m_rot, m_velocity, GetRight(), GetUp());
}
void GLPlayer::PlayerDash()
{
	if (!isDashing && !dashOnCooldown)
	{
		isDashing = true;
		dashCurrentDuration = 0.0f;
		dashCooldownCounter = 0.0f;
		//lastForward = 32768.0f;
	}
}

void GLPlayer::PowerUpCoolDown()
{
	if (this->currentPowerUp != PowerUps::POWER_NEUTRAL)
	{
		this->powerUpTimer += this->deltaTime;


		if (this->powerUpTimer >= 5)
		{
			int k = 0;
			this->currentPowerUp = PowerUps::POWER_NEUTRAL;
			this->powerUpTimer = 0.0f;
			this->HandlePowerUps();
		}
	}
}

void GLPlayer::CalcVelocity(float& deltaTime)
{
	glm::vec3 forward = this->GetForward();
	if (m_velocity != glm::vec3(0))
	{
		if (isDashing)
		{
			if (glm::dot(m_velocity, m_velocity) < MAX_DASHSPEED)
			{
				m_velocity += forward * DASH_SCALE;
			}
			// If VALUE > MAX_SPEED set it to MAX_SPEED else if VALUE < -MAX_SPEED set it to -MAX_SPEED else keep VALUE
			//m_velocity.x = (m_velocity.x > MAX_DASHSPEED) ? MAX_DASHSPEED : (m_velocity.x < -MAX_DASHSPEED) ? -MAX_DASHSPEED : m_velocity.x;
			//m_velocity.y = (m_velocity.y > MAX_DASHSPEED) ? MAX_DASHSPEED : (m_velocity.y < -MAX_DASHSPEED) ? -MAX_DASHSPEED : m_velocity.y;
			//m_velocity.z = (m_velocity.z > MAX_DASHSPEED) ? MAX_DASHSPEED : (m_velocity.z < -MAX_DASHSPEED) ? -MAX_DASHSPEED : m_velocity.z;
		}
		else if(!isDashing)
		{
			// If VALUE > MAX_SPEED set it to MAX_SPEED else if VALUE < -MAX_SPEED set it to -MAX_SPEED else keep VALUE
			//m_velocity.x = (m_velocity.x > MAX_SPEED) ? MAX_SPEED : (m_velocity.x < -MAX_SPEED) ? -MAX_SPEED : m_velocity.x;
			//m_velocity.y = (m_velocity.y > MAX_SPEED) ? MAX_SPEED : (m_velocity.y < -MAX_SPEED) ? -MAX_SPEED : m_velocity.y;
			//m_velocity.z = (m_velocity.z > MAX_SPEED) ? MAX_SPEED : (m_velocity.z < -MAX_SPEED) ? -MAX_SPEED : m_velocity.z;
			
		}
		

		this->transform->m_pos += (m_velocity  * deltaTime);
		glm::vec3 friction = (m_velocity * MOVEMENT_FRICTION);
		m_velocity -= friction * deltaTime;

		
	}

	if (glm::dot(m_velocity, m_velocity) < MAX_SPEED)
	{
		m_velocity += forward * (float)(lastForward / (MAX_INPUT));
	}
	m_velocity.x = (glm::abs(m_velocity.x) < MIN_SPEED) ? 0.0f : m_velocity.x;
	m_velocity.y = (glm::abs(m_velocity.y) < MIN_SPEED) ? 0.0f : m_velocity.y;
	m_velocity.z = (glm::abs(m_velocity.z) < MIN_SPEED) ? 0.0f : m_velocity.z;
}

void GLPlayer::HandleDash(float & deltaTime)
{
	if (isDashing)
	{
		m_camera.AddDistance(MOVE_CAM_DISTANCE * deltaTime);
		dashCurrentDuration += deltaTime;
		if (dashCurrentDuration >= DASH_DURATION)
		{
			isDashing = false;
			dashOnCooldown = true;
			dashCurrentDuration = DASH_DURATION;
		}
	}
	else if (dashOnCooldown)
	{
		if (dashCurrentDuration >= 0)
		{
			m_camera.DecreaseDistance(MOVE_CAM_DISTANCE * deltaTime);
			dashCurrentDuration -= deltaTime;
		}
		dashCooldownCounter += deltaTime;
		if (DASH_COOLDOWN <= dashCooldownCounter)
		{
			dashOnCooldown = false;
			dashCooldownCounter = 0.0f;
			//lastForward = 0.0f;
		}
	}
}

void GLPlayer::HandlePowerUps()
{
	if (this->currentPowerUp == GLPlayer::POWER_BUBBLESHOTGUN)
		this->m_projectileHandler->ChangeStateTo(ProjectilePowerUpState::SHOTGUN);
	else if (this->currentPowerUp == GLPlayer::POWER_BUBBLEBIG)
		this->m_projectileHandler->ChangeStateTo(ProjectilePowerUpState::BIG);
	else
		this->m_projectileHandler->ChangeStateTo(ProjectilePowerUpState::REGULAR);
}

GLPlayer::PowerUps GLPlayer::getPowerUpByNumber(int power)
{
	GLPlayer::PowerUps powerUp;
	switch (power)
	{
	case 0:
		powerUp = POWER_BUBBLESHOTGUN;
		break;
	case 1:
		powerUp = POWER_BUBBLEBIG;
		break;
	case 2:
		powerUp = POWER_HIGH;
		break;
	default:
		powerUp = POWER_NEUTRAL;
		break;
	}
	return powerUp;
}

void GLPlayer::PlayerEating(float deltaTime)
{

}