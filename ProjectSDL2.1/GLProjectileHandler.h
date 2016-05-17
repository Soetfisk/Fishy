#pragma once

#include "GLProjectile.h"

enum ProjectilePowerUpState
{
	REGULAR,
	SHOTGUN,
	BIG,
	FAST,
	STRONG,

	NUM_PROJPOWERUPSTATES
};

class GLProjectileHandler
{
public:
	GLProjectileHandler();
	GLProjectileHandler(FishBox* FSH_Loader, unsigned int modelID, int nrOfProjectiles, int projectileActiveTime, float projectileSpeed, float cooldown = 1.0f);
	virtual ~GLProjectileHandler();

	void Shoot(glm::vec3 forward, glm::vec3 pos, glm::vec3 rot, glm::vec3 velocity, glm::vec3 right, glm::vec3 up);// Take a inactive projectile and make it active or create a new projectile if there is no inactive
	void ChangeStateTo(ProjectilePowerUpState state);
	void Update(float& dt);																		// Update all active projectiles
	void Draw(GLShader& shader);																// Draw all active Projectiles
	std::vector<GLProjectile*>& GetProjectiles();
	std::vector<GLProjectile*> GetActiveProjectiles();
	bool CanShoot()
	{
		return !cooldown;
	}

	void StandardProjectileSize(float size);


	void drawParticles(GLShader *shader);
	void updateParticles(float& deltaTime);
	void addParticleHandlerReference(ParticleHandler* pHandlerRef);

private:
	const float SHOTGUN_OFFSET = 1.0f;
	const float BIG_PROJECTILE_MULTIPLIER = 3.0f;
	const float MAX_ANGLE = 0.2f;

	FishBox* FSH_Loader; 
	unsigned int modelID;
	int projectileActiveTime;																								
	float projectileSpeed, projectileStrength, projectileSize;
	float standardProjectileSize;
	float cooldownDuration, cooldownCounter;
	bool cooldown;
	ProjectilePowerUpState currentState;
	
	std::vector<GLProjectile*>	projectiles;																			
	GLProjectile* GetInactiveProjectile();
	void RegularShoot(glm::vec3 forward, glm::vec3 pos, glm::vec3 rot, glm::vec3 velocity);
	void ShotgunShoot(glm::vec3 forward, glm::vec3 pos, glm::vec3 rot, glm::vec3 velocity, glm::vec3 right, glm::vec3 up);

	ParticleHandler *particleHandlerReference;

	void addEmitterToProjectile(GLProjectile* projectile, glm::vec3 pos);
};
