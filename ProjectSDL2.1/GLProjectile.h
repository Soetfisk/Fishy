#pragma once

#include "GLModel.h"

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
	GLProjectile(FishBox& FSH_Loader, char* filePath, int maxDist, float speed);
	virtual ~GLProjectile();
	
	void TestDraw(GLShader& shader);	// 
	void TestUpdate(float& dt);			// 
	void ResetTo(glm::vec3& pos);		// Reset projectile to a new position
	void SetForward(glm::vec3 forward);	// 
	void SetVelocity(glm::vec3 velocity);
	void ShootAt(glm::vec3 startPos, glm::vec3 forward, glm::vec3 velocity);
	void Scale(glm::vec3 scale);
	void SetSpeed(float& speed);		// 
	void Activate();					// Activates the projectile 
	void Inactivate();					// Deactivates the projectile
	bool IsActive();					// Returns true if the projectile is active

private:
	int maxDistance;				// The max distance the projecitle is allowed to travel
	float distanceTraveled;			// Keeping track of how long the projectile has traveled 
	//float speed;					// The speed the bullet travels at
	glm::vec3 velocity;
	glm::vec3 forward;				// The direction the projectile will travel
	glm::vec3 forwardVel;
	//glm::vec3 forwardSpeed;			// Forward * speed
	ProjectileStates currentState;	// The current state
};

/*
	Change size(scale)
	Change speed
	Change distance

*/