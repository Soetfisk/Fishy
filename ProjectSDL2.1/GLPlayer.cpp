#include "GLPlayer.h"



GLPlayer::GLPlayer()
{
	this->m_camera;
}


GLPlayer::~GLPlayer()
{
}

void GLPlayer::tempDraw()
{
}

void GLPlayer::Update(Events state, glm::vec3 movementVec)
{
	switch (state)
	{
	case CAMERA_MOVE:
		m_camera.SetInput((movementVec.x == 0) ? -1 : movementVec.x, (movementVec.y == 0)? -1: movementVec.y);
		break;
	case PLAYER_MOVE:

		break;
	case JOY_ADDED:
		this->AddController(movementVec.x);
		break;
	case JOY_REMOVED:
		this->RemoveController(movementVec.x);
		break;
	case NOTHING:
		this->m_camera.Update(GLTransform(), movementVec.x);
		break;
	default:
		break;
	}
	
}

GLCamera GLPlayer::GetCamera()
{
	return this->m_camera;
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

void GLPlayer::RemoveController(int id)
{
	SDL_GameControllerFromInstanceID(id);
}
