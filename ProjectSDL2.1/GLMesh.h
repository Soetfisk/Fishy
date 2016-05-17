#pragma once

#include "GLUtil.h"
#include "GLTransform.h"
#include "GLtexture.h"
#include "GLShader.h"

class GLMesh
{
public:
	struct Material
	{
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float shininess;
		GLTexture* texture;
	};

	GLMesh(FSHData::mesh * meshData, FSHData::vertexData * vertices, unsigned int * indices, FSHData::material* material, GLuint textureID);
	GLMesh(FSHData::mesh * meshData, FSHData::vertexData * vertices, unsigned int * indices, FSHData::material* material, FSHData::texture * texture);
	GLMesh() {};
	~GLMesh();

	bool Draw(GLShader& shader, GLTransform& modelTrans);
	GLTransform& GetTransform();
	FSHData::material* GetMaterial() {	return material;}
	void SetMaterial(FSHData::material* NewMaterial) { material = NewMaterial; }
	FSHData::texture* GetTexture() { return texture; }
protected:

	GLuint m_vertexArrayObject;
	GLuint vertexBuffer;
	GLuint indexBuffer;
	GLuint textureID;

	GLTransform m_transfrom;
	unsigned int m_drawCount;

	FSHData::mesh meshData;
	FSHData::vertexData * vertices;
	FSHData::material * material;
	//FSHData::material * 
	Material m_material;
	FSHData::texture * texture;
	glm::mat4 trans;
	glm::mat4 test;
};

