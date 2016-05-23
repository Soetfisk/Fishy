#pragma once
#include "GLModel.h"
#include "RNG.h"
#include "GLFrustum.h"


class SeaWeedLeafs : public GLModel
{

private:
	std::vector<GLModel*> Leafs;
	FishBox* FSH_Loader;
	unsigned int modelID;
	AABB boundingBox;
	float scaleMin, scaleMax;
	int leafsAmount;
	float posX, posY, posZ;
	float offsetX, offsetZ;
	float GetRandOffsetX();
	float getRandOffsetZ();
	float rotation = 3.1f;

public:
	SeaWeedLeafs(FishBox* FSH_Loader, unsigned int modelID, float posX, float posY, float posZ, int leafs);
	virtual ~SeaWeedLeafs();
	void Draw(GLShader& shader);
	void Draw(GLShader& shader, GLFrustum& frustrum);
	void LoadMesh();
	void reset();
	void SetScale(float min, float max);
	void SetOffset(float x, float y);
	void SetBoundingBox(glm::vec3& center, glm::vec3& extents);
	void Reset();
	std::vector<GLModel*>& GetModels();
	void SetRotation(float X_Z);

};