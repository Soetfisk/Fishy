#pragma once
#include "GLModel.h" 
#include "RNG.h"

class SpecialStaticMesh : public GLModel
{
public:
	SpecialStaticMesh(FishBox* FSH_Loader, unsigned int modelID);
	virtual ~SpecialStaticMesh() {};
	int hello = 5;
	virtual void reset()=0;
};