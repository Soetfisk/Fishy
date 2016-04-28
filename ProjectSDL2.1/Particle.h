#pragma once
#include "GLUtil.h"


class Particle
{
private:
	int particleID;
	float lifeTimeMax, lifeTimeCurrent;
	bool isActive;

	glm::mat4 transformMatrix;
	glm::vec4 velocity;
	glm::vec4 position;
public:
	Particle(float lifeTime, glm::vec4 position);
	~Particle();

	bool Update(const float &deltaTime);
	bool GetIsActive();


	glm::mat4 GetTransformMatrix();
	glm::vec4 GetVelocity();
	glm::vec4 GetPosition();
};