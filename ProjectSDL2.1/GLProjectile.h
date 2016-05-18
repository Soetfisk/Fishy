#pragma once

#include "GLModel.h"
#include "ParticleHandler.h"

enum ProjectileStates
{
	ACTIVE,
	INACTIVE,

	NR_OF_STATES,
};

class GLProjectile : public GLModel
{
public:
	GLProjectile();
	GLProjectile(int maxDist);
	GLProjectile(FishBox* FSH_Loader, unsigned int modelID, int projectileActiveTime, float projectileSpeed, float projectileStrength = 10.0f, float projectileSize = 1.0f);
	virtual ~GLProjectile();
	
	void TestDraw(GLShader& shader);	// 
	void TestUpdate(float& dt);			// 
	void ResetTo(glm::vec3& pos);		// Reset projectile to a new position
	void SetForward(glm::vec3 forward);	// 
	void SetVelocity(glm::vec3 velocity);
	void Shoot(glm::vec3 startPos, glm::vec3 forward, glm::vec3 velocity, glm::vec3 rot);
	void SetScale(float scale);
	void setMaxActiveTime(int Time); //Not used
	void SetSpeed(float& speed);		// 
	void SetStrength(float strength);
	void Activate();					// Activates the projectile 
	void Inactivate();					// Deactivates the projectile
	bool IsActive();					// Returns true if the projectile is active

	void addParticleEmitter(ParticleEmitter* emitter);
	void updateParticleEmitter(float& deltaTime);
	void drawParticles(GLShader* shader);

	bool hasParticleEmitter();
private:
	const float MIN_PROJECTILE_SPEED = 30;
	const float MIN_SPEED = 0.5f;

	float checkForOutOfBoundsValue;
	int maxActiveTime, MaxActiveTimeUnaltered;				// The max distance the projecitle is allowed to travel
	float timeActive;				// Keeping track of how long the projectile has traveled 
	float speed;					// The speed the bullet travels at
	float strength;
	glm::vec3 velocity;
	glm::vec3 forward;				// The direction the projectile will travel
	glm::vec3 forwardVel;
	ProjectileStates currentState;	// The current state
	ParticleEmitter* projectileEmitter;

	void CheckIfOutOfBounds();
};

/*
	Change size(scale)
	Change speed
	Change distance

*/