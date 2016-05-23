#include "GLNPC_GoldFish.h"



GLNPC_GoldFish::GLNPC_GoldFish(FishBox * FSH_Loader, unsigned int modelID) : GLNPC(FSH_Loader, modelID)
{
	this->currentState = NPC_MOVE;
	transform->SetPos(glm::vec3(RNG::range(-DEADZONEX, DEADZONEX), RNG::range(-DEADZONEY, DEADZONEY), RNG::range(-DEADZONEZ, DEADZONEZ)));

	this->FishSpeedMultiplier = originalFishSpeedMultiplier;

	glm::vec3 scale = glm::vec3(RNG::range(1.0f, 1.5f));
	transform->SetScale(scale);
	this->TimeUntilChange = RNG::range(0.2f, 3.0f);
	this->forwardSpeed = RNG::range(0.0f, 3.3f); 
	this->rotationChange = glm::vec3(0, RNG::range(-1.0f, 1.0f), 0);

}

void GLNPC_GoldFish::NPCUpdate(float deltaTime)
{

	if (currentState == NPC_INACTIVE)
	{
		this->RespawnCountdown(deltaTime);
	} 

	if (currentState != NPC_INACTIVE)
	{
		TimeUntilChange -= deltaTime;
		if (TimeUntilChange < 0)
		{
			this->TimeUntilChange = RNG::range(0.2f, 3.0f);
			this->forwardSpeed = RNG::range(0.5f, 6.3f);
			this->rotationChange = glm::vec3(RNG::range(-0.1f, 0.1f), RNG::range(-0.8f, 0.8f), 0);
		}


		if (currentState == NPC_MOVE)
		{
			this->transform->m_pos += (this->GetForward() * forwardSpeed) * deltaTime;
			this->transform->m_rot += rotationChange * deltaTime;
			;
		}
		else if (currentState == NPC_FLEEING)
		{
			this->TimeUntilChange -= deltaTime;
			this->transform->m_pos += this->GetForward() * (forwardSpeed + 2 * 3) * deltaTime;
			this->transform->m_rot += rotationChange * deltaTime * 2.f;

			fleeingTimer -= deltaTime;
			if (fleeingTimer < 0)
			{
				currentState = NPC_MOVE;
			}


		}
		else if (currentState == NPC_BEINGEATEN)
		{
			
			this->transform->m_pos += HitMomentum;
			HitMomentum = HitMomentum * 0.98f;
			float CurrentScale = GetTransform().GetScale().y;
			if (CurrentScale > targetScale)
			{
				float ScaleLossFactor = 1.0f * deltaTime * 4;
				GetTransform().SetScale(glm::vec3(CurrentScale - ScaleLossFactor, CurrentScale - ScaleLossFactor, CurrentScale - ScaleLossFactor));
				BitenCoolDown -= deltaTime;
				if (GetTransform().GetScale().y < 0.5f)
				{
					NPCKill();
				}
			}
			BitenCoolDown -= deltaTime;
			if (BitenCoolDown < 0)
			{
				currentState = NPC_MOVE;
			}
		}
		checkboarderCollision();
		moveAnimation(deltaTime, 1 * forwardSpeed);
		
	}
}

void GLNPC_GoldFish::NPCDraw(GLShader & shader)
{
	if (currentState != NPC_INACTIVE)
	{
		this->Draw(shader);
	}
}

bool GLNPC_GoldFish::gettingEaten(bool& isKill, float BiteSize, glm::vec3 PushVector)
{
	if (this->currentState != NPC_INACTIVE && BitenCoolDown <= 0)
	{
		this->HitMomentum = PushVector;
		targetScale = this->GetTransform().GetScale().y - BiteSize;
		this->currentState = NPC_BEINGEATEN;
		BitenCoolDown = 2.0f;


		if (targetScale < 0.5f)
		{
			isKill = true;

		}
		else
		{
			isKill = false;
		}


		return true;

	}
	else
	{
		return false;
	}

}



void GLNPC_GoldFish::NPCKill()
{
	this->currentState = NPC_INACTIVE;
	
	if (this->isPowerUp == true)
	{
		this->isPowerUp = false;
		this->meshes[0]->SetMaterial(originalMaterial);
	}

	this->npc_blood_emitter->disableSpawn();
}

void GLNPC_GoldFish::initiateFleeingState(glm::vec3 playerForwardVector)
{
	if (this->currentState != NPC_BEINGEATEN && this->currentState != NPC_INACTIVE)
	{
		this->currentState = NPC_FLEEING;
		//this->transform->SetRot(playerForwardVector);
		fleeingTimer = (float)RNG::range(3, 10);
	}
}

void GLNPC_GoldFish::checkboarderCollision()
{
	glm::vec3 pos = transform->GetPos();
	glm::vec3 rot = transform->GetRot();

	if (rot.x>1.0f)
	{
		transform->SetRot(glm::vec3(1.0f, rot.y, rot.z));
		this->rotationChange = glm::vec3(RNG::range(-0.3f, -0.2f), RNG::range(-0.8f, 0.8f), 0);

	}

	else if (rot.x < -1.0f)
	{
		transform->SetRot(glm::vec3(-1.0f, rot.y, rot.z));
		this->rotationChange = glm::vec3(RNG::range(0.1f, 0.3f), RNG::range(-0.8f, 0.8f), 0);
	}
	if (pos.x < -this->DEADZONEX)
	{
		pos.x = (float)-DEADZONEX;
		if (rot.y >= 0)
		{
			this->rotationChange = glm::vec3(RNG::range(-0.1f, 0.1f), RNG::range(1.5f, 2.0f), 0);
		}
		else
		{
			this->rotationChange = glm::vec3(RNG::range(-0.1f, 0.1f), RNG::range(-2.0f, -1.5f), 0);
		}
	}
	else if (pos.x >this->DEADZONEX)
	{
		pos.x = (float)DEADZONEX;
		if (rot.y >= 0)
		{
			this->rotationChange = glm::vec3(RNG::range(-0.1f, 0.1f), RNG::range(1.5f, 2.0f), 0);
		}
		else
		{
			this->rotationChange = glm::vec3(RNG::range(-0.1f, 0.1f), RNG::range(-2.0f, -1.5f), 0);
		}
	}

	if (pos.y < -this->DEADZONEY)
	{
		pos.y = (float)-DEADZONEY;
		this->rotationChange = glm::vec3(RNG::range(-0.3f, -0.2f), RNG::range(-0.8f, 0.8f), 0);
	}
	else if (pos.y >this->DEADZONEY)
	{
		pos.y = (float)DEADZONEY;
		this->rotationChange = glm::vec3(RNG::range(0.2f, 0.3f), RNG::range(-0.8f, 0.8f), 0);
	}

	if (pos.z < -this->DEADZONEZ)
	{
		pos.z = (float)-DEADZONEZ;

		if (rot.y >= 0)
		{
			this->rotationChange = glm::vec3(RNG::range(-0.1f, 0.1f), RNG::range(1.5f, 2.0f), 0);
		}
		else
		{
			this->rotationChange = glm::vec3(RNG::range(-0.1f, 0.1f), RNG::range(-2.0f, -1.0f), 0);
		}
	}
	else if (pos.z >this->DEADZONEZ)
	{
		pos.z = (float)DEADZONEZ;
		
		if (rot.y >= 0)
		{
			this->rotationChange = glm::vec3(RNG::range(-0.1f, 0.1f), RNG::range(1.5f, 2.0f), 0);
		}
		else
		{
			this->rotationChange = glm::vec3(RNG::range(-0.1f, 0.1f), RNG::range(-2.0f, -1.5f), 0);
		}
	}

	transform->SetPos(pos);
	
}




void GLNPC_GoldFish::ResetFish()
{
	this->currentState = NPC_MOVE;
	transform->SetPos(glm::vec3(RNG::range(-DEADZONEX, DEADZONEX), RNG::range(-DEADZONEY, DEADZONEY), RNG::range(-DEADZONEZ, DEADZONEZ)));

	glm::vec3 scale = glm::vec3(RNG::range(1.0f, 1.5f));
	transform->SetScale(scale);

	FishSpeedMultiplier = 1.0f;
	fishSize = 1.0f;

	this->TimeUntilChange = RNG::range(0.2f, 3.0f);
	this->forwardSpeed = RNG::range(0.0f, 3.3f);
	this->rotationChange = glm::vec3(0, RNG::range(-1.0f, 1.0f), 0);
	
	this->isPowerUp = false;
	this->meshes.at(0)->SetMaterial(originalMaterial);

	this->BitenCoolDown = 0;
}

void GLNPC_GoldFish::ResetFish(float size)
{
	this->currentState = NPC_MOVE;
	transform->SetPos(glm::vec3(RNG::range(-DEADZONEX, DEADZONEX), RNG::range(-DEADZONEY, DEADZONEY), RNG::range(-DEADZONEZ, DEADZONEZ)));
	glm::vec3 scale = glm::vec3(RNG::range(1.1f + size, 3.0f + size));
	transform->SetScale(scale);

	FishSpeedMultiplier = size;
	this->TimeUntilChange = RNG::range(0.2f, 3.0f);
	this->forwardSpeed = FishSpeedMultiplier * RNG::range(0.0f, 3.3f);
	this->rotationChange = glm::vec3(0, RNG::range(-1.0f, 1.0f), 0);
	this->isPowerUp = false;
	this->meshes.at(0)->SetMaterial(originalMaterial);

	this->BitenCoolDown = 0;
}


