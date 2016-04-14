#include "GLMesh.h"

GLMesh::GLMesh(std::vector<Vertex> vertices, unsigned int numVertices, std::vector<unsigned int> indices, unsigned int numIndices, Material material)
{
	this->m_drawCount = numIndices;

	this->m_transfrom = GLTransform();

	this->m_material = material;

	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;

	

	positions.reserve(numVertices);
	texCoords.reserve(numVertices);
	normals.reserve(numVertices);

	for (unsigned int i = 0; i < numVertices; i++)
	{
		positions.push_back(vertices[i].Pos());
		texCoords.push_back(vertices[i].TexCoord());
		normals.push_back(vertices[i].Normal());
	}



	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);


	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(normals[0]), &normals[0], GL_STATIC_DRAW);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

GLMesh::GLMesh(FSHData::mesh * meshData, FSHData::vertexData * vertices, unsigned int * indices)
{
	this->m_drawCount = meshData->indexCount;

	this->indexies = indices;

	this->m_transfrom = GLTransform();

	//glGenBuffers(1, &vertexBuffer);
	//glGenBuffers(1, &indexBuffer);

	//
	//glGenVertexArrays(1, &m_vertexArrayObject);
	//glBindVertexArray(m_vertexArrayObject);
	//
	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	//glEnableVertexAttribArray(2);



	//glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	//glBufferData(GL_ARRAY_BUFFER, meshData->vertexCount * sizeof(float) * 3, vertices, GL_STATIC_DRAW);


	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
	//glBufferData(GL_ARRAY_BUFFER, meshData->vertexCount * sizeof(float) * 2, vertices, GL_STATIC_DRAW);


	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 3, 0);

	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
	//glBufferData(GL_ARRAY_BUFFER, meshData->vertexCount * sizeof(float) * 3, vertices, GL_STATIC_DRAW);

	//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshData->indexCount * sizeof(indices[0]), indices, GL_STATIC_DRAW);

	/*glBindVertexArray(0);*/

	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);



	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, meshData->vertexCount * sizeof(float[3]), vertices->pos, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertexData), (void*)offsetof(FSHData::vertexData, pos));

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, meshData->vertexCount * sizeof(float[3]), vertices->normal, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertexData), (void*)offsetof(FSHData::vertexData, normal));

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, meshData->vertexCount * sizeof(float[2]), vertices->uv, GL_STATIC_DRAW);


	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertexData), (void*)offsetof(FSHData::vertexData, uv));



	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshData->indexCount * sizeof(indices[0]), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);

}

GLMesh::~GLMesh()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
	//delete m_material.texture;
}

bool GLMesh::Draw(GLShader& shader, GLTransform& modelTrans)
{
	glm::mat4 trans =  modelTrans.GetModel() * m_transfrom.GetModel();
	glUniformMatrix4fv(shader.GetUnifromLocation("TransformMatrix"), 1, GL_FALSE, glm::value_ptr(trans));

	glBindVertexArray(m_vertexArrayObject);

	glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	return true;
}

GLTransform& GLMesh::GetTransform()
{
	return this->m_transfrom;
}

