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
	GLProjectile(int maxDist, float speed);
	GLProjectile(FishBox* FSH_Loader, unsigned int modelID, int maxDist, float speed);
	virtual ~GLProjectile();
	
	void TestDraw(GLShader& shader);	// 
	void TestUpdate(float& dt);			// 
	void ResetTo(glm::vec3& pos);		// Reset projectile to a new position
	void SetForward(glm::vec3& forward);// 
	void SetSpeed(float& speed);		// 
	void Activate();					// Activates the projectile 
	void Inactivate();					// Deactivates the projectile
	bool isActive();					// Returns true if the projectile is active

private:
	int maxDistance;				// The max distance the projecitle is allowed to travel
	float distanceTraveled;			// Keeping track of how long the projectile has traveled 
	float speed;					// The speed the bullet travels at
	glm::vec3 forward;				// The direction the projectile will travel
	glm::vec3 forwardSpeed;			// Forward * speed
	ProjectileStates currentState;	// The current state
};

