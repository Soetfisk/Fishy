#include "GLNPC_BlueTang.h"



GLNPC_BlueTang::GLNPC_BlueTang(FishBox * FSH_Loader, unsigned int modelID) : GLNPC(FSH_Loader, modelID)
{
	this->currentState = NPC_MOVE;
	transform->SetPos(glm::vec3(RNG::range(-DEADZONEX, DEADZONEX), RNG::range(-DEADZONEY, DEADZONEY), RNG::range(-DEADZONEZ, DEADZONEZ)));
	glm::vec3 scale = glm::vec3(RNG::range(1.1f,3.0f));
	transform->SetScale(scale);

	this->TimeUntilChange = RNG::range(0.2f, 3.0f);
	this->forwardSpeed = FishSpeedMultiplier * RNG::range(0.0f, 3.3f);
	this->rotationChange = glm::vec3(0, RNG::range(-1.0f, 1.0f), 0);
}

void GLNPC_BlueTang::NPCUpdate(float deltaTime)
{
	//if (currentState != NPC_INACTIVE)
	//{
	//	TimeUntilChange -= deltaTime;
	//	if (TimeUntilChange < 0)
	//	{
	//		this->TimeUntilChange = RNG::range(0.2f, 3.0f);
	//		this->forwardSpeed = FishSpeedMultiplier * RNG::range(0.5f, 6.3f);
	//		this->rotationChange = glm::vec3(RNG::range(-0.1f, 0.1f), RNG::range(-1.0f, 1.0f), 0);
	//	}


	//	if (currentState == NPC_MOVE)
	//	{
	//		this->transform->m_pos += (this->GetForward() * forwardSpeed) * deltaTime;
	//		this->transform->m_rot += rotationChange * deltaTime;
	//		;
	//	}
	//	else if (currentState == NPC_FLEEING)
	//	{
	//		this->TimeUntilChange -= deltaTime;
	//		this->transform->m_pos += this->GetForward() * (forwardSpeed + 2 * 3) * deltaTime;
	//		this->transform->m_rot += rotationChange * deltaTime * 2.f;

	//		fleeingTimer -= deltaTime;
	//		if (fleeingTimer < 0)
	//		{
	//			currentState = NPC_MOVE;
	//		}


	//	}
	//	else if (currentState == NPC_BEINGEATEN)
	//	{
	//		glm::vec3 reduce = this->transform->GetScale() - deltaTime / 2;
	//		this->transform->SetScale(reduce);
	//		if (GetTransform().GetScale().y < 0.2)
	//		{
	//			NPCKill();
	//		}
	//	}
	//	checkboarderCollision();
	//}
}

void GLNPC_BlueTang::NPCDraw(GLShader & shader)
{
	if (currentState != NPC_INACTIVE)
	{
		this->Draw(shader);
	}
}

void GLNPC_BlueTang::gettingEaten(float deltaTime, GLTransform playerTransform)
{
	if (this->currentState != NPC_INACTIVE)
	{
		
		this->transform->SetPos(playerTransform.GetPos());
		this->currentState = NPC_BEINGEATEN;

	}
}

void GLNPC_BlueTang::NPCKill()
{
	this->currentState = NPC_INACTIVE;
	if (this->isPowerUp == true)
	{
		;//printf("i wanna be the very fish, that no one ever was");
	}
}

void GLNPC_BlueTang::initiateFleeingState(glm::vec3 playerForwardVector)
{
	if (this->currentState != NPC_BEINGEATEN && this->currentState != NPC_INACTIVE)
	{
		this->currentState = NPC_FLEEING;
		//this->transform->SetRot(playerForwardVector);
		fleeingTimer = (float)RNG::range(3, 10);
	}
}

void GLNPC_BlueTang::checkboarderCollision()
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



bool GLNPC_BlueTang::GetIsPowerUp()
{
	return isPowerUp;
}

void GLNPC_BlueTang::ResetFish()
{
	this->currentState = NPC_MOVE;
	transform->SetPos(glm::vec3(RNG::range(-DEADZONEX, DEADZONEX), RNG::range(-DEADZONEY, DEADZONEY), RNG::range(-DEADZONEZ, DEADZONEZ)));
	glm::vec3 scale = glm::vec3(RNG::range(1.1f, 3.0f));
	transform->SetScale(scale);

	this->TimeUntilChange = RNG::range(0.2f, 3.0f);
	this->forwardSpeed = FishSpeedMultiplier * RNG::range(0.0f, 3.3f);
	this->rotationChange = glm::vec3(0, RNG::range(-1.0f, 1.0f), 0);
}
