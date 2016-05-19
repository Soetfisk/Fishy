#include "GLMeshBS.h"

GLMeshBS::GLMeshBS
(
	FSHData::mesh * meshData,
	FSHData::vertexData * vertices,
	unsigned int * indices,
	FSHData::material * material,
	GLuint textureID,
	FSHData::blendShape ** blendShapes
	)
{
	this->m_drawCount = meshData->indexCount;
	this->material = material;
	this->texture = texture;
	this->blendShapeCount = meshData->blendshapesCount;
	this->m_transfrom = GLTransform();
	this->textureID = textureID;

	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	glGenBuffers(NO_OF_VBO, vertexBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[Vertex_Data]);
	glBufferData(GL_ARRAY_BUFFER, meshData->vertexCount * sizeof(vertexData), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertexData), reinterpret_cast<void*>(offsetof(vertexData, pos)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertexData), reinterpret_cast<void*>(offsetof(vertexData, normal)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertexData), reinterpret_cast<void*>(offsetof(vertexData, uv)));


	int m_location = 3;
	for (unsigned int i = 0; i < meshData->blendshapesCount; i++)
	{
		GLuint index = m_location + i;

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[1 + i]);
		glBufferData(GL_ARRAY_BUFFER, meshData->vertexCount * sizeof(blendShape), blendShapes[i], GL_STATIC_DRAW);

		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, sizeof(blendShape), 0);
	}

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshData->indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);

}
