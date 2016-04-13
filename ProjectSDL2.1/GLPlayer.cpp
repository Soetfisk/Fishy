#include "GLPlayer.h"


GLPlayer::GLPlayer() : GLModel()
{
	this->m_camera;
	this->m_projectile = new GLProjectile(10, 20.0f);
}


GLPlayer::~GLPlayer()
{
	delete this->m_projectile;
}

GLProjectile * GLPlayer::tempGetProjectile()
{
	return this->m_projectile;
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
		this->PlayerMove((movementVec.x == 0) ? -1 : movementVec.x, (movementVec.y == 0) ? -1 : movementVec.y);
		break;
	case PLAYER_SHOOT:
		this->PlayerShoot();
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

void GLPlayer::PlayerMove(float x, float y)
{
	if ((x < -DEADZONE || x > DEADZONE))
	{
		lastX = x;
	}
	else if (x != -1)
	{
		lastX = 0;
	}
	if ((y < -DEADZONE || y > DEADZONE))
	{
		lastY = y;
	}
	else if (y != -1)
	{
		lastY = 0;
	}
}

void GLPlayer::PlayerUpdate(float deltaTime)
{
	//player update
	this->GetTransform().m_pos += m_forward * (this->m_velocity.x * deltaTime);
	this->GetTransform().m_rot.y -= (this->m_velocity.z * deltaTime);

	if ((lastX < -DEADZONE || lastX > DEADZONE) && (this->m_velocity.z >= -MAX_SPEED && this->m_velocity.z <= MAX_SPEED))
	{
		this->m_velocity.z += lastX / (glm::pow(2, 15));
	}
	if ((lastY < -DEADZONE || lastY > DEADZONE) && (this->m_velocity.x >= -MAX_SPEED && this->m_velocity.x <= MAX_SPEED))
	{
		this->m_velocity.x += lastY / (glm::pow(2, 15));
	}

	if (m_velocity.x > 0) m_velocity.x = glm::max(m_velocity.x - MOVEMENT_FRICTION * deltaTime, 0.0f);
	//if (m_velocity.y > 0) m_velocity.y = glm::max(m_velocity.y - FRICTION * deltaTime, 0.0f);
	if (m_velocity.z > 0) m_velocity.z = glm::max(m_velocity.z - MOVEMENT_FRICTION * deltaTime, 0.0f);
	if (m_velocity.x < 0) m_velocity.x = glm::min(m_velocity.x + MOVEMENT_FRICTION * deltaTime, 0.0f);
	//if (m_velocity.y < 0) m_velocity.y = glm::min(m_velocity.y + FRICTION * deltaTime, 0.0f);
	if (m_velocity.z < 0) m_velocity.z = glm::min(m_velocity.z + MOVEMENT_FRICTION * deltaTime, 0.0f);

	glm::vec3 front;
	front.x = cos(this->transform->m_rot.x) * sin(this->transform->m_rot.y);
	front.y = sin(this->transform->m_rot.x);
	front.z = cos(this->transform->m_rot.x) * cos(this->transform->m_rot.y);
	m_forward = glm::normalize(front);

	//camera update
	this->m_camera.Update(this->GetTransform(), deltaTime);

	this->m_projectile->TestUpdate(deltaTime);
}

void GLPlayer::PlayerShoot()
{
	if (!this->m_projectile->isActive())
	{
		this->m_projectile->SetForward(m_forward);
		this->m_projectile->ResetTo(this->transform->m_pos);
		this->m_projectile->GetTransform().m_rot = this->transform->m_rot;
		this->m_projectile->Activate();
	}
}
