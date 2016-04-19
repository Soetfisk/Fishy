#include "GLNPC.h"


GLNPC::GLNPC(void)
{
	this->currentState = NPCMOVE;
	transform->SetPos(glm::vec3(RNG::range(-20, 20), RNG::range(-2, 2), RNG::range(-20, 20)));

	this->TimeUntilChange = RNG::range(0.2, 3.0f);
	this->scaleChange = RNG::range(-0.02f, 0.02f);
	this->forwardSpeed = RNG::range(0.0f, 3.3f);
	this->rotationChange = glm::vec3(0, RNG::range(-1.0f,1.0f), 0);
	
	
}

GLNPC::GLNPC(FishBox& FSH_Loader, char* filePath) : GLModel(FSH_Loader, filePath)
{
	this->currentState = NPCMOVE;
	transform->SetPos(glm::vec3(RNG::range(-20, 20), RNG::range(-2, 2), RNG::range(-20, 20)));

	this->TimeUntilChange = RNG::range(0.2, 3.0f);
	this->scaleChange = RNG::range(-0.02f, 0.02f);
	this->forwardSpeed = RNG::range(0.0f, 3.3f);
	this->rotationChange = glm::vec3(0, RNG::range(-1.0f, 1.0f), 0);


}


void GLNPC::NPCUpdate(float deltaTime)
{
	TimeUntilChange -= deltaTime;
	if (TimeUntilChange < 0)
	{
		this->TimeUntilChange = RNG::range(0.2, 3.0f);
		this->forwardSpeed = RNG::range(0.5f,6.3f);
		this->rotationChange = glm::vec3(RNG::range(-0.1f,0.1f), RNG::range(-1.0f, 1.0f), 0);
	}


	if (currentState == NPCMOVE)
	{
		this->transform->m_pos += this->GetForward() * forwardSpeed * deltaTime;
		this->transform->m_rot += rotationChange * deltaTime;
	}
	else if (currentState == FLEEING)
	{
		this->transform->m_pos += this->GetForward() * 12.0f * deltaTime;
		this->transform->m_rot += rotationChange * deltaTime;

		fleeingTimer -= deltaTime;
		if (fleeingTimer < 0)
		{
			currentState = NPCMOVE;
		}


	}
	else if (currentState == BEINGEATEN)
	{
		;
	}

	//temp
	glm::vec3 pos = transform->GetPos();
	if (pos.x < - this->DEADZONEX)
	{
		pos.x = -DEADZONEX;
	}
	else if(pos.x >this->DEADZONEX)
	{
		pos.x = DEADZONEX;
	}

	if (pos.y < - this->DEADZONEY)
	{
		pos.y = -DEADZONEY;
	}
	else if (pos.y >this->DEADZONEY)
	{
		pos.y = DEADZONEY;
	}

	if (pos.z < - this->DEADZONEZ)
	{
		pos.z = -DEADZONEZ;
	}
	else if (pos.y >this->DEADZONEZ)
	{
		pos.z = DEADZONEZ;
	}

	transform->SetPos(pos);
}

void GLNPC::NPCDraw(GLShader & shader)
{
	this->Draw(shader);
}

void GLNPC::gettingEaten(float deltaTime)
{
	glm::vec3 reduce = this->transform->GetScale() - deltaTime;
	this->transform->SetScale(reduce);
	this->currentState = BEINGEATEN;
	
	
}

void GLNPC::initiateFleeingState(glm::vec3 playerForwardVector)
{
	if (this->currentState != BEINGEATEN)
	{
		this->currentState = FLEEING;
	//this->transform->SetRot(playerForwardVector);
	fleeingTimer = 4;
	}
}
