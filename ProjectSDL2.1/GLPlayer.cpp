#include "GLPlayer.h"



GLPlayer::GLPlayer()
{
	this->m_camera = GLCamera();
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
		this->m_camera.ProcessInput(movementVec.x, movementVec.y);
		break;
	case PLAYER_MOVE:

		break;
	case JOY_ADDED:
		this->AddController(movementVec.x);
		break;
	case JOY_REMOVED:
		this->RemoveController(movementVec.x);
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
			AddController(e.cdevice.which);
		}
	}
	float x, y;
	x = SDL_GameControllerGetAxis(pad, SDL_CONTROLLER_AXIS_RIGHTX);
	y = SDL_GameControllerGetAxis(pad, SDL_CONTROLLER_AXIS_RIGHTY);

	x = x / (glm::pow(2, 15));
	y = y / (glm::pow(2, 15));

	std::cout << "X:" << x << std::endl;
	std::cout << "Y:" << y << std::endl;
	this->Update(CAMERA_MOVE, glm::vec3(x, y, 0));
}

void GLPlayer::AddController(int id)
{
	if (SDL_IsGameController(id)) {
		this->pad = SDL_GameControllerOpen(id);
		if (pad)
		{
			_SDL_Joystick *joy = SDL_GameControllerGetJoystick(pad);
			this->instanceID = SDL_JoystickInstanceID(joy);
		}
	}
}

void GLPlayer::RemoveController(int id)
{
	SDL_GameControllerFromInstanceID(id);
}
