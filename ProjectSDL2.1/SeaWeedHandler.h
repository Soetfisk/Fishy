#pragma once
#include "SeaWeedLeafs.h"
class SeaWeedHandler
{
private:
	std::vector<SeaWeedLeafs*> specialStaticMeshes;
	int amountOfPlants, modelID;
	float  limitPosX, limitPosZ, PosY, leafsMin, leafsMax, scaleMin, scaleMax;
	int xMin, xMax, yMin, yMax;
	int offsetX, offsetZ;
	FishBox* FSH_Loader;


public:
	SeaWeedHandler(FishBox* FSH_Loader, unsigned int modelID);
	void LoadSeaWeed();
	virtual ~SeaWeedHandler();
	void Draw(GLShader* shader);
	void SetYLimit(int min, int max);
	void SetXLimit(int min, int max);
	void SetLeafAmount(int min, int max);
	void SetAmountOfPlants(int plants);
	void setScale(float min, float max);
	void setOffset(int x, int z);
};
