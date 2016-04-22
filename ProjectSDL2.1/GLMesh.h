#pragma once

#include "GLUtil.h"
#include "GLTransform.h"
#include "GLtexture.h"
#include "GLShader.h"

class Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal)
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}
	Vertex(float x, float y, float z, float u, float v, float nx, float ny, float nz)
	{
		this->pos = glm::vec3(x, y, z);
		this->texCoord = glm::vec2(u, v);
		this->normal = glm::vec3(nx, ny, nz);
	}
	glm::vec3& Pos() { return this->pos; }
	glm::vec2& TexCoord() { return this->texCoord; }
	glm::vec3& Normal() { return this->normal; }
private:
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec2 texCoord;
};
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


	GLMesh(std::vector<Vertex> vertices, unsigned int numVertices, std::vector<unsigned int> indices, unsigned int numIndices, Material material);
	GLMesh(FSHData::mesh * meshData, FSHData::vertexData * vertices, unsigned int * indices, FSHData::material* material, char * texture);
	GLMesh() {};
	~GLMesh();

	bool Draw(GLShader& shader, GLTransform& modelTrans);
	GLTransform& GetTransform();
	FSHData::material* GetMaterial() {	return material;}
	char * GetTexture() { return texture; }
private:
	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,

		INDEX_VB,

		NUM_BUFFERS
	};

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];

	GLTransform m_transfrom;
	unsigned int m_drawCount;
	unsigned int * indexies;
	FSHData::mesh meshData;
	FSHData::vertexData * vertices;
	FSHData::material * material;
	//FSHData::material * 
	Material m_material;
	char * texture;

	//TEST
	std::vector<unsigned int> objindex;
	std::vector<unsigned int> getobjindex() { return objindex; };

	std::vector<Vertex> objvertices;
	std::vector<Vertex> getobjvertices() { return objvertices; };

	GLuint vertexBuffer;
	GLuint indexBuffer;
};

