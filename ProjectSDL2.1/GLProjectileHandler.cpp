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
	this->projectileStrength = 10;
	for (int i = 0; i < nrOfProjectiles; i++)
		projectiles.push_back(new GLProjectile(FSH_Loader, modelID, projectileActiveTime, projectileSpeed, projectileStrength));
	currentState = REGULAR;
}

GLProjectileHandler::~GLProjectileHandler()
{
	for (int i = 0; i < projectiles.size(); i++)
		delete projectiles.at(i);
}

void GLProjectileHandler::Shoot(glm::vec3 forward, glm::vec3 pos, glm::vec3 rot, glm::vec3 velocity, glm::vec3 right, glm::vec3 up)
{
	switch (currentState)
	{
	case REGULAR:
		RegularShoot(forward, pos, rot, velocity);
		break;
	case SHOTGUN:
		ShotgunShoot(forward, pos, rot, velocity, right, up);
		break;
	case BIG:
		RegularShoot(forward, pos, rot, velocity);
		break;
	case FAST:
		RegularShoot(forward, pos, rot, velocity);
		break;
	case STRONG:
		RegularShoot(forward, pos, rot, velocity);
		break;
	default:
		break;
	}
	
}

void GLProjectileHandler::ChangeStateTo(ProjectilePowerUpState state)
{
	currentState = state;
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

std::vector<GLProjectile*> GLProjectileHandler::GetActiveProjectiles()
{
	std::vector<GLProjectile*> result;

	for (int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles.at(i)->IsActive())
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
		if (!projectiles.at(i)->IsActive())
		{
			projectilePtr = projectiles.at(i);
			i = projectiles.size();
		}
	}
	return projectilePtr;
}

void GLProjectileHandler::RegularShoot(glm::vec3 forward, glm::vec3 pos, glm::vec3 rot, glm::vec3 velocity)
{
	GLProjectile* projectilePtr = GetInactiveProjectile();
	if (projectilePtr != nullptr)
		projectilePtr->Shoot(pos, forward, velocity, rot);
	else
		projectiles.push_back(new GLProjectile(FSH_Loader, modelID, projectileActiveTime, projectileSpeed));
}

void GLProjectileHandler::ShotgunShoot(glm::vec3 forward, glm::vec3 pos, glm::vec3 rot, glm::vec3 velocity, glm::vec3 right, glm::vec3 up)
{

	GLProjectile* projectilePtr = GetInactiveProjectile();
	if (projectilePtr == nullptr)
	{
		projectiles.push_back(new GLProjectile(FSH_Loader, modelID, projectileActiveTime, projectileSpeed, projectileStrength));
		projectilePtr = projectiles.back();
	}

	glm::vec3 offSet = projectilePtr->GetBoundingBox().halfDimension;
	glm::vec3 projRight = right;
	glm::vec3 projUp = up;
	float size = glm::length(offSet) * 1.0f;

	glm::vec3 tempRight;
	glm::vec3 tempUp;

	for (float x = -1; x < 2; x++)
	{
		for (float y = -1; y < 2; y++)
		{
			tempRight = glm::vec3(projRight.x, projRight.y, projRight.z);
			tempUp = glm::vec3(projUp.x, projUp.y, projUp.z);
			
			if (x != 0)
				tempRight *= size * x;
			else
				tempRight *= 0;
			if (y != 0)
				tempUp *= size * y;
			else
				tempUp *= 0;
		
			projectilePtr = GetInactiveProjectile();
			if (projectilePtr != nullptr)
				projectilePtr->Shoot(pos + (tempRight + tempUp), forward, velocity, rot);
			else
			{
				projectiles.push_back(new GLProjectile(FSH_Loader, modelID, projectileActiveTime, projectileSpeed, projectileStrength));
				projectiles.back()->Shoot(pos + (tempRight + tempUp), forward, velocity, rot);
			}	
		}
	}
}
