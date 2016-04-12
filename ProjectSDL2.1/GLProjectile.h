#pragma once

#include "GLModel.h"

class GLProjectile : public GLModel
{
public:
	GLProjectile();
	GLProjectile(glm::vec3& forward, int& maxDist, float& speed);
	GLProjectile(std::string& filePath, glm::vec3& forward);
	virtual ~GLProjectile();
	
	void TestDraw(GLShader& shader);
	void TestUpdate(float& dt);
	void ResetTo(glm::vec3& pos);
	void SetForward(glm::vec3& forward);
	void Activate();
	void Inactivate();

private:
	enum ProjectileStates
	{
		ACTIVE,
		INACTIVE,

		NR_OF_STATES,
	};

	int maxDistance;
	float distanceTraveled;
	float speed;
	glm::vec3 forward;
	
	ProjectileStates currentState;
};

