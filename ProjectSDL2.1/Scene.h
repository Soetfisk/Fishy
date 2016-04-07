#ifndef SCENE_H
#define SCENE_H

#include "GLUtil.h"

class Scene
{
private:

public:
	Scene();
	~Scene();

	void pollEvent(SDL_Event* e);

};

#endif