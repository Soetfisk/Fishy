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
	;
}

