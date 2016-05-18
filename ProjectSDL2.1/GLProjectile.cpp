#include "GLProjectile.h"

GLProjectile::GLProjectile() : GLModel()
{
	maxActiveTime = 0;
	timeActive = 0.0;
	forward = glm::vec3(0);
	currentState = INACTIVE;
	SetBoundingBox(glm::vec3(0), glm::vec3(0.5));
	this->projectileEmitter = nullptr;
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
	SetBoundingBox(glm::vec3(0), glm::vec3(0.5));
	this->projectileEmitter = nullptr;
}


GLProjectile::GLProjectile(FishBox* FSH_Loader, unsigned int modelID, int projectileActiveTime, float projectileSpeed, float projectileStrength, float projectileSize) : GLModel(FSH_Loader, modelID)
{
	maxActiveTime = projectileActiveTime/2;
	MaxActiveTimeUnaltered = projectileActiveTime/2;
	timeActive = 0.0f;
	this->speed = projectileSpeed*2;
	strength = projectileStrength;
	transform->m_scale = glm::vec3(projectileSize);
	velocity = glm::vec3();
	forward = glm::vec3();
	forwardVel = glm::vec3();
	currentState = INACTIVE;
	SetBoundingBox(glm::vec3(0), glm::vec3(0.5));
	this->projectileEmitter = nullptr;
	checkForOutOfBoundsValue = 0.0f;
}

GLProjectile::~GLProjectile()
{
	if(this->projectileEmitter != nullptr)
		delete this->projectileEmitter;
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
			if (this->projectileEmitter != nullptr)
				this->projectileEmitter->clean();
			//printf("MaxTimePassed\n");
		}
		else
			transform->m_pos += forward * speed * dt;	// Move Projectile forward
		if (timeActive >= checkForOutOfBoundsValue)
		{
			CheckIfOutOfBounds();
			checkForOutOfBoundsValue += 0.5f;
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
	checkForOutOfBoundsValue = 0.0f;
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
	if (this->projectileEmitter != nullptr)
		this->projectileEmitter->clean();
}

bool GLProjectile::IsActive()
{
	bool check = false;
	if (currentState == ACTIVE)
		check = true;
	return check;
}

void GLProjectile::addParticleEmitter(ParticleEmitter* emitter) {
	if (this->projectileEmitter == nullptr) {
		this->projectileEmitter = emitter;
		
	}

	this->projectileEmitter->updateEmitterData(glm::vec4(this->transform->GetPos(), 1),
		glm::vec4(this->forward, 0), glm::vec4(this->GetRight(), 0), glm::vec4(this->GetUp(), 0), this->transform->GetScale().z);
		
	
}

void GLProjectile::updateParticleEmitter(float& deltaTime) {
	switch (currentState)
	{
	case ACTIVE:
		this->projectileEmitter->UpdateEmitter(deltaTime);

		this->projectileEmitter->updatePosition(glm::vec4(this->transform->GetPos(), 1));
		this->projectileEmitter->updateScale(this->transform->GetScale().z);
		break;
	}
}

void GLProjectile::drawParticles(GLShader* shader) {
	switch (currentState)
	{
	case ACTIVE:
		this->projectileEmitter->Draw(shader);
		break;
	}
}

bool GLProjectile::hasParticleEmitter() {
	return this->projectileEmitter != nullptr;
}

void GLProjectile::CheckIfOutOfBounds()
{
	if (transform->m_pos.x > bounds::MAX_X || transform->m_pos.x < bounds::MIN_X)
	{
		currentState = INACTIVE;
		if (this->projectileEmitter != nullptr)
			this->projectileEmitter->clean();
	}
	else if (transform->m_pos.y > bounds::MAX_Y || transform->m_pos.y < bounds::MIN_Y)
	{
		currentState = INACTIVE;
		if (this->projectileEmitter != nullptr)
			this->projectileEmitter->clean();
	}
	else if (transform->m_pos.z > bounds::MAX_Z || transform->m_pos.z < bounds::MIN_Z)
	{
		currentState = INACTIVE;
		if (this->projectileEmitter != nullptr)
			this->projectileEmitter->clean();
	}
}

