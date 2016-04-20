#include "GLPlayer.h"
#include <math.h>
#include "RNG.h"

GLPlayer::GLPlayer() : GLModel()
{
	this->m_camera;
	this->m_projectileHandler = new GLProjectileHandler(1, 20, 10.0f);
	this->m_velocity = glm::vec3(0);
	
}

GLPlayer::GLPlayer(FishBox& FSH_Loader, char* filePath) : GLModel(FSH_Loader, filePath) //DEPRICATED USE AT OWN RISK
{
	this->m_camera;
	this->m_projectile = new GLProjectile(10, 20.0f);
	this->m_projectileHandler = new GLProjectileHandler(1, 20, 10.0f);
	this->m_velocity = glm::vec3(0);
}

GLPlayer::GLPlayer(FishBox & FSH_Loader, unsigned int modelID) : GLModel(FSH_Loader, modelID)
{
	this->m_camera;
	this->m_projectileHandler = new GLProjectileHandler(1, 20, 10.0f);
	this->m_velocity = glm::vec3(0);
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

	if (this->transform->m_rot.x > glm::radians(MAX_ANGLE))
		this->transform->m_rot.x = glm::radians(MAX_ANGLE);
	if (this->transform->m_rot.x < -glm::radians(MAX_ANGLE))
		this->transform->m_rot.x = -glm::radians(MAX_ANGLE);

	float maxAngle = 0.785398;

	if (this->meshes[0]->GetTransform().m_rot.z <= maxAngle && this->meshes[0]->GetTransform().m_rot.z >= -maxAngle)
	{
		this->meshes[0]->GetTransform().m_rot.z += -(lastHorizontal / (glm::pow(2, 15))) * deltaTime;
		//this->meshes[1]->GetTransform().m_rot.z += -(lastHorizontal / (glm::pow(2, 15))) * deltaTime;
	}
		
	this->meshes[0]->GetTransform().m_rot.z -= this->meshes[0]->GetTransform().m_rot.z * deltaTime;
	//this->meshes[1]->GetTransform().m_rot.z -= this->meshes[0]->GetTransform().m_rot.z * deltaTime;

	if (m_velocity != glm::vec3(0))
	{
		this->transform->m_pos += (m_velocity  * deltaTime);
		glm::vec3 friction = (m_velocity * MOVEMENT_FRICTION);
		m_velocity -= friction * deltaTime;
	}

	glm::vec3 forward = this->GetForward();
	m_velocity += forward * (float)(lastForward / (glm::pow(2, 15)));

	//camera update
	this->m_camera.Update(this->GetTransform(), deltaTime);

	//this->m_projectile->TestUpdate(deltaTime);
	this->m_projectileHandler->Update(deltaTime);
}

void GLPlayer::PlayerShoot()
{
	this->m_projectileHandler->Shoot(this->GetForward(), transform->m_pos, transform->m_rot);
	/*if (!this->m_projectile->isActive())
	{
		this->m_projectile->SetForward(this->GetForward());
		this->m_projectile->ResetTo(this->transform->m_pos);
		this->m_projectile->GetTransform().m_rot = this->transform->m_rot;
		this->m_projectile->Activate();
	}*/
}
void GLPlayer::PlayerEating(float deltaTime)
{
	glm::vec3 scaleIncrease = this->transform->GetScale() + (deltaTime / 4);
	this->transform->SetScale(scaleIncrease);
}