#include "GLProjectileHandler.h"
#include "RNG.h"

GLProjectileHandler::GLProjectileHandler()
{
	projectileActiveTime = 0;
	projectileSpeed = 0.0f;
}

GLProjectileHandler::GLProjectileHandler(FishBox* FSH_Loader, unsigned int modelID, int nrOfProjectiles, int projectileActiveTime, float projectileSpeed, float cooldown)
{
	this->FSH_Loader = FSH_Loader;
	this->modelID = modelID;
	this->projectileActiveTime = projectileActiveTime;
	this->projectileSpeed = projectileSpeed;
	this->projectileStrength = 30.0f;
	this->projectileSize = 1.0f;
	standardProjectileSize = 1.0f;
	this->cooldownDuration = cooldown;
	this->cooldownCounter = 0.0f;
	this->cooldown = false;
	for (int i = 0; i < nrOfProjectiles; i++)
		projectiles.push_back(new GLProjectile(FSH_Loader, modelID, projectileActiveTime, projectileSpeed, projectileStrength, projectileSize));
	currentState = REGULAR;
}

GLProjectileHandler::~GLProjectileHandler()
{
	for (size_t i = 0; i < projectiles.size(); i++)
		delete projectiles.at(i);
}

void GLProjectileHandler::Shoot(glm::vec3 forward, glm::vec3 pos, glm::vec3 rot, glm::vec3 velocity, glm::vec3 right, glm::vec3 up)
{
	if (!cooldown)
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
		cooldown = true;
	}
}

void GLProjectileHandler::ChangeStateTo(ProjectilePowerUpState state)
{
	switch (state)
	{
	case REGULAR:
		projectileSize = standardProjectileSize;
		break;
	case SHOTGUN:
		projectileSize = standardProjectileSize;
		break;
	case BIG:
 		projectileSize = standardProjectileSize * BIG_PROJECTILE_MULTIPLIER;
		break;
	case FAST:
		projectileSize = standardProjectileSize;
		break;
	case STRONG:
		projectileSize = standardProjectileSize;
		break;
	default:
		break;
	}
	currentState = state;
}

void GLProjectileHandler::Update(float& dt)
{
	GLProjectile* temp = nullptr;
	for (size_t i = 0; i < projectiles.size(); i++)
	{
		projectiles.at(i)->TestUpdate(dt);
		projectiles.at(i)->UpdateModel();
	}
		
	if (cooldown)
	{
		cooldownCounter += dt;
		if (cooldownCounter >= cooldownDuration)
		{
			cooldown = false;
			cooldownCounter = 0.0f;
		}
	}
}

void GLProjectileHandler::Draw(GLShader& shader)
{
	for (size_t i = 0; i < projectiles.size(); i++)
		projectiles.at(i)->TestDraw(shader);
}

std::vector<GLProjectile*>& GLProjectileHandler::GetProjectiles()
{
	return this->projectiles;
}

std::vector<GLProjectile*> GLProjectileHandler::GetActiveProjectiles()
{
	std::vector<GLProjectile*> result;

	for (size_t i = 0; i < projectiles.size(); i++)
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
	for (size_t i = 0; i < projectiles.size(); i++)
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
	if (projectilePtr == nullptr)
	{
		projectiles.push_back(new GLProjectile(FSH_Loader, modelID, projectileActiveTime, projectileSpeed, projectileSize));
		projectilePtr = projectiles.back();
	}

	projectilePtr->SetScale(projectileSize);
	float size = glm::length(projectilePtr->GetBoundingBox().halfDimension) * SHOTGUN_OFFSET;
	pos = pos + forward * size;
	projectilePtr->Shoot(pos, forward, velocity, rot);

	addEmitterToProjectile(projectilePtr, pos);
}

void GLProjectileHandler::addEmitterToProjectile(GLProjectile* projectile, glm::vec3 pos) {
	if(!projectile->hasParticleEmitter())
		projectile->addParticleEmitter(this->particleHandlerReference->CreateEmitter(EmitterType::PROJECTILE, glm::vec4(pos, 1)));
}

void GLProjectileHandler::ShotgunShoot(glm::vec3 forward, glm::vec3 pos, glm::vec3 rot, glm::vec3 velocity, glm::vec3 right, glm::vec3 up)
{
	// Get projectiles boundingBox and get the size for offsetting
	GLProjectile* projectilePtr = GetInactiveProjectile();
	if (projectilePtr == nullptr)
	{
		projectiles.push_back(new GLProjectile(FSH_Loader, modelID, projectileActiveTime, projectileSpeed, projectileStrength, projectileSize));
		projectilePtr = projectiles.back();
	}
	projectilePtr->SetScale(projectileSize);
	float size = glm::length(projectilePtr->GetBoundingBox().halfDimension) * SHOTGUN_OFFSET;
	glm::vec3 tempRight;
	glm::vec3 tempUp;
	glm::vec3 tempForward;
	float angle = 0.0f;
	pos = pos + forward * size;

	for (float x = -1; x < 2; x++)
	{
		for (float y = -1; y < 2; y++)
		{
			tempRight = glm::vec3(right.x, right.y, right.z);
			tempUp = glm::vec3(up.x, up.y, up.z);
			do 
				angle = RNG::range(0.0f, MAX_ANGLE);
			while (angle == 0);
			do 
			{
				tempForward = glm::vec3(forward.x + RNG::range(-angle, angle),
										forward.y + RNG::range(-angle, angle),
										forward.z + RNG::range(-angle, angle));
			} while (glm::dot(forward, tempForward) < 0.8);
			glm::normalize(tempForward);

			if (x != 0)
				tempRight *= size * x;	// Add offset in X
			else
				tempRight *= 0.0f;		// Remove offset in X
			if (y != 0)
				tempUp *= size * y;		// Add offset in Y
			else
				tempUp *= 0.0f;			// Remove offset in Y;
			
			// Get a inactive projectile
			projectilePtr = GetInactiveProjectile();
			if (projectilePtr == nullptr) // Create projectile if needed
			{
				projectiles.push_back(new GLProjectile(FSH_Loader, modelID, projectileActiveTime, projectileSpeed, projectileStrength, projectileSize));
				projectilePtr = projectiles.back();
			}
			// Set scale and shoot from new start pos(startPos + tempRight + tempUp)
			projectilePtr->SetScale(projectileSize);
			projectilePtr->Shoot(pos + tempRight + tempUp, tempForward, velocity, rot);
			addEmitterToProjectile(projectilePtr, pos);
		}
	}
}

void GLProjectileHandler::StandardProjectileSize(float size)
{
	standardProjectileSize = size;
	if (currentState == BIG)
		projectileSize = standardProjectileSize * BIG_PROJECTILE_MULTIPLIER;
	else
		projectileSize = standardProjectileSize;
}

void GLProjectileHandler::drawParticles(GLShader *shader) {
	for (size_t i = 0; i < projectiles.size(); i++)
		projectiles.at(i)->drawParticles(shader);
}

void GLProjectileHandler::updateParticles(float& deltaTime) {
	for (size_t i = 0; i < projectiles.size(); i++)
		projectiles.at(i)->updateParticleEmitter(deltaTime);
}

void GLProjectileHandler::addParticleHandlerReference(ParticleHandler* pHandlerRef) {
	this->particleHandlerReference = pHandlerRef;
}