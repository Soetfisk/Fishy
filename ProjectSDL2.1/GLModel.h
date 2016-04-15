#pragma once

#include "GLMesh.h"
#include "GLShader.h"

class GLModel
{
public:
	GLModel();
	GLModel(std::string& filePath);
	~GLModel();

	virtual void Draw(GLShader& shader);
	virtual void Update(float& dt);

	GLTransform& GetTransform();
	glm::vec3 GetForward();
protected:
	std::vector<GLMesh*> meshes;
	GLTransform* transform;

};

