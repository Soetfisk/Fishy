#include "GLNPC.h"


GLNPC::GLNPC()
{
	RNG::range(-1.0f, 1.0f);
	
	this->transform->SetPos(glm::vec3(RNG::range(-20,20), RNG::range(-4, 4), RNG::range(-20, 20)));
	
}

void GLNPC::update()
{
	;//Pass
}

void GLNPC::NPCDraw(GLShader & shader)
{
	this->Draw(shader);
}


