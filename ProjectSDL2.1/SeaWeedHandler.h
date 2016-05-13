#pragma once
#include "SeaWeedLeafs.h"
class SeaWeedHandler
{
public:
	enum Animations
	{
		SWONE,
		SWTWO,

		SW_NUM_ANIMATION
	};

private:
	std::vector<SeaWeedLeafs*> specialStaticMeshes;
	int amountOfPlants, modelID;
	float  limitPosX, limitPosZ, PosY, leafsMin, leafsMax, scaleMin, scaleMax;
	float randomRot = 0.8f;
	int xMin, xMax, zMin, zMax;
	int offsetX, offsetZ;
	FishBox* FSH_Loader;

	bool isBlendShape = false;
	float * blendWeights;
	float animationFactors[SW_NUM_ANIMATION];

	



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
	
	void SetRandomRotation(float radian);
	//blendshape
	void SetIsBlendShape(bool TF) { this->isBlendShape = TF; };
	bool GetIsBlendShape(bool TF) { return this->isBlendShape; };
	float * GetBlendWeights() { return blendWeights; }
	unsigned int GetBlendShapeCount() { return SW_NUM_ANIMATION; }
	void moveAnimation(float deltaTime, float speedFactor);
	void Update(float deltaTime);
};

