#include "GLProjectile.h"

GLProjectile::GLProjectile()
	:GLModel()
{
	maxDistance = 9;
	distanceTraveled = 0.0;
	speed = 1;
	forward = glm::vec3(0, 0, 1) * speed;
	
	currentState = ProjectileStates::ACTIVE;
}

GLProjectile::GLProjectile(glm::vec3& forward, int& maxDist, float& speed)
	: GLModel()
{
	maxDistance = maxDist;
	distanceTraveled = 0.0;
	this->speed = speed;
	this->forward = forward * this->speed;
	currentState = ProjectileStates::INACTIVE;
}

GLProjectile::GLProjectile(std::string & filePath, glm::vec3& forward, int& maxDist, float& speed)
	: GLModel(filePath)
{
	maxDistance = maxDist;
	distanceTraveled = 0.0;
	this->speed = speed;
	this->forward = forward * this->speed;
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
	}

}


void GLProjectile::TestUpdate(float& dt)
{
	//Only update the projectile if it is active
	switch (currentState)
	{
	case ProjectileStates::ACTIVE:
		distanceTraveled += speed * dt;
		if (distanceTraveled >= maxDistance)
			currentState = ProjectileStates::INACTIVE;
		else
			transform->m_pos += forward * dt;
		break;
	case ProjectileStates::INACTIVE:
		break;
	}
}

void GLProjectile::ResetTo(glm::vec3& pos)
{
	transform->SetPos(pos);
	distanceTraveled = 0.0;
	currentState = ProjectileStates::ACTIVE;
}

void GLProjectile::SetForward(glm::vec3& forward)
{
	this->forward = forward * speed;
}

void GLProjectile::SetSpeed(float & speed)
{
	this->speed = speed;
}

void GLProjectile::Activate()
{
	currentState = ProjectileStates::ACTIVE;
}

void GLProjectile::Inactivate()
{
	currentState = ProjectileStates::INACTIVE;
}

ProjectileStates& GLProjectile::getCurrentState()
{
	return currentState;
}
