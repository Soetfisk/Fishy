#include "GLPlayer.h"
#include <math.h>
#include "RNG.h"

GLPlayer::GLPlayer() : GLModel() //NEVER USE
{
	sound[SHOOT_SOUND] = Mix_LoadWAV("./res/Sounds/shoot.wav");
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
	this->playEat = false;
}



GLPlayer::GLPlayer(FishBox * FSH_Loader, unsigned int modelID, unsigned int projectileModelID) : GLModel(FSH_Loader, modelID)
{
	sound[SHOOT_SOUND] = Mix_LoadWAV("./res/Sounds/shoot.wav");
	this->m_camera;
	this->m_projectileHandler = new GLProjectileHandler(FSH_Loader, projectileModelID, 1, 2, 20.0f);
	this->m_velocity = glm::vec3(0);

	this->dashCurrentDuration = 0.0f;
	this->dashCooldownCounter = 0;
	this->isDashing = false;
	this->dashOnCooldown = false;
	this->blendWeights = new float[NUM_ANIMATION];
	this->playEat = false;
	for (int i = 0; i < NUM_ANIMATION; i++)
	{
		blendWeights[i] = 0.0f;
		animationFactors[i] = 0.0f;
	}
}


GLPlayer::~GLPlayer()
{
	for (int i = 0; i < NUM_SOUND; i++)
	{
		Mix_FreeChunk(sound[i]);
	}
	delete this->m_projectileHandler;
	delete[] this->blendWeights;
}

//handles events sent too the player // movement.x = deltaTime
void GLPlayer::Update(Events state, glm::vec3 movementVec)
{
	switch (state)
	{
	case PLAYER_MOVE_RIGHT:
		this->PlayerMove(-1, -1, -1, (movementVec.x == 0) ? -1 : movementVec.x, (movementVec.y == 0) ? -1 : movementVec.y);
		break;
	case PLAYER_MOVE_LEFT:
		this->PlayerMove((movementVec.x == 0) ? -1 : movementVec.x, (movementVec.y == 0) ? -1 : movementVec.y, (movementVec.z == 0) ? -1 : movementVec.z, -1, -1);
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
			size += momentum.x;
			totalPoints += (int)(100 * momentum.x);
			currentPoints += (int)(100 * momentum.x);
		}
		if (momentum.x < 0 && (totalPoints + 100 * momentum.x) >= 0)
		{
			size += momentum.x;
			totalPoints += (int)(100 * momentum.x);
			currentPoints += (int)(100 * momentum.x);
		}
		playEat = true;
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



void GLPlayer::resetMoveAnimation(float deltaTime, float speedFactor)
{
	float speed = deltaTime * speedFactor;


	if (blendWeights[ASIX] > 0.0f)
	{
		blendWeights[ASIX] -= speed;
		animationFactors[ASIX] = 0.0f;
		if (blendWeights[ASIX] < 0.0f)
			blendWeights[ASIX] = 0.0f;
	}
	else if (blendWeights[ASEVEN] > 0.0f)
	{
		blendWeights[ASEVEN] -= speed;
		animationFactors[ASEVEN] = 0.0f;
		if (blendWeights[ASEVEN] < 0.0f)
			blendWeights[ASEVEN] = 0.0f;
	}
}

void GLPlayer::resetHeadAnimation(float deltaTime, float speedFactor, int axis) // 0 = horizontal, 2 = vertical
{
	float speed = deltaTime * speedFactor;


	if (axis == 0) // handle horizontal
	{
		if (blendWeights[AONE] > 0.0f)
		{
			blendWeights[AONE] -= speed;
			animationFactors[AONE] = 0.0f;
			if (blendWeights[AONE] < 0.0f)
			{
				blendWeights[AONE] = 0.0f;
			}
		}
		if (blendWeights[AFOUR] > 0.0f)
		{
			blendWeights[AFOUR] -= speed;
			animationFactors[AFOUR] = 0.0f;
			if (blendWeights[AFOUR] < 0.0f)
			{
				blendWeights[AFOUR] = 0.0f;
			}
		}
	}

	if (axis == 1) // handle Vertical
	{
		if (blendWeights[ATWO] > 0.0f)
		{
			blendWeights[ATWO] -= speed;
			animationFactors[ATWO] = 0.0f;
			if (blendWeights[ATWO] < 0.0f)
			{
				blendWeights[ATWO] = 0.0f;
			}
		}
		if (blendWeights[ATHREE] > 0.0f)
		{
			blendWeights[ATHREE] -= speed;
			animationFactors[ATHREE] = 0.0f;
			if (blendWeights[ATHREE] < 0.0f)
			{
				blendWeights[ATHREE] = 0.0f;
			}
		}
	}




}


void GLPlayer::moveAnimation(float deltaTime, float speedFactor)
{
	float speed = abs(deltaTime * speedFactor), y;

	animationFactors[ASIX] += speed;

	y = sin(animationFactors[ASIX]);

	if (y > 0.0)
		this->blendWeights[ASIX] = y;
	if (y < 0.0)
		this->blendWeights[ASEVEN] = abs(y);

}

void GLPlayer::eatAnimation(float deltaTime, float speedFactor)
{
	// (sin(x-(3/2))+1)/2    // sine 0 -> 1 and back
	float speed = abs(deltaTime * speedFactor), y;

	animationFactors[ASIX] += speed;
	y = ((sin(animationFactors[ASIX] - (3 / 2))) + 1) / 2;
		
	blendWeights[ASIX] = animationFactors[ASIX];

	if (blendWeights[ASIX] <= 0.0f)
	{
		playEat = false;
		animationFactors[ASIX] = 0.0f;
	}
}

void GLPlayer::headAnimation(float deltaTime, float speedFactor, int direction)
{

	//horizontal

	if (direction == 0 && blendWeights[AONE] < 1.0) //head left
	{
		if (blendWeights[AFOUR] > 0.0)
		{
			animationFactors[AFOUR] -= abs(deltaTime * speedFactor);
			blendWeights[AFOUR] += animationFactors[AFOUR];
		}
		else if (blendWeights[AFOUR] < 0.0)
		{
			blendWeights[AFOUR] = 0.0f;
			animationFactors[AFOUR] = 0.0f;
		}

		else
		{
			animationFactors[AONE] += abs(deltaTime * speedFactor);
			blendWeights[AONE] += animationFactors[AONE];
		}
		if (animationFactors[AFOUR] >= 0.0f)
			animationFactors[AFOUR] = 0.0f;

	}

	else if (direction == 3 && blendWeights[AFOUR] < 1.0) //head right
	{
		if (blendWeights[AONE] > 0.0)
		{
			animationFactors[AONE] -= abs(deltaTime * speedFactor);
			blendWeights[AONE] += animationFactors[AONE];
		}
		else if (blendWeights[AONE] < 0.0)
		{
			blendWeights[AONE] = 0.0f;
			animationFactors[AONE] = 0.0f;
		}

		else
		{
			animationFactors[AFOUR] += abs(deltaTime * speedFactor);
			blendWeights[AFOUR] += animationFactors[AFOUR];
		}
		if (animationFactors[AONE] >= 0.0f)
			animationFactors[AONE] = 0.0f;
	}


	//vertical
	if (direction == 1 && blendWeights[ATHREE] < 1.0) //head up
	{
		if (blendWeights[ATWO] > 0.0)
		{
			animationFactors[ATWO] -= abs(deltaTime * speedFactor);
			blendWeights[ATWO] += animationFactors[ATWO];
		}
		else if (blendWeights[ATWO] < 0.0)
		{
			blendWeights[ATWO] = 0.0f;
			animationFactors[ATWO] = 0.0f;
		}

		else
		{
			animationFactors[ATHREE] += abs(deltaTime * speedFactor);
			blendWeights[ATHREE] += animationFactors[ATHREE];
		}
		if (animationFactors[ATWO] >= 0.0f)
			animationFactors[ATWO] = 0.0f;
	}
	else if (direction == 2 && blendWeights[ATWO] < 1.0) //head down
	{
		if (blendWeights[ATHREE] > 0.0)
		{
			animationFactors[ATHREE] -= abs(deltaTime * speedFactor);
			blendWeights[ATHREE] += animationFactors[ATHREE];
		}
		else if (blendWeights[ATHREE] < 0.0)
		{
			blendWeights[ATHREE] = 0.0f;
			animationFactors[ATHREE] = 0.0f;
		}

		else
		{
			animationFactors[ATWO] += abs(deltaTime * speedFactor);
			blendWeights[ATWO] += animationFactors[ATWO];
		}
		if (animationFactors[ATHREE] >= 0.0f)
			animationFactors[ATHREE] = 0.0f;

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

void GLPlayer::PlayerMove(float lx, float ly, float z, float rx, float ry)
{
	if ((lx < -DEADZONE || lx > DEADZONE))
	{
		lastHorizontal = -lx;
	}
	else if (lx != -1)
	{
		lastHorizontal = 0;
	}
	if ((ly < -DEADZONE || ly > DEADZONE))
	{
		lastVertical = -ly;
	}
	else if (ly != -1)
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
	if ((rx < -DEADZONE || rx > DEADZONE))
	{
		lastSide = -rx;
	}
	else if (rx != -1)
	{
		lastSide = 0;
	}
	if ((ry < -DEADZONE || ry > DEADZONE))
	{
		lastUp = ry;
	}
	else if (ry != -1)
	{
		lastUp = 0;
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
		

	if (abs(lastHorizontal) > DEADZONE)
	{
		if (lastHorizontal > 0.0)
			headAnimation(deltaTime, 0.25, 0);
		else if (lastHorizontal < 0.0)
			headAnimation(deltaTime, 0.25, 3);
	}
	else
		resetHeadAnimation(deltaTime, 3.0, 0);
	if (abs(lastVertical) > DEADZONE)
	{
		if (lastVertical > 0.0)
			headAnimation(deltaTime, 0.25, 1);
		else if (lastVertical < 0.0)
			headAnimation(deltaTime, 0.25, 2);
	}
	else
		resetHeadAnimation(deltaTime, 3.0, 1);
	if (playEat)
		eatAnimation(deltaTime, 3.0);

	this->meshes[0]->GetTransform().m_rot.z -= this->meshes[0]->GetTransform().m_rot.z * deltaTime;
	//this->meshes[1]->GetTransform().m_rot.z -= this->meshes[0]->GetTransform().m_rot.z * deltaTime;
	
	//std::cout << "X: " << this->m_velocity.x << " Y: " << this->m_velocity.y << " Z: " << this->m_velocity.z << std::endl;

	if (lastForward > DEADZONE)
		moveAnimation(deltaTime, sqrt(glm::dot(m_velocity, m_velocity)));
	else
		resetMoveAnimation(deltaTime, 2.0f);
	
	CalcVelocity(deltaTime);
	HandleDash(deltaTime);

	if (this->GetTransform().GetScale().x < size)
	{
		this->transform->SetScale(this->transform->GetScale() + (deltaTime / 4));
	}

	//camera update
	this->m_camera.Update(this->GetTransform(), deltaTime);

	this->m_projectileHandler->Update(deltaTime);
}

void GLPlayer::PlayerShoot()
{
	if (this->m_projectileHandler->CanShoot())
	{
		Mix_PlayChannel(-1, sound[SHOOT_SOUND], 0);
	}
	this->m_projectileHandler->Shoot(GetForward(), transform->m_pos, transform->m_rot, m_velocity, GetRight(), GetUp());
}
void GLPlayer::PlayerDash()
{
	if (!isDashing && !dashOnCooldown)
	{
		isDashing = true;
		dashCurrentDuration = 0.0f;
		dashCooldownCounter = 0.0f;
		lastForward = 32768.0f;
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
		m_velocity += this->GetUp() * (float)(lastUp / (MAX_INPUT));
		m_velocity += this->GetRight() * (float)(lastSide / (MAX_INPUT));
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
			lastForward = 0.0f;
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