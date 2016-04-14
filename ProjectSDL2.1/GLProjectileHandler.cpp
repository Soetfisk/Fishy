#include "GLProjectileHandler.h"

GLProjectileHandler::GLProjectileHandler()
{
	projectileTravelDistance = 0;
	projectileSpeed = 0;
}

GLProjectileHandler::GLProjectileHandler(int nrOfProjectiles, int projectileTravelDisntace, float projectileSpeed)
{
	this->projectileTravelDistance = projectileTravelDisntace;
	this->projectileSpeed = projectileSpeed;
	for (int i = 0; i < nrOfProjectiles; i++)
	{
		projectiles.push_back(new GLProjectile(projectileTravelDisntace, projectileSpeed));
		inactiveProjectiles.push_back(projectiles.at(i));
	}
}

GLProjectileHandler::~GLProjectileHandler()
{
	for (int i = 0; i < projectiles.size(); i++)
		delete projectiles.at(i);
}

void GLProjectileHandler::Shoot(glm::vec3& forward, glm::vec3& pos, glm::vec3& rot)
{
	GLProjectile* projectilePtr = GetInactiveProjectile();
	if (projectilePtr != nullptr)
	{
		this->ActivateProjectile(projectilePtr, forward, pos, rot);
	}
	else
	{
		projectiles.push_back(new GLProjectile(projectileTravelDistance, projectileSpeed));
		this->ActivateProjectile(projectiles.back(), forward, pos, rot);
	}
}

void GLProjectileHandler::Update(float& dt)
{
	GLProjectile* temp = nullptr;
	for (int i = 0; i < activeProjectiles.size(); i++)
	{
		activeProjectiles.at(i)->TestUpdate(dt);
		if (!activeProjectiles.at(i)->isActive())
		{
			//temp = activeProjectiles.at(i);
			//inactiveProjectiles.push_back(temp);

			//activeProjectiles.erase(activeProjectiles.begin() + i);
			////activeProjectiles.at(i);
			////activeProjectiles.pop_back();
		}
	}
}

void GLProjectileHandler::Draw(GLShader& shader)
{
	for (int i = 0; i < activeProjectiles.size(); i++)
		activeProjectiles.at(i)->TestDraw(shader);
}

GLProjectile* GLProjectileHandler::GetInactiveProjectile()
{
	GLProjectile* projectilePtr = nullptr;
	if (!inactiveProjectiles.empty())
	{
		projectilePtr = inactiveProjectiles.back();
		inactiveProjectiles.pop_back();
	}
	return projectilePtr;
}

void GLProjectileHandler::ActivateProjectile(GLProjectile* projectile, glm::vec3& forward, glm::vec3& pos, glm::vec3& rot)
{
	projectile->SetForward(forward);
	projectile->ResetTo(pos);
	projectile->GetTransform().m_rot = rot;
	projectile->Activate();
	activeProjectiles.push_back(projectiles.back());
}
