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

//FSH includes
#include <FishBox.h>

//Structs

//WINDOW

namespace window {
	const int WIDTH = 1024;
	const int HEIGHT = 768;
}
#ifdef _DEBUG 
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 
#endif
#endif  // _DEBUG
