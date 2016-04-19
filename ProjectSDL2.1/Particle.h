#pragma once
class Particle
{
private:
	
	float lifeTimeMax, lifeTimeCurrent;
	bool isActive;
public:
	Particle(float lifeTime);
	~Particle();

	bool Update(const float &deltaTime);
	bool GetIsActive();
};

