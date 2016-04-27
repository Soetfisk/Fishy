#pragma once

#include "GLProjectile.h"

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

private:
	FishBox* FSH_Loader; 
	unsigned int modelID;
	int projectileActiveTime;																								
	float projectileSpeed;
	
	std::vector<GLProjectile*>	projectiles;																			
	GLProjectile* GetInactiveProjectile();																				
};

