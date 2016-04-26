#include "GLProjectile.h"

GLProjectile::GLProjectile() : GLModel()
{
	maxDistance = 0;
	distanceTraveled = 0.0;
	//speed = 0;
	forward = glm::vec3(0);
	//forwardSpeed = glm::vec3(0);
	currentState = INACTIVE;
}

GLProjectile::GLProjectile(int maxDist) : GLModel()
{
	maxDistance = maxDist;
	distanceTraveled = 0.0;
	//this->speed = speed;
	forward = glm::vec3(0);
	//forwardSpeed = glm::vec3(0);
	currentState = INACTIVE;
}

GLProjectile::GLProjectile(FishBox& FSH_Loader, char* filePath, int maxDist, float speed) : GLModel(FSH_Loader, filePath)
{
	maxDistance = maxDist;
	distanceTraveled = 0.0;
	//this->speed = speed;
	forward = glm::vec3(0);
	//forwardSpeed = glm::vec3(0);
	currentState = INACTIVE;
}

GLProjectile::~GLProjectile()
{
}

void GLProjectile::TestDraw(GLShader & shader)
{
	//Only draw the projectile if it is active
	switch (currentState)
	{
	case ACTIVE:
		this->Draw(shader);
		break;
	case INACTIVE:
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
	case ACTIVE:
		distanceTraveled += dt;							// Add to distanceTraveled
		if (distanceTraveled >= maxDistance)			// Check if maxDistance was reached
			currentState = INACTIVE;
		else
			transform->m_pos += dt;		// Move Projectile forward
		break;
	case INACTIVE:
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

void GLProjectile::SetForward(glm::vec3 forward)
{
	this->forward = forward;
	//forwardSpeed = forward * speed;
}

void GLProjectile::SetVelocity(glm::vec3 velocity)
{
	this->velocity = velocity;
}

void GLProjectile::ShootAt(glm::vec3 startPos, glm::vec3 forward, glm::vec3 velocity)
{
	transform->SetPos(startPos);
	distanceTraveled = 0.0;
	this->forward = forward;
	this->velocity = velocity;
	forwardVel = forward * velocity;
	currentState = ACTIVE;
}

void GLProjectile::Scale(glm::vec3 scale)
{
	transform->m_scale = scale;
}

void GLProjectile::SetSpeed(float& speed)
{
	//this->speed = speed;
	//forwardSpeed = forward * speed;
}

void GLProjectile::Activate()
{
	currentState = ACTIVE;
}

void GLProjectile::Inactivate()
{
	currentState = ProjectileStates::INACTIVE;
}

bool GLProjectile::IsActive()
{
	bool check = false;
	if (currentState == ACTIVE)
		check = true;
	return check;
}
