#pragma once
#include "GLUtil.h"
#include "GLModel.h"
#include "GLNPC.h"
#include "GLPlayer.h"
#include "GLNPC_PowerUpHandler.h"

class GLCollisionHandler
{
public:
	GLCollisionHandler() {
		AABB wall(glm::vec3(0), glm::vec3(125, 50, 85));
		walls[TOP] =	AABB(glm::vec3(0, 55, 0), glm::vec3(125, 5, 85));
		walls[BOTTOM] = AABB(glm::vec3(0, -55, 0), glm::vec3(125, 5, 85));
		walls[LEFT] =	AABB(glm::vec3(0, 0, -90), glm::vec3(125, 50, 5));
		walls[RIGHT] =	AABB(glm::vec3(0, 0, 90), glm::vec3(125, 50, 5));
		walls[FRONT] =	AABB(glm::vec3(130, 0, 0), glm::vec3(5, 50, 85));
		walls[BOTTOM] =	AABB(glm::vec3(-130, 0, 0), glm::vec3(5, 50, 85));
	};
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
	void resetPowerUpHandler();

	void AddParticleHandlerReference(ParticleHandler* pHandlerRef);
private:
	enum
	{
		TOP,
		BOTTOM,
		LEFT,
		RIGHT,
		FRONT,
		BACK,

		NUM_WALLS
	};

	AABB walls[NUM_WALLS];
	std::vector<GLPlayer*> players;
	std::vector<GLNPC*> NPCs;
	std::vector<GLModel*> models;
	NpcPowerUpHandler* PowerUpHandler;
	ParticleHandler* pHandlerRef;
};

