#include "GLCollisionHandler.h"



GLCollisionHandler::~GLCollisionHandler()
{
	delete PowerUpHandler;
}

void GLCollisionHandler::CheckCollisions(float deltaTime)
{
	glm::vec3 distance;
	float distSqrd;
	//AABB for aquarium walls
	AABB wall(glm::vec3(0), glm::vec3(125, 50, 85));



	for (size_t i = 0; i < players.size(); i++)
	{
		distance = players.at(i)->GetTransform().GetPos() - players.at(1 - i)->GetTransform().GetPos();
		distSqrd = glm::dot(distance,distance);
		if (distSqrd < 100)
		{
			//checks if players collide and if so it pushes the player out of the other player
			if (players.at(i)->GetBoundingBox().containsAABB(players.at(1-i)->GetBoundingBox()))
			{

				glm::vec3 dir = players.at(i)->GetBoundingBox().center - players.at(1 - i)->GetBoundingBox().center;
				float center_dist = glm::dot(dir, dir);
				glm::vec3 min_dist = players.at(i)->GetBoundingBox().halfDimension + players.at(1 - i)->GetBoundingBox().halfDimension;
				if (center_dist < min_dist.x*min_dist.x)
				{
					players.at(i)->GetTransform().m_pos.x += glm::normalize(dir).x * (min_dist.x - sqrt(center_dist));
				}
				if (center_dist < min_dist.y*min_dist.y)
				{
					players.at(i)->GetTransform().m_pos.y += glm::normalize(dir).y * (min_dist.y - sqrt(center_dist));
				}
				if (center_dist < min_dist.z*min_dist.z)
				{
					players.at(i)->GetTransform().m_pos.z += glm::normalize(dir).z * (min_dist.z - sqrt(center_dist));
				}
			}
		}

		for (int j = 0; j < models.size(); j++)
		{
			distance = players.at(i)->GetTransform().GetPos() - this->models.at(j)->GetTransform().GetPos();
			distSqrd = glm::dot(distance, distance);
			if (distSqrd < 100)
			{
				//checks if players collide and if so it pushes the player out of the other player
				if (players.at(i)->GetBoundingBox().containsAABB(this->models.at(j)->GetBoundingBox()))
				{

					glm::vec3 dir = players.at(i)->GetBoundingBox().center - this->models.at(j)->GetBoundingBox().center;
					float center_dist = glm::dot(dir, dir);
					glm::vec3 min_dist = players.at(i)->GetBoundingBox().halfDimension + this->models.at(j)->GetBoundingBox().halfDimension;
					if (center_dist < min_dist.x*min_dist.x)
					{
						players.at(i)->GetTransform().m_pos.x += glm::normalize(dir).x * (min_dist.x - sqrt(center_dist));
					}
					if (center_dist < min_dist.y*min_dist.y)
					{
						players.at(i)->GetTransform().m_pos.y += glm::normalize(dir).y * (min_dist.y - sqrt(center_dist));
					}
					if (center_dist < min_dist.z*min_dist.z)
					{
						players.at(i)->GetTransform().m_pos.z += glm::normalize(dir).z * (min_dist.z - sqrt(center_dist));
					}
				}
			}
		}
		//checks if the player is out of bounds and if so pushes the player back in
		//if (!players.at(i)->GetBoundingBox().containsAABB(wall))
		//{
			
			glm::vec3 dir = players.at(i)->GetBoundingBox().center - wall.center;
			float center_dist = glm::dot(dir, dir);
			glm::vec3 min_dist =  wall.halfDimension - players.at(i)->GetBoundingBox().halfDimension;
			glm::vec3 normal(0);
			if (dir.x < -min_dist.x && players.at(i)->getVelocity().x < 0)
			{
				normal += glm::vec3(1, 0, 0);
			}
			else if (dir.x > min_dist.x && players.at(i)->getVelocity().x > 0)
			{
				normal += glm::vec3(-1, 0, 0);
			}
			if (dir.y < -min_dist.y && players.at(i)->getVelocity().y < 0)
			{
				normal += glm::vec3(0, 1, 0);
			}
			if (dir.y > min_dist.y && players.at(i)->getVelocity().y > 0)
			{
				normal += glm::vec3(0, -1, 0);
			}
			if (dir.z < -min_dist.z && players.at(i)->getVelocity().z < 0)
			{
				normal += glm::vec3(0, 0, 1);
			}
			if (dir.z > min_dist.z && players.at(i)->getVelocity().z > 0)
			{
				normal += glm::vec3(0, 0, -1);
			}
			players.at(i)->getVelocity() -= normal * glm::dot(players.at(i)->GetVelocity(), normal);
		//}
		//checks if a projectile hits a player and if so adds the momentum of the projectile too the player
		for (size_t j = 0; j < players.at(i)->GetProjectiles().size(); j++)
		{
			if (players.at(i)->GetProjectiles().at(j)->GetBoundingBox().containsAABB(players.at(1 - i)->GetBoundingBox()))
			{
				players.at(1 - i)->HandleCollision(GLPlayer::EATING, deltaTime, glm::vec3(-0.10f));
				players.at(1 - i)->HandleCollision(GLPlayer::HIT, deltaTime,players.at(i)->GetProjectiles().at(j)->GetForward() * 30.0f);
				players.at(i)->GetProjectiles().at(j)->Inactivate();
			}
		}

		for (unsigned int j = 0; j < this->NPCs.size(); j++) {
			distance = players.at(i)->GetTransform().GetPos() - NPCs.at(j)->GetTransform().GetPos();
			distSqrd = glm::dot(distance, distance);
			if (distSqrd < 60)
			{

				AABB NpcSeenSpace(NPCs.at(j)->GetTransform().GetPos() + (NPCs.at(j)->GetForward() *10.f), glm::vec3(10, 10, 10));


				//check if player collides with a fish if so it will eat a part of it and gets score
				if (NPCs.at(j)->GetBoundingBox().containsAABB(players.at(i)->GetBoundingBox()))
				{
					if (players.at(i)->GetTransform().GetScale().x + 0.5f >= NPCs.at(j)->GetTransform().GetScale().x)
					{
						if (NPCs.at(j)->GetCurrentState() != NPC_INACTIVE /*&& NPCs.at(j)->GetCurrentState() != NPC_BEINGEATEN*/)
						{

							if (!NPCs.at(j)->hasBloodEmitter()) {
								NPCs.at(j)->addBloodEmitter(pHandlerRef->CreateEmitter(EmitterType::BLOOD, glm::vec4(NPCs.at(i)->GetTransform().GetPos(), 1)));
							}
							NPCs.at(j)->enableBlood();

							bool isKill = false;
							bool result = NPCs.at(j)->gettingEaten(isKill, players.at(i)->GetTransform().GetScale().x / 4, -glm::normalize(players.at(i)->GetTransform().GetPos() - NPCs.at(j)->GetTransform().GetPos())*0.7f);
							players.at(i)->HandleCollision(GLPlayer::HIT, deltaTime, (glm::normalize(players.at(i)->GetTransform().GetPos() - NPCs.at(j)->GetTransform().GetPos())) * 2.0f);

							if (result == true)
							{
								players.at(i)->HandleCollision(GLPlayer::EATING, deltaTime, glm::vec3(roundf(NPCs.at(j)->GetTransform().GetScale().x * 100) / 100));
								if (isKill == true)
								{
									if (NPCs.at(j)->GetIsPowerUp() == true)
									{

										PowerUpHandler->RemovePowerUpFish(NPCs.at(j), j);
										players.at(i)->SetRandomPowerUp();
									}
									else
									{
										PowerUpHandler->RemoveAvailableFish(j);
									}
								}
							}
							players.at(i)->HandleCollision(GLPlayer::HIT, deltaTime, (glm::normalize(players.at(i)->GetTransform().GetPos() - NPCs.at(j)->GetTransform().GetPos())) * 10.0f);

						}
						else if (NpcSeenSpace.containsAABB(players.at(i)->GetBoundingBox()))
						{
							NPCs.at(j)->initiateFleeingState(players.at(i)->GetForward());
						}
					}
					else // if you collide with bigger fish
					{
						players.at(i)->HandleCollision(GLPlayer::HIT, deltaTime, (glm::normalize(players.at(i)->GetTransform().GetPos() - NPCs.at(j)->GetTransform().GetPos())) * 100.0f);
					}



					//if the player is seen it will init fleeing behavior of npc

				}
			}
		}
	}
}


//Getting eaten


void GLCollisionHandler::AddPlayer(GLPlayer * player)
{
	this->players.push_back(player);
}

void GLCollisionHandler::AddPlayer(std::vector<GLPlayer*> players)
{
	for (size_t i = 0; i < players.size(); i++)
	{
		this->players.push_back(players.at(i));
	}
}

void GLCollisionHandler::RemovePlayer(GLPlayer * player)
{
	for (size_t i = 0; i < this->players.size(); i++)
	{
		if (this->players.at(i) == player)
		{
			this->players.erase(players.begin() + i);
		}
	}
	
}

void GLCollisionHandler::AddNPC(GLNPC * npc)
{
	this->NPCs.push_back(npc);
}

void GLCollisionHandler::AddNPC(std::vector<GLNPC*> npcs)
{
	for (size_t i = 0; i < npcs.size(); i++)
	{
		this->NPCs.push_back(npcs.at(i));
	}
}

void GLCollisionHandler::RemoveNPC(GLNPC * npc)
{
	for (size_t i = 0; i < this->NPCs.size(); i++)
	{
		if (this->NPCs.at(i) == npc)
		{
			this->NPCs.erase(NPCs.begin() + i);
		}
	}
}

void GLCollisionHandler::AddModel(GLModel * model)
{
	this->models.push_back(model);
}

void GLCollisionHandler::AddModel(std::vector<GLModel*> models)
{
	for (size_t i = 0; i < models.size(); i++)
	{
		this->models.push_back(models.at(i));
	}
}

void GLCollisionHandler::RemoveModel(GLModel * model)
{
	for (size_t i = 0; i < this->models.size(); i++)
	{
		if (this->models.at(i) == model)
		{
			this->models.erase(models.begin() + i);
		}
	}
}

void GLCollisionHandler::InitiatePowerUpHandler()
{
	this->PowerUpHandler = new NpcPowerUpHandler(this->NPCs);
}

void GLCollisionHandler::resetPowerUpHandler()
{
	PowerUpHandler->initiatePowerFishes();
	PowerUpHandler->AsssignStartPowerupFishes();
}

void GLCollisionHandler::AddParticleHandlerReference(ParticleHandler* pHandlerRef) {
	this->pHandlerRef = pHandlerRef;
	this->PowerUpHandler->addParticleHandlerReference(pHandlerRef);
	this->PowerUpHandler->AsssignStartPowerupFishes();
}