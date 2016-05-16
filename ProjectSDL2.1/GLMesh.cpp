#include "GLMesh.h"

GLMesh::GLMesh(FSHData::mesh * meshData, FSHData::vertexData * vertices, unsigned int * indices, FSHData::material* material, GLuint textureID)
{
	this->m_drawCount = meshData->indexCount;
	this->material = material;
	this->texture = texture;
	this->m_transfrom = GLTransform();
	this->textureID = textureID;


	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	glBufferData(GL_ARRAY_BUFFER, meshData->vertexCount * sizeof(vertexData), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertexData), reinterpret_cast<void*>(offsetof(vertexData, pos)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertexData), reinterpret_cast<void*>(offsetof(vertexData, normal)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertexData), reinterpret_cast<void*>(offsetof(vertexData, uv)));

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshData->indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);

}

GLMesh::GLMesh(FSHData::mesh * meshData, FSHData::vertexData * vertices, unsigned int * indices, FSHData::material* material, FSHData::texture * texture)
{
	this->m_drawCount = meshData->indexCount;
	this->material = material;
	this->texture = texture;
	this->m_transfrom = GLTransform();


	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	glBufferData(GL_ARRAY_BUFFER, meshData->vertexCount * sizeof(vertexData), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertexData), reinterpret_cast<void*>(offsetof(vertexData, pos)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertexData), reinterpret_cast<void*>(offsetof(vertexData, normal)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertexData), reinterpret_cast<void*>(offsetof(vertexData, uv)));

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshData->indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->textureData);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


}

GLMesh::~GLMesh()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
	//delete m_material.texture;
}

bool GLMesh::Draw(GLShader& shader, GLTransform& modelTrans)
{
	trans =  modelTrans.GetModel() * m_transfrom.GetModel();
	glUniformMatrix4fv(shader.GetUnifromLocation("TransformMatrix"), 1, GL_FALSE, glm::value_ptr(trans));

	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);


	glBindVertexArray(m_vertexArrayObject);

	glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	return true;
}

GLTransform& GLMesh::GetTransform()
{
	return this->m_transfrom;
}

