#include "GLPlayer.h"
#include <math.h>
#include "RNG.h"

GLPlayer::GLPlayer() : GLModel()
{
	this->m_camera;
	this->m_projectileHandler = new GLProjectileHandler(1, 20, 10.0f);
	this->m_velocity = glm::vec3(0);
	
	this->dashCurrentDuration = 0.0f;
	this->dashDuration = 0.2f;
	this->dashCooldown = 5;
	this->dashCooldownCounter = 0;
	this->isDashing = false;
	this->dashOnCooldown = false;
}

GLPlayer::GLPlayer(FishBox& FSH_Loader, char* filePath) : GLModel(FSH_Loader, filePath) //DEPRICATED USE AT OWN RISK
{
	this->m_camera;
	this->m_projectileHandler = new GLProjectileHandler(1, 20, 10.0f);
	this->m_velocity = glm::vec3(0);
}

GLPlayer::GLPlayer(FishBox & FSH_Loader, unsigned int modelID) : GLModel(FSH_Loader, modelID)
{
	this->m_camera;
	this->m_projectileHandler = new GLProjectileHandler(1, 20, 10.0f);
	this->m_velocity = glm::vec3(0);
	
	this->dashCurrentDuration = 0.0f;
	this->dashDuration = 0.3f;
	this->dashCooldown = 1;
	this->dashCooldownCounter = 0;
	this->isDashing = false;
	this->dashOnCooldown = false;
}


GLPlayer::~GLPlayer()
{
	delete this->m_projectileHandler;
}

//handles events sent too the player
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
		this->AddController(movementVec.x);
		break;
	case JOY_REMOVED:
		this->RemoveController(movementVec.x);
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
	this->m_projectileHandler->Draw(shader);
}

void GLPlayer::HandleCollision(PlayerStates state, glm::vec3 momentum)
{
	switch (state)
	{
	case MOVING:
		this->m_velocity = momentum;
	break;
	case EATING:
		glm::vec3 scaleIncrease = this->transform->GetScale();// + (deltaTime / 4);
		this->transform->SetScale(scaleIncrease);
	break;
	}
}

std::vector<GLProjectile*>& GLPlayer::GetProjectiles()
{
	return this->m_projectileHandler->GetProjectiles();
}

glm::vec3 GLPlayer::GetVelocity()
{
	return this->m_velocity;
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

	float maxAngle = 0.785398;

	if (this->meshes[0]->GetTransform().m_rot.z <= maxAngle && this->meshes[0]->GetTransform().m_rot.z >= -maxAngle)
	{
		this->meshes[0]->GetTransform().m_rot.z += -(lastHorizontal / (MAX_INPUT)) * deltaTime;
		//this->meshes[1]->GetTransform().m_rot.z += -(lastHorizontal / (glm::pow(2, 15))) * deltaTime;
	}
		
	this->meshes[0]->GetTransform().m_rot.z -= this->meshes[0]->GetTransform().m_rot.z * deltaTime;
	//this->meshes[1]->GetTransform().m_rot.z -= this->meshes[0]->GetTransform().m_rot.z * deltaTime;
	
	CalcVelocity(deltaTime);
	HandleDash(deltaTime);

	//camera update
	this->m_camera.Update(this->GetTransform(), deltaTime);

	//this->m_projectile->TestUpdate(deltaTime);
	this->m_projectileHandler->Update(deltaTime);
}

void GLPlayer::PlayerShoot()
{
	this->m_projectileHandler->Shoot(this->GetForward(), transform->m_pos, transform->m_rot);
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

void GLPlayer::CalcVelocity(float& deltaTime)
{
	if (m_velocity != glm::vec3(0))
	{
		if (isDashing)
			m_velocity += m_velocity * 0.2f;

		this->transform->m_pos += (m_velocity  * deltaTime);
		glm::vec3 friction = (m_velocity * MOVEMENT_FRICTION);
		m_velocity -= friction * deltaTime;
	}

	glm::vec3 forward = this->GetForward();
	m_velocity += forward * (float)(lastForward / (MAX_INPUT));
}

void GLPlayer::HandleDash(float & deltaTime)
{
	if (isDashing)
	{
		m_camera.AddDistance(5 * deltaTime);
		dashCurrentDuration += deltaTime;
		this->PlayerMove(0, 0, (MAX_INPUT - MAX_INPUT * dashCurrentDuration / dashDuration));
		if (dashCurrentDuration >= dashDuration)
		{
			//dashCurrentDuration = 0.0f;
			isDashing = false;
			dashOnCooldown = true;
		}
	}
	else if (dashOnCooldown)
	{
		if (dashCurrentDuration >= 0)
		{
			m_camera.DecreaseDistance(5 * deltaTime);
			dashCurrentDuration -= deltaTime;
		}
		dashCooldownCounter += deltaTime;
		//this->PlayerMove(0, 0, (MAX_INPUT - MAX_INPUT * dashCurrentDuration / dashDuration));
		std::cout << dashCooldownCounter << std::endl;;
		if (dashCooldown <= dashCooldownCounter)
		{
			dashOnCooldown = false;
			dashCooldownCounter = 0.0f;
		}
	}
}

void GLPlayer::PlayerEating(float deltaTime)
{
	
}