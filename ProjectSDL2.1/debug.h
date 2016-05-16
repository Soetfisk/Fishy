#pragma once
#include "GLUtil.h"

class debugger
{
private:
	float currentDTime;
	float dTime;
	float prevDTime;
	float combinedDtime;

public:
	void debugger::setDebugTimer(bool debug)
	{
		if (debug)
		{
			this->currentDTime = SDL_GetTicks();
			this->dTime = (currentDTime - prevDTime) / 1000.0f;
			this->prevDTime = currentDTime;
			this->combinedDtime += dTime;
		}

	}



	void debugger::printDebugTimer(bool debug, std::string name)
	{
		if (debug)
			printf("\nTime: %f, %s", dTime, name.c_str());
	}

	void debugger::PrintAndResetCombinedDTimer(bool debug)
	{
		if (debug)
		{
			printf("\nCombinded frame time: %f\n", combinedDtime);
			combinedDtime = 0.0f;
		}
	}
};