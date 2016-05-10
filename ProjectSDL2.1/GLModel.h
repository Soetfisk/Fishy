#pragma once

#include "GLMesh.h"
#include "GLMeshBS.h"
#include "GLShader.h"
#include "AABB.h"

class GLModel
{
public:
	GLModel();
	GLModel(FishBox* FSH_Loader, char* filePath);
	GLModel(FishBox* FSH_Loader, unsigned int modelID);
	~GLModel();

	virtual void Draw(GLShader& shader);
	virtual void Update(float& dt);

	GLTransform& GetTransform();
	glm::vec3 GetForward();
	glm::vec3 GetRight();
	glm::vec3 GetUp();

	AABB GetBoundingBox();
	void SetBoundingBox(glm::vec3 center, glm::vec3 extents);
protected:
	std::vector<GLMesh*> meshes;
	GLTransform* transform;
	int modelID;
	AABB boundingBox;
};

