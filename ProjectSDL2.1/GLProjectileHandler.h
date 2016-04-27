#pragma once

#include "GLProjectile.h"

class GLProjectileHandler
{
public:
	GLProjectileHandler();
	GLProjectileHandler(int nrOfProjectiles, int projectileTravelDisntace, float projectileSpeed, FishBox* FSH_Loader, unsigned int modelID);
	virtual ~GLProjectileHandler();

	void Shoot(glm::vec3& forward, glm::vec3& pos, glm::vec3& rot);	// Take a inactive projectile and make it active or create a new projectile if there is no inactive
	void Update(float& dt);											// Update all active projectiles
	void Draw(GLShader& shader);// Draw all active Projectiles
	std::vector<GLProjectile*>& GetProjectiles();

private:
	int projectileTravelDistance;																			// For creating projectiles
	float projectileSpeed;																					// For creating projectiles
	std::vector<GLProjectile*>	projectiles;																// 
	GLProjectile* GetInactiveProjectile();																	//
	void ActivateProjectile(GLProjectile* projectile, glm::vec3& forward, glm::vec3& pos, glm::vec3& rot);	//
	unsigned int projectileModelID;
	FishBox * FSH_Loader;
};

