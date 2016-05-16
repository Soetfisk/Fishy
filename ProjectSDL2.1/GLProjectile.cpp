#include "GLProjectile.h"

GLProjectile::GLProjectile() : GLModel()
{
	maxActiveTime = 0;
	timeActive = 0.0;
	forward = glm::vec3(0);
	currentState = INACTIVE;
}

GLProjectile::GLProjectile(int maxDist) : GLModel()
{
	maxActiveTime = maxDist;
	timeActive = 0.0f;
	speed = 1.0f;
	strength = 10.0f;
	velocity = glm::vec3();
	forward = glm::vec3();
	forwardVel = glm::vec3();
	currentState = INACTIVE;
}

GLProjectile::GLProjectile(FishBox* FSH_Loader, char* filePath, int projectileActiveTime, float projectileSpeed) : GLModel(FSH_Loader, filePath)
{
	maxActiveTime = projectileActiveTime;
	MaxActiveTimeUnaltered = projectileActiveTime;
	timeActive = 0.0f;
	this->speed = projectileSpeed;
	strength = 10.0f;
	velocity = glm::vec3();
	forward = glm::vec3();
	forwardVel = glm::vec3();
	currentState = INACTIVE;
}

GLProjectile::GLProjectile(FishBox* FSH_Loader, unsigned int modelID, int projectileActiveTime, float projectileSpeed, float projectileStrength, float projectileSize) : GLModel(FSH_Loader, modelID)
{
	maxActiveTime = projectileActiveTime;
	MaxActiveTimeUnaltered = projectileActiveTime;
	timeActive = 0.0f;
	this->speed = projectileSpeed;
	strength = projectileStrength;
	transform->m_scale = glm::vec3(projectileSize);
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
		if (timeActive >= maxActiveTime)
		{			// Check if maxActiveTime was reached
			currentState = INACTIVE;
			//printf("MaxTimePassed\n");
		}
		else
			transform->m_pos += forward * speed * dt;	// Move Projectile forward
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
	timeActive = 0.0f;
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
	this->maxActiveTime = MaxActiveTimeUnaltered * (this->GetTransform().GetScale().x);
	transform->m_pos = startPos;
	transform->m_rot = rot;
	timeActive = 0.0f;
	this->forward = forward;
	this->velocity = velocity;

	float temp  = glm::length(velocity) * 0.2f;
	forwardVel = forward * speed;
	forwardVel *= ((temp >= 1) ? temp : 1.0f);
	currentState = ACTIVE;
}

void GLProjectile::SetScale(float scale)
{
	transform->m_scale = glm::vec3(scale);
}

void GLProjectile::setMaxActiveTime(int Time)
{
	this->maxActiveTime = Time;
}

void GLProjectile::SetSpeed(float& speed)
{
	this->speed = speed;
}

void GLProjectile::SetStrength(float strength)
{
	this->strength = strength;
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

void GLProjectile::addParticleEmitter(ParticleEmitter* emitter) {
	this->projectileEmitter = emitter;
	
}

void GLProjectile::updateParticleEmitter(float& deltaTime) {
	this->projectileEmitter->UpdateEmitter(deltaTime);
}

void GLProjectile::drawParticles(GLShader* shader) {
	this->projectileEmitter->Draw(shader);
}