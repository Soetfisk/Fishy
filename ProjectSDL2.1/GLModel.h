#pragma once

#include "GLMesh.h"
#include "GLShader.h"

class GLModel
{
public:
	GLModel();
	GLModel(FishBox& FSH_Loader, char* filePath);
	~GLModel();

	virtual void Draw(GLShader& shader);
	virtual void Update(float& dt);

	GLTransform& GetTransform();
protected:
	std::vector<GLMesh*> meshes;
	GLTransform* transform;
	int modelID;

};

