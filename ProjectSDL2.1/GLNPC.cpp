#include "GLNPC.h"


GLNPC::GLNPC(void)
{
	transform->SetPos(glm::vec3(RNG::range(-4,4), RNG::range(-2,2), RNG::range(1,2)));
}

void GLNPC::update()
{
	;//Pass
}

void GLNPC::NPCDraw(GLShader & shader)
{
	this->Draw(shader);
}
