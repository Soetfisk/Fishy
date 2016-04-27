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
		//inactiveProjectiles.push_back(projectiles.at(i));
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
		ActivateProjectile(projectilePtr, forward, pos, rot);
	}
	else
	{
		projectiles.push_back(new GLProjectile(projectileTravelDistance, projectileSpeed));
		//ActivateProjectile(projectiles.back(), forward, pos, rot);
	}
}

void GLProjectileHandler::Update(float& dt)
{
	GLProjectile* temp = nullptr;
	//std::cout << projectiles.size() << std::endl;
	for (int i = 0; i < projectiles.size(); i++)
	{
		projectiles.at(i)->TestUpdate(dt);
	}
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

std::vector<GLProjectile*> GLProjectileHandler::GetActiveProjectiles()
{
	std::vector<GLProjectile*> result;

	for (int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles.at(i)->isActive())
		{
			result.push_back(projectiles.at(i));
		}
	}

	return result;
}

GLProjectile* GLProjectileHandler::GetInactiveProjectile()
{
	GLProjectile* projectilePtr = nullptr;
	for (int i = 0; i < projectiles.size(); i++)
	{
		if (!projectiles.at(i)->isActive())
		{
			projectilePtr = projectiles.at(i);
			i = projectiles.size();
		}
	}
	return projectilePtr;
}

void GLProjectileHandler::ActivateProjectile(GLProjectile* projectile, glm::vec3& forward, glm::vec3& pos, glm::vec3& rot)
{
	projectile->SetForward(forward);
	projectile->ResetTo(pos);
	projectile->GetTransform().m_rot = rot;
	projectile->Activate();
}
