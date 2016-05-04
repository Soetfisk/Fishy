#include "GLCollisionHandler.h"



GLCollisionHandler::~GLCollisionHandler()
{
	delete PowerUpHandler;
}

void GLCollisionHandler::CheckCollisions(float deltaTime)
{
	glm::vec3 distance;
	float distSqrd;
	AABB wall(glm::vec3(0), glm::vec3(125, 48, 86));
	for (int i = 0; i < players.size(); i++)
	{
		distance = players.at(i)->GetTransform().GetPos() - players.at(1 - i)->GetTransform().GetPos();
		distSqrd = glm::dot(distance,distance);
		if (distSqrd < 50)
		{
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

		if (!players.at(i)->GetBoundingBox().containsAABB(wall))
		{
			
			glm::vec3 dir = players.at(i)->GetBoundingBox().center - wall.center;
			float center_dist = glm::dot(dir, dir);
			glm::vec3 min_dist = players.at(i)->GetBoundingBox().halfDimension + wall.halfDimension;
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
		}

		for (int j = 0; j < players.at(i)->GetProjectiles().size(); j++)
		{
			if (players.at(i)->GetProjectiles().at(j)->GetBoundingBox().containsAABB(players.at(1 - i)->GetBoundingBox()))
			{
				players.at(1 - i)->HandleCollision(GLPlayer::HIT, deltaTime,players.at(i)->GetProjectiles().at(j)->GetForward() * 30.0f);
				players.at(i)->GetProjectiles().at(j)->Inactivate();
			}
		}

		for (unsigned int j = 0; j < this->NPCs.size(); j++) {

 			distance = players.at(i)->GetTransform().GetPos() - NPCs.at(j)->GetTransform().GetPos();
			distSqrd = glm::dot(distance, distance);
			if (distSqrd < 60)
			{
				AABB NpcSeenSpace(NPCs.at(j)->GetTransform().GetPos() +(NPCs.at(j)->GetForward() *10.f), glm::vec3(10, 10, 10));

				if (NPCs.at(j)->GetBoundingBox().containsAABB(players.at(i)->GetBoundingBox()))
				{
					if (NPCs.at(j)->GetCurrentState()!=NPC_INACTIVE && NPCs.at(j)->GetCurrentState() != NPC_BEINGEATEN)
					{
						NPCs.at(j)->gettingEaten(deltaTime, players.at(i)->GetTransform());
						players.at(i)->HandleCollision(GLPlayer::EATING, deltaTime, glm::vec3(0));
							
							if (NPCs.at(j)->GetIsPowerUp()==true)
							{
								PowerUpHandler->RemovePowerUpFish(NPCs.at(j),j);
								players.at(i)->SetPowerUp(GLPlayer::POWER_HIGH);
							}
							else
							{
								PowerUpHandler->RemoveAvailableFish(j);
							}
					}
				}
				else if (NpcSeenSpace.containsAABB(players.at(i)->GetBoundingBox()))
				{
					NPCs.at(j)->initiateFleeingState(players.at(i)->GetForward());
				}
			}
		}
	}
}

void GLCollisionHandler::AddPlayer(GLPlayer * player)
{
	this->players.push_back(player);
}

void GLCollisionHandler::AddPlayer(std::vector<GLPlayer*> players)
{
	for (int i = 0; i < players.size(); i++)
	{
		this->players.push_back(players.at(i));
	}
}

void GLCollisionHandler::RemovePlayer(GLPlayer * player)
{
	for (int i = 0; i < this->players.size(); i++)
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
	for (int i = 0; i < npcs.size(); i++)
	{
		this->NPCs.push_back(npcs.at(i));
	}
}

void GLCollisionHandler::RemoveNPC(GLNPC * npc)
{
	for (int i = 0; i < this->NPCs.size(); i++)
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
	for (int i = 0; i < models.size(); i++)
	{
		this->models.push_back(models.at(i));
	}
}

void GLCollisionHandler::RemoveModel(GLModel * model)
{
	for (int i = 0; i < this->models.size(); i++)
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
