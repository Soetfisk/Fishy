#pragma once
#include "GLUtil.h"
#include "GLModel.h"
#include "GLNPC.h"
#include "GLPlayer.h"
#include "GLNPC_PowerUpHandler.h"

class GLCollisionHandler
{
public:
	GLCollisionHandler() {};
	~GLCollisionHandler();

	void CheckCollisions(float deltaTime);

	void AddPlayer(GLPlayer* player);
	void AddPlayer(std::vector<GLPlayer*> players);
	void RemovePlayer(GLPlayer* player);

	void AddNPC(GLNPC* npc);
	void AddNPC(std::vector<GLNPC*> npcs);
	void RemoveNPC(GLNPC* npc);

	void AddModel(GLModel* model);
	void AddModel(std::vector<GLModel*> models);
	void RemoveModel(GLModel* model);

	void InitiatePowerUpHandler();

private:
	std::vector<GLPlayer*> players;
	std::vector<GLNPC*> NPCs;
	std::vector<GLModel*> models;
	NpcPowerUpHandler* PowerUpHandler;
};

