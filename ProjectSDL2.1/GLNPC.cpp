#include "GLNPC.h"


GLNPC::GLNPC(void)
{
	transform->SetPos(glm::vec3(RNG::range(-20,20), RNG::range(-2,2), RNG::range(-20,20)));
}

void GLNPC::update()
{
	;//Pass
}

void GLNPC::NPCDraw(GLShader & shader)
{
	this->Draw(shader);
}
