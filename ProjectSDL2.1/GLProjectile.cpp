#include "GLProjectile.h"

GLProjectile::GLProjectile() : GLModel()
{
	maxActiveTime = 0;
	timeActive = 0.0;
	//speed = 0;
	forward = glm::vec3(0);
	//forwardSpeed = glm::vec3(0);
	currentState = INACTIVE;
}

GLProjectile::GLProjectile(int maxDist) : GLModel()
{
	maxActiveTime = maxDist;
	timeActive = 0.0;
	speed = 1.0;
	velocity = glm::vec3();
	forward = glm::vec3();
	forwardVel = glm::vec3();
	currentState = INACTIVE;
}

GLProjectile::GLProjectile(FishBox& FSH_Loader, char* filePath, int projectileActiveTime, float projectileSpeed) : GLModel(FSH_Loader, filePath)
{
	maxActiveTime = projectileActiveTime;
	timeActive = 0.0;
	this->speed = projectileSpeed;
	velocity = glm::vec3();
	forward = glm::vec3();
	forwardVel = glm::vec3();
	currentState = INACTIVE;
}

GLProjectile::GLProjectile(FishBox& FSH_Loader, unsigned int modelID, int projectileActiveTime, float projectileSpeed) : GLModel(FSH_Loader, modelID)
{
	maxActiveTime = projectileActiveTime;
	timeActive = 0.0;
	this->speed = projectileSpeed;
	velocity = glm::vec3();
	forward = glm::vec3();
	forwardVel = glm::vec3();
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
		timeActive += dt;						
		if (timeActive >= maxActiveTime)			// Check if maxDistance was reached
			currentState = INACTIVE;
		else
		{
			transform->m_pos += forward * MIN_PROJECTILE_SPEED * dt;	// Move Projectile forward
			std::cout << "ProjectileForwardVel:\t" << forward.x << "\t" << forward.y << "\t" << forward.z << "\n";
		}
	
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
	timeActive = 0.0;
}

void GLProjectile::SetForward(glm::vec3 forward)
{
	this->forward = forward;
}

void GLProjectile::SetVelocity(glm::vec3 velocity)
{
	this->velocity = velocity;
}

void GLProjectile::Shoot(glm::vec3 startPos, glm::vec3 forward, glm::vec3 velocity, glm::vec3 rot)
{
	transform->m_pos = startPos;
	transform->m_rot = rot;
	timeActive = 0.0;
	this->forward = forward;
	this->velocity = velocity;



	//forwardVel.x = (velocity.x > MIN_SPEED || velocity.x < -MIN_SPEED) ? forward.x * glm::abs(velocity.x) : forward.x;
	//forwardVel.x = (forwardVel.x < MIN_PROJECTILE_SPEED && forwardVel.x > 0) ? MIN_PROJECTILE_SPEED : (forwardVel.x > -MIN_PROJECTILE_SPEED && forwardVel.x < 0) ? -MIN_PROJECTILE_SPEED : forwardVel.x;

	//forwardVel.y = (velocity.y > MIN_SPEED || velocity.y < -MIN_SPEED) ? forward.y * glm::abs(velocity.y) : forward.y;
	//forwardVel.y = (forwardVel.y < MIN_PROJECTILE_SPEED && forwardVel.y > 0) ? MIN_PROJECTILE_SPEED : (forwardVel.y > -MIN_PROJECTILE_SPEED && forwardVel.y < 0) ? -MIN_PROJECTILE_SPEED : forwardVel.y;
	//
	//forwardVel.z = (velocity.z > MIN_SPEED || velocity.z < -MIN_SPEED) ? forward.z * glm::abs(velocity.z) : forward.z;
	//forwardVel.z = (forwardVel.z < MIN_PROJECTILE_SPEED && forwardVel.z > 0) ? MIN_PROJECTILE_SPEED : (forwardVel.z > -MIN_PROJECTILE_SPEED && forwardVel.z < 0) ? -MIN_PROJECTILE_SPEED : forwardVel.z;
	
	/*forwardVel.x = (forwardVel.x > 0 && forwardVel.x < MIN_PROJECTILE_SPEED) ? forwardVel.x + MIN_PROJECTILE_SPEED : (forward.x < 0) ? -MIN_PROJECTILE_SPEED : 0;
	forwardVel.y = (forwardVel.y != 0 && forwardVel.y < MIN_PROJECTILE_SPEED) ? MIN_PROJECTILE_SPEED : (forward.y < 0) ? -MIN_PROJECTILE_SPEED : 0;
	forwardVel.z = (forwardVel.z != 0 && forwardVel.z < MIN_PROJECTILE_SPEED) ? MIN_PROJECTILE_SPEED : (forward.z < 0) ? -MIN_PROJECTILE_SPEED : 0;
	forwardVel *= speed;*/
	//std::cout << "ProjectileForwardVel:\t" << forward.x << "\t" << forward.y << "\t" << forward.z << "\n";
	currentState = ACTIVE;
}

void GLProjectile::Scale(glm::vec3 scale)
{
	transform->m_scale = scale;
}

void GLProjectile::SetSpeed(float& speed)
{
	this->speed = speed;
}

void GLProjectile::Activate()
{
	currentState = ACTIVE;
}

void GLProjectile::Inactivate()
{
	currentState = INACTIVE;
}

bool GLProjectile::IsActive()
{
	bool check = false;
	if (currentState == ACTIVE)
		check = true;
	return check;
}
