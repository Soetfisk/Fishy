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
	GLProjectile(glm::vec3& forward, int& maxDist, float& speed);
	GLProjectile(std::string& filePath, glm::vec3& forward, int& maxDist, float& speed);
	virtual ~GLProjectile();
	
	void TestDraw(GLShader& shader);
	void TestUpdate(float& dt);
	void ResetTo(glm::vec3& pos);
	void SetForward(glm::vec3& forward);
	void SetSpeed(float& speed);
	void Activate();
	void Inactivate();
	ProjectileStates& getCurrentState();

private:
	int maxDistance;				// The max distance the projecitle is allowed to travel
	float distanceTraveled;			// Keeping track of how long the projectile has traveled 
	float speed;					// The speed the bullet travels at
	glm::vec3 forward;				// The direction the projectile will travel
	ProjectileStates currentState;	// The current state 
};

