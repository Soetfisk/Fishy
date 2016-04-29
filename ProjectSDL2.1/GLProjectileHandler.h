#pragma once

#include "GLProjectile.h"

enum ProjectilePowerUpState
{
	REGULAR,
	SHOTGUN,
	BIG,
	FAST,
	STRONG,
	NUM_STATES
};

class GLProjectileHandler
{
public:
	GLProjectileHandler();
	GLProjectileHandler(FishBox* FSH_Loader, unsigned int modelID, int nrOfProjectiles, int projectileActiveTime, float projectileSpeed);
	virtual ~GLProjectileHandler();

	void Shoot(glm::vec3 forward, glm::vec3 pos, glm::vec3 rot, glm::vec3 velocity);			// Take a inactive projectile and make it active or create a new projectile if there is no inactive
	void Update(float& dt);																		// Update all active projectiles
	void Draw(GLShader& shader);																// Draw all active Projectiles
	std::vector<GLProjectile*>& GetProjectiles();
	std::vector<GLProjectile*> GetActiveProjectiles();

private:
	FishBox* FSH_Loader; 
	unsigned int modelID;
	int projectileActiveTime;																								
	float projectileSpeed;
	float projectileStrength;
	ProjectilePowerUpState currentState;
	
	std::vector<GLProjectile*>	projectiles;																			
	GLProjectile* GetInactiveProjectile();
	void RegularShoot(glm::vec3 forward, glm::vec3 pos, glm::vec3 rot, glm::vec3 velocity);
	void ShotgunShoot(glm::vec3 forward, glm::vec3 pos, glm::vec3 rot, glm::vec3 velocity);
};

/*
	Shotgun
	Stora
	Snabba
	Starka
*/
