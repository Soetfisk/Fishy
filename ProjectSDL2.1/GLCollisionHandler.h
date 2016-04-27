#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H
#include "GLUtil.h"
#include "GLModel.h"
#include "GLNPC.h"
#include "GLPlayer.h"

class GLCollisionHandler
{
public:
	GLCollisionHandler() {};
	~GLCollisionHandler() {};

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

private:
	std::vector<GLPlayer*> players;
	std::vector<GLNPC*> NPCs;
	std::vector<GLModel*> models;
};
#endif

