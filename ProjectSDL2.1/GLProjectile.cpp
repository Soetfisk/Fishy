#include "GLProjectile.h"

GLProjectile::GLProjectile()
	:GLModel()
{
	maxDistance = 10;
	distanceTraveled = 0.0;
	speed = 1;
	forward = glm::vec3(0, 0, 1) * speed;
	
	currentState = ProjectileStates::ACTIVE;
}

GLProjectile::GLProjectile(glm::vec3& forward)
	: GLModel()
{
	this->forward = forward;
}

GLProjectile::GLProjectile(std::string & filePath, glm::vec3& forward)
	: GLModel(filePath)
{
	// load from file
}


GLProjectile::~GLProjectile()
{
}

void GLProjectile::TestDraw(GLShader & shader)
{
	switch (currentState)
	{
	case ProjectileStates::ACTIVE:
		this->Draw(shader);
		std::cout << "ACTIVE\n";
		break;
	case ProjectileStates::INACTIVE:
		std::cout << "INACTIVE\n";
		break;
	}

}

void GLProjectile::TestUpdate(float& dt)
{
	switch (currentState)
	{
	case ProjectileStates::ACTIVE:
		distanceTraveled += dt;
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
}

void GLProjectile::SetForward(glm::vec3 & forward)
{
	this->forward = forward;
}
