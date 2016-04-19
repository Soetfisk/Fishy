#include "Particle.h"



Particle::Particle(float lifeTime)
{
	this->lifeTimeCurrent = 0;
	this->lifeTimeMax = lifeTime;
	this->isActive = true;
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
