#include "GLProjectile.h"

GLProjectile::GLProjectile() : GLModel()
{
	maxDistance = 0;
	distanceTraveled = 0.0;
	speed = 0;
	forward = glm::vec3(0);
	forwardSpeed = glm::vec3(0);
	currentState = ProjectileStates::INACTIVE;
}

GLProjectile::GLProjectile(int maxDist, float speed) : GLModel()
{
	maxDistance = maxDist;
	distanceTraveled = 0.0;
	this->speed = speed;
	forward = glm::vec3(0);
	forwardSpeed = glm::vec3(0);
	currentState = ProjectileStates::INACTIVE;
}

GLProjectile::GLProjectile(FishBox* FSH_Loader, unsigned int modelID, int maxDist, float speed) : GLModel(FSH_Loader, modelID)
{
	maxDistance = maxDist;
	distanceTraveled = 0.0;
	this->speed = speed;
	forward = glm::vec3(0);
	forwardSpeed = glm::vec3(0);
	currentState = ProjectileStates::INACTIVE;
}

GLProjectile::~GLProjectile()
{
}

void GLProjectile::TestDraw(GLShader & shader)
{
	//Only draw the projectile if it is active
	switch (currentState)
	{
	case ProjectileStates::ACTIVE:
		this->Draw(shader);
		break;
	case ProjectileStates::INACTIVE:
		break;
	default:
		break;
	}
}

void GLProjectile::TestUpdate(float& dt)
{
	//Only update the projectile if it is active
	switch (currentState)
	{
	case ProjectileStates::ACTIVE:
		distanceTraveled += speed * dt;					// Add to distanceTraveled
		if (distanceTraveled >= maxDistance)			// Check if maxDistance was reached
			currentState = ProjectileStates::INACTIVE;
		else
			transform->m_pos += forwardSpeed * dt;		// Move Projectile forward
		break;
	case ProjectileStates::INACTIVE:
		break;
	default:
		break;
	}
}

void GLProjectile::ResetTo(glm::vec3& pos)
{
	transform->SetPos(pos);
	distanceTraveled = 0.0;
}

void GLProjectile::SetForward(glm::vec3& forward)
{
	this->forward = forward;
	forwardSpeed = forward * speed;
}

void GLProjectile::SetSpeed(float& speed)
{
	this->speed = speed;
	forwardSpeed = forward * speed;
}

void GLProjectile::Activate()
{
	currentState = ProjectileStates::ACTIVE;
}

void GLProjectile::Inactivate()
{
	currentState = ProjectileStates::INACTIVE;
}

bool GLProjectile::isActive()
{
	bool check = false;
	if (currentState == ProjectileStates::ACTIVE)
		check = true;
	return check;
}
