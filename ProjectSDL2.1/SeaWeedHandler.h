#pragma once
#include "SeaWeedLeafs.h"
class SeaWeedHandler
{
private:
	std::vector<SeaWeedLeafs*> specialStaticMeshes;
	int amountOfPlants, modelID;
	float  limitPosX, limitPosZ, PosY, leafsMin, leafsMax, scaleMin, scaleMax;
	float randomRot = 0.8f;
	int xMin, xMax, zMin, zMax;
	int offsetX, offsetZ;
	FishBox* FSH_Loader;


public:
	SeaWeedHandler(FishBox* FSH_Loader, unsigned int modelID);
	void LoadSeaWeed();
	virtual ~SeaWeedHandler();
	void Draw(GLShader* shader);
	void SetZLimit(int min, int max);
	void SetXLimit(int min, int max);
	void SetLeafAmount(int min, int max);
	void SetAmountOfPlants(int plants);
	void SetScale(float min, float max);
	void SetOffset(int x, int z);
	void Reset();
	std::vector<GLModel*> GetMeshes();
	void SetRandomRotation(float radian);
};

