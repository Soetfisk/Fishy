#ifndef SCENE_H
#define SCENE_H

#include "GLUtil.h"

class Scene
{
private:
	//todo implement
	//std::vector<Model> models;
	//std::vector<Player> players;
	//std::vector<Npc> npc;


public:
	Scene();
	~Scene();

	void HandleEvenet(SDL_Event* e);

	void Update(float& deltaTime);
	void LoadScene();
	void DrawScene();
};

#endif