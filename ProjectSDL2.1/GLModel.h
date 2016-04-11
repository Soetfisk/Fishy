#pragma once

#include "GLMesh.h"
#include "GLShader.h"

class GLModel
{
public:
	GLModel();
	~GLModel();

	void Draw(GLShader& shader);
	void Update(float& dt);

	GLTransform& GetTransform();
private:
	std::vector<GLMesh*> meshes;
	GLTransform* transform;

	float test;
};

