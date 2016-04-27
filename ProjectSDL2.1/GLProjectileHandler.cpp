#include "GLProjectileHandler.h"

GLProjectileHandler::GLProjectileHandler()
{
	projectileActiveTime = 0;
	projectileSpeed = 0;
}

GLProjectileHandler::GLProjectileHandler(FishBox* FSH_Loader, unsigned int modelID, int nrOfProjectiles, int projectileActiveTime, float projectileSpeed)
{
	this->FSH_Loader = FSH_Loader;
	this->modelID = modelID;
	this->projectileActiveTime = projectileActiveTime;
	this->projectileSpeed = projectileSpeed;
	for (int i = 0; i < nrOfProjectiles; i++)
		projectiles.push_back(new GLProjectile(*FSH_Loader, modelID, projectileActiveTime, projectileSpeed));
}

GLProjectileHandler::~GLProjectileHandler()
{
	for (int i = 0; i < projectiles.size(); i++)
		delete projectiles.at(i);
}

void GLProjectileHandler::Shoot(glm::vec3 forward, glm::vec3 pos, glm::vec3 rot, glm::vec3 velocity)
{
	GLProjectile* projectilePtr = GetInactiveProjectile();
	if (projectilePtr != nullptr)
		projectilePtr->Shoot(pos, forward, velocity, rot);
	else
		projectiles.push_back(new GLProjectile(*FSH_Loader, modelID, projectileActiveTime, projectileSpeed));
}

void GLProjectileHandler::Update(float& dt)
{
	GLProjectile* temp = nullptr;
	for (int i = 0; i < projectiles.size(); i++)
		projectiles.at(i)->TestUpdate(dt);
}

void GLProjectileHandler::Draw(GLShader& shader)
{
	for (int i = 0; i < projectiles.size(); i++)
		projectiles.at(i)->TestDraw(shader);
}

std::vector<GLProjectile*>& GLProjectileHandler::GetProjectiles()
{
	return this->projectiles;
}

GLProjectile* GLProjectileHandler::GetInactiveProjectile()
{
	GLProjectile* projectilePtr = nullptr;
	for (int i = 0; i < projectiles.size(); i++)
	{
		if (!projectiles.at(i)->IsActive())
		{
			projectilePtr = projectiles.at(i);
			i = projectiles.size();
		}
	}
	return projectilePtr;
}