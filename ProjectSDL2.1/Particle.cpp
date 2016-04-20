#include "Particle.h"



Particle::Particle(float lifeTime, glm::vec4 position)
{
	this->lifeTimeCurrent = 0;
	this->lifeTimeMax = lifeTime;
	this->isActive = true;
	this->position = position;
	this->transformMatrix =  glm::mat4(1.0);
	this->velocity = glm::vec4(0, 0, -1, 1);

}


glm::mat4 Particle::GetTransformMatrix() {
	return this->transformMatrix;
}
glm::vec4 Particle::GetVelocity() {
	return this->velocity;

}
glm::vec4 Particle::GetPosition() {
	return this->position;
}

bool Particle::Update(const float &deltaTime) {
	this->lifeTimeCurrent += deltaTime;


	if (lifeTimeCurrent >= lifeTimeMax)
		return true;
	return false;
}

bool Particle::GetIsActive() {
	return this->isActive;
}

Particle::~Particle()
{
}
