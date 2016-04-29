#include "GLNPC_BlueTang.h"



GLNPC_BlueTang::GLNPC_BlueTang(FishBox * FSH_Loader, unsigned int modelID) : GLNPC(FSH_Loader, modelID)
{
	this->currentState = NPC_MOVE;
	transform->SetPos(glm::vec3(RNG::range(-20, 20), RNG::range(-2, 2), RNG::range(-20, 20)));
	glm::vec3 scale = glm::vec3(RNG::range(1.1f,3.0f));
	transform->SetScale(scale);

	this->TimeUntilChange = RNG::range(0.2, 3.0f);
	this->scaleChange = RNG::range(-0.02f, 0.02f);
	this->forwardSpeed = FishSpeedMultiplier * RNG::range(0.0f, 3.3f);
	this->rotationChange = glm::vec3(0, RNG::range(-1.0f, 1.0f), 0);
}

void GLNPC_BlueTang::NPCUpdate(float deltaTime)
{
	if (currentState != NPC_INACTIVE)
	{
		TimeUntilChange -= deltaTime;
		if (TimeUntilChange < 0)
		{
			this->TimeUntilChange = RNG::range(0.2, 3.0f);
			this->forwardSpeed = FishSpeedMultiplier * RNG::range(0.5f, 6.3f);
			this->rotationChange = glm::vec3(RNG::range(-0.1f, 0.1f), RNG::range(-1.0f, 1.0f), 0);
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
			;

		}

		//temp
		glm::vec3 pos = transform->GetPos();
		if (pos.x < -this->DEADZONEX)
		{
			pos.x = -DEADZONEX;
		}
		else if (pos.x >this->DEADZONEX)
		{
			pos.x = DEADZONEX;
		}

		if (pos.y < -this->DEADZONEY)
		{
			pos.y = -DEADZONEY;
		}
		else if (pos.y >this->DEADZONEY)
		{
			pos.y = DEADZONEY;
		}

		if (pos.z < -this->DEADZONEZ)
		{
			pos.z = -DEADZONEZ;
		}
		else if (pos.y >this->DEADZONEZ)
		{
			pos.z = DEADZONEZ;
		}

		transform->SetPos(pos);
	}
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
		glm::vec3 reduce = this->transform->GetScale() - deltaTime / 2;
		this->transform->SetScale(reduce);
		this->transform->SetPos(playerTransform.GetPos());
		this->currentState = NPC_BEINGEATEN;

	}
}

void GLNPC_BlueTang::NPCKill()
{
	this->currentState = NPC_INACTIVE;
}

void GLNPC_BlueTang::initiateFleeingState(glm::vec3 playerForwardVector)
{
	if (this->currentState != NPC_BEINGEATEN && this->currentState != NPC_INACTIVE)
	{
		this->currentState = NPC_FLEEING;
		//this->transform->SetRot(playerForwardVector);
		fleeingTimer = RNG::range(3, 10);
	}
}

int GLNPC_BlueTang::GetCurrentState()
{
	return this->currentState;
}
