#include "GLPlayer.h"
#include "obj_loader.h"


GLPlayer::GLPlayer()
{
	this->m_camera;
	this->tempMesh = objLoadFromFile("./res/OBJ/box2.obj");
}


GLPlayer::~GLPlayer()
{
}

void GLPlayer::tempDraw()
{
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

GLMesh * GLPlayer::tempGetMesh()
{
	return this->tempMesh;
}

void GLPlayer::tempEvent()
{
	SDL_PumpEvents();
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{

		if (e.type == SDL_CONTROLLERDEVICEADDED)
		{
			Update(JOY_ADDED, glm::vec3(e.cdevice.which));
		}
		else if (e.type == SDL_CONTROLLERDEVICEREMOVED)
		{
			Update(JOY_REMOVED, glm::vec3(e.cdevice.which));
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
	this->tempMesh->GetTransform().m_pos -= (this->m_velocity * deltaTime);

	if ((lastX < -DEADZONE || lastX > DEADZONE))
	{
		this->m_velocity.z += lastX / (glm::pow(2, 15));
	}
	if ((lastY < -DEADZONE || lastY > DEADZONE))
	{
		this->m_velocity.x -= lastY / (glm::pow(2, 15));
	}

	if (m_velocity.x > 0) m_velocity.x = glm::max(m_velocity.x - FRICTION * deltaTime, 0.0f);
	if (m_velocity.y > 0) m_velocity.y = glm::max(m_velocity.y - FRICTION * deltaTime, 0.0f);
	if (m_velocity.z > 0) m_velocity.z = glm::max(m_velocity.z - FRICTION * deltaTime, 0.0f);
	if (m_velocity.x < 0) m_velocity.x = glm::min(m_velocity.x + FRICTION * deltaTime, 0.0f);
	if (m_velocity.y < 0) m_velocity.y = glm::min(m_velocity.y + FRICTION * deltaTime, 0.0f);
	if (m_velocity.z < 0) m_velocity.z = glm::min(m_velocity.z + FRICTION * deltaTime, 0.0f);

	system("cls");
	std::cout << "X: " << m_velocity.x << std::endl;
	std::cout << "Y: " << m_velocity.y << std::endl;
	std::cout << "Z: " << m_velocity.z << std::endl;

	//camera update
	this->m_camera.Update(this->tempMesh->GetTransform(), deltaTime);
}
