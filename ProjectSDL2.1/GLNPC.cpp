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

void GLNPC::NPCUpdate(float deltaTime)
{
	TimeUntilChange -= deltaTime;
	if (TimeUntilChange < 0)
	{
		this->TimeUntilChange = RNG::range(0.2, 3.0f);
		//this->scaleChange = RNG::range(-0.02f, 0.02f);
		this->forwardSpeed = RNG::range(0.0f,3.3f);
		this->rotationChange = glm::vec3(0, RNG::range(-1.0f, 1.0f), 0);
	}

	//transform->SetPos(glm::vec3(RNG::range(-20, 20), RNG::range(-2, 2), RNG::range(-20, 20)));

	if (currentState = NPCMOVE)
	{
		this->transform->m_pos += this->GetForward() * forwardSpeed * deltaTime;

		this->transform->m_scale += scaleChange * deltaTime;
		this->transform->m_rot += rotationChange * deltaTime;
	}
	
}

void GLNPC::NPCDraw(GLShader & shader)
{
	this->Draw(shader);
}
