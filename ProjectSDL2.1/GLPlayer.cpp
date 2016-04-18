#include "GLPlayer.h"
#include <math.h>


GLPlayer::GLPlayer() : GLModel()
{
	this->m_camera;
	this->m_projectile = new GLProjectile(10, 20.0f);
	this->m_projectileHandler = new GLProjectileHandler(1, 10, 1.0f);
	this->m_velocity = glm::vec3(0);
}


GLPlayer::~GLPlayer()
{
	delete this->m_projectile;
	delete this->m_projectileHandler;
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
		this->PlayerMove((movementVec.x == 0) ? -1 : movementVec.x, (movementVec.y == 0) ? -1 : movementVec.y, (movementVec.z == 0) ? -1 : movementVec.z);
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

void GLPlayer::TestDraw(GLShader & shader)
{
	this->Draw(shader);
	this->m_projectileHandler->Draw(shader);
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
	glm::vec3 v = glm::vec3((lastVertical / (glm::pow(2, 15))), (lastHorizontal / (glm::pow(2, 15))),0);
	this->transform->m_rot += (v * rotateSpeed * deltaTime);

	float maxAngle = 0.785398;

	if (this->meshes[0]->GetTransform().m_rot.z <= maxAngle && this->meshes[0]->GetTransform().m_rot.z >= -maxAngle)
	{
		this->meshes[0]->GetTransform().m_rot.z += -(lastHorizontal / (glm::pow(2, 15))) * deltaTime;
		this->meshes[1]->GetTransform().m_rot.z += -(lastHorizontal / (glm::pow(2, 15))) * deltaTime;
	}
		
	this->meshes[0]->GetTransform().m_rot.z -= this->meshes[0]->GetTransform().m_rot.z * deltaTime;
	this->meshes[1]->GetTransform().m_rot.z -= this->meshes[0]->GetTransform().m_rot.z * deltaTime;

	
	glm::vec3 forward = this->GetForward();
	m_velocity += forward * (float)(lastForward / (glm::pow(2, 15)));
	if (m_velocity != glm::vec3(0))
	{
		this->transform->m_pos += (m_velocity  * deltaTime);
		m_velocity -= (m_velocity * (MOVEMENT_FRICTION * deltaTime));
	}

	//camera update
	this->m_camera.Update(this->GetTransform(), deltaTime);

	//this->m_projectile->TestUpdate(deltaTime);
	this->m_projectileHandler->Update(deltaTime);
}

void GLPlayer::PlayerShoot()
{
	this->m_projectileHandler->Shoot(m_forward, transform->m_pos, transform->m_rot);
	/*if (!this->m_projectile->isActive())
	{
		this->m_projectile->SetForward(this->GetForward());
		this->m_projectile->ResetTo(this->transform->m_pos);
		this->m_projectile->GetTransform().m_rot = this->transform->m_rot;
		this->m_projectile->Activate();
	}*/
}
//
//this->GetTransform().m_pos += m_forward * (this->m_velocity.x * deltaTime);
//this->GetTransform().m_pos.x = sin(this->m_velocity.x) * 0.01;
//this->GetTransform().m_rot.y -= (this->m_velocity.z * deltaTime);
//
//if ((lastX < -DEADZONE || lastX > DEADZONE) && (this->m_velocity.z >= -MAX_SPEED && this->m_velocity.z <= MAX_SPEED))
//{
//	this->m_velocity.z += lastX / (glm::pow(2, 15));
//}
//if ((lastY < -DEADZONE || lastY > DEADZONE) && (this->m_velocity.x >= -MAX_SPEED && this->m_velocity.x <= MAX_SPEED))
//{
//	this->m_velocity.x += lastY / (glm::pow(2, 15));
//}
//
//if (m_velocity.x > 0) m_velocity.x = glm::max(m_velocity.x - MOVEMENT_FRICTION * deltaTime, 0.0f);
////if (m_velocity.y > 0) m_velocity.y = glm::max(m_velocity.y - FRICTION * deltaTime, 0.0f);
//if (m_velocity.z > 0) m_velocity.z = glm::max(m_velocity.z - MOVEMENT_FRICTION * deltaTime, 0.0f);
//if (m_velocity.x < 0) m_velocity.x = glm::min(m_velocity.x + MOVEMENT_FRICTION * deltaTime, 0.0f);
////if (m_velocity.y < 0) m_velocity.y = glm::min(m_velocity.y + FRICTION * deltaTime, 0.0f);
//if (m_velocity.z < 0) m_velocity.z = glm::min(m_velocity.z + MOVEMENT_FRICTION * deltaTime, 0.0f);
