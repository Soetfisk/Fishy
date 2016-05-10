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


//WINDOW

namespace window {
	const int WIDTH = 800;
	const int HEIGHT = 600;
	const float HALF_WIDTH = WIDTH * 0.5;
	const float HALF_HEIGHT = HEIGHT * 0.5;
	const float QUARTER_WIDHT = HALF_WIDTH * 0.5;
	const float QUARTER_HEIGHT = HALF_HEIGHT * 0.5;
}
#ifdef _DEBUG 
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 
#endif
#endif  // _DEBUG
