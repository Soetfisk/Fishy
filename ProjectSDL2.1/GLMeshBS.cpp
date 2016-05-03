#include "GLMeshBS.h"

GLMeshBS::GLMeshBS
(
	FSHData::mesh * meshData, 
	FSHData::vertexData * vertices, 
	unsigned int * indices, 
	FSHData::material * material, 
	FSHData::texture * texture, 
	FSHData::blendShape * blendShapes
)
{
	this->m_drawCount = meshData->indexCount;
	this->material = material;
	this->texture = texture;
	this->blendShapeCount = meshData->blendshapesCount;
	this->m_transfrom = GLTransform();

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

	//glEnableVertexAttribArray(3);
	//glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[blendShape_Data]);
	
	//glVertexAttribPointer(3, 3 * blendShapeCount, GL_FLOAT, GL_FALSE, sizeof(blendShape) * blendShapeCount, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[blendShape_Data]);
	glBufferData(GL_ARRAY_BUFFER, meshData->vertexCount * sizeof(blendShape) * blendShapeCount, blendShapes, GL_STATIC_DRAW);
	
	int m_location = 3;
	for (unsigned int i = 0; i < 10; i++)
	{
		GLuint index = m_location + i;
		GLsizei stride = sizeof(blendShape)/**10*/;
		GLsizei offset = sizeof(blendShape)*i;

		glEnableVertexAttribArray(index);
		
		glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(offset));

		glVertexAttribDivisor(index, 0);
	}

	int n;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &n);
	//glGenBuffers(1, &pe_transBuf);
	//glBindBuffer(GL_ARRAY_BUFFER, pe_transBuf);
	//int m_location = 1;
	//for (unsigned int i = 0; i < 4; i++) {
	//	GLuint index = m_location + i;
	//	GLsizei stride = sizeof(glm::mat4);
	//	GLsizei offset = (sizeof(GLfloat)*i * 4);

	//	glEnableVertexAttribArray(index);

	//	glVertexAttribPointer(index,
	//		4, GL_FLOAT, GL_FALSE,
	//		stride,
	//		(const GLvoid*)offset);

	//	//glVertexAttribDivisor(index, 0);
	//}



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
