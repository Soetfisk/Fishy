#include "GLNPC.h"

int GLNPC::GetCurrentState()
{
	return currentState;
}

void GLNPC::SetCurrentState()
{
	this->currentState = NPC_STANDSTILL;
}

GLNPC::GLNPC(FishBox * FSH_Loader, unsigned int modelID) : GLModel(FSH_Loader,modelID)
{
	this->blendWeights = new float[NUM_ANIMATION];
	for (int i = 0; i < NUM_ANIMATION; i++)
	{
		blendWeights[i] = 0.0f;
		animationFactors[i] = 0.0f;
	}
}

void GLNPC::moveAnimation(float deltaTime, float speedFactor)
{
	float speed = abs(deltaTime * speedFactor), y;

	animationFactors[AONE] += speed;

	y = sin(animationFactors[AONE]);

	if (y > 0.0)
		this->blendWeights[AONE] = y;
	if (y < 0.0)
		this->blendWeights[ATWO] = abs(y);

}
