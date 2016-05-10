#pragma once
#include "SpecialStaticMesh.h" 


class SeaWeedLeafs : public SpecialStaticMesh
{

private:
	std::vector<GLModel*> Leafs;
	FishBox* FSH_Loader;
	unsigned int modelID;

public:
	SeaWeedLeafs(FishBox* FSH_Loader, unsigned int modelID);
	~SeaWeedLeafs();
	void Draw(GLShader& shader);
	void reset();

};