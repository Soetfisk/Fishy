#pragma once
#include "GLModel.h"
#include "RNG.h"


class SeaWeedLeafs : public GLModel
{

private:
	std::vector<GLModel*> Leafs;
	FishBox* FSH_Loader;
	unsigned int modelID;
	float scaleMin, scaleMax;
	int leafsAmount;
	float posX, posY, posZ;
	float offsetX, offsetZ;
	float GetRandOffsetX();
	float getRandOffsetZ();

public:
	SeaWeedLeafs(FishBox* FSH_Loader, unsigned int modelID, float posX, float posY, float posZ, int leafs);
	virtual ~SeaWeedLeafs();
	void Draw(GLShader& shader);
	void LoadMesh();
	void reset();
	void SetScale(float min, float max);
	void SetOffset(int x, int y);
	void Reset();
	std::vector<GLModel*>& GetModels();

};