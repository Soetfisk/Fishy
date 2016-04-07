#ifndef SCENE_H
#define SCENE_H

#include "GLUtil.h"

class Scene
{
private:




public:
	Scene();
	~Scene();

	void HandleEvenet(SDL_Event* e);

	void Update(float& deltaTime);
	void LoadScene();
	void DrawScene();
};

#endif