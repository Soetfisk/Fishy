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
	currentState = SHOTGUN;
}

GLProjectileHandler::~GLProjectileHandler()
{
	for (int i = 0; i < projectiles.size(); i++)
		delete projectiles.at(i);
}

void GLProjectileHandler::Shoot(glm::vec3 forward, glm::vec3 pos, glm::vec3 rot, glm::vec3 velocity)
{
	switch (currentState)
	{
	case REGULAR:
		RegularShoot(forward, pos, rot, velocity);
		break;
	case SHOTGUN:
		ShotgunShoot(forward, pos, rot, velocity);
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

void GLProjectileHandler::RegularShoot(glm::vec3 forward, glm::vec3 pos, glm::vec3 rot, glm::vec3 velocity)
{
	GLProjectile* projectilePtr = GetInactiveProjectile();
	if (projectilePtr != nullptr)
		projectilePtr->Shoot(pos, forward, velocity, rot);
	else
		projectiles.push_back(new GLProjectile(FSH_Loader, modelID, projectileActiveTime, projectileSpeed));
}

void GLProjectileHandler::ShotgunShoot(glm::vec3 forward, glm::vec3 pos, glm::vec3 rot, glm::vec3 velocity)
{

	GLProjectile* projectilePtr = GetInactiveProjectile();
	if(projectilePtr != nullptr)
		projectilePtr->Shoot(pos, forward, velocity, rot);
	else
	{
		projectiles.push_back(new GLProjectile(FSH_Loader, modelID, projectileActiveTime, projectileSpeed, projectileStrength));
		projectiles.back()->Shoot(pos, forward, velocity, rot);
		projectilePtr = projectiles.back();
	}
	glm::vec3 offSet = projectilePtr->GetBoundingBox().halfDimension;
	glm::vec3 projRight = projectilePtr->GetRight();
	float size = glm::length(offSet) * 1.0f;

	glm::vec3 tempRight;
	for (float x = -1; x < 2; x++) {
		for (float y = -1; y < 2; y++) {
			if (x != 0 && y != 0) {
				tempRight = glm::vec3(projRight.x * x, projRight.y * y, projRight.z);
				projectilePtr = GetInactiveProjectile();
				if (projectilePtr != nullptr)
					projectilePtr->Shoot(pos + (tempRight*size), forward, velocity, rot);
				else
					projectiles.push_back(new GLProjectile(FSH_Loader, modelID, projectileActiveTime, projectileSpeed, projectileStrength));
				projectiles.back()->Shoot(pos + (tempRight*size), forward, velocity, rot);
			}

			
		}
	}

	for (float i = -1; i < 2; i+=2) {
		projectilePtr = GetInactiveProjectile();
		if (projectilePtr != nullptr)
			projectilePtr->Shoot(pos + (projRight*i*size) , forward, velocity, rot);
		else
			projectiles.push_back(new GLProjectile(FSH_Loader, modelID, projectileActiveTime, projectileSpeed, projectileStrength));
			projectiles.back()->Shoot(pos + (projRight*i*size), forward, velocity, rot);
	}

	

	

}
