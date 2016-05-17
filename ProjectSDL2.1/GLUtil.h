#pragma once

//Win32 Includes
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

//Basic Util Includes
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

//OpenGL Includes
#include <gl\glew.h>
#include <glm\glm.hpp>
#include <gl\GL.h>
#include <glm\gtx\transform.hpp>

//SDL Includes
#include <SDL2\SDL.h>
#include <SDL2\SDL_mixer.h>

//FSH includes
#include <FishBox.h>

//Structs

//Particle
enum EmitterType
{
	STATICSTREAM,
	GOLDSTREAM,
	PLAYERFOLLOW,
	PROJECTILE,
	NREMITERTYPE
};

//debug
#include "debug.h"

//WINDOW

namespace window 
{
	const int WIDTH = 1024;
	const int HEIGHT = 768;

	const float HALF_WIDTH = WIDTH * 0.5;
	const float HALF_HEIGHT = HEIGHT * 0.5;

	const float QUARTER_WIDHT = HALF_WIDTH * 0.5;
	const float QUARTER_HEIGHT = HALF_HEIGHT * 0.5;
}

//BOUNDS
namespace bounds
{
	const float MAX_X = 125.0f;
	const float MIN_X = -125.0f;

	const float MAX_Y = 50.0f;
	const float MIN_Y = -50.0f;

	const float MAX_Z = 85.0f;
	const float MIN_Z = -85.0f;
}

#ifdef _DEBUG 
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 
#endif
#endif  // _DEBUG
