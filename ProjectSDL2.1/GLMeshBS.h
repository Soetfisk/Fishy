#pragma once
#include "GLMesh.h" 


class GLMeshBS : public GLMesh
{
public:
	GLMeshBS(FSHData::mesh * meshData, FSHData::vertexData * vertices, unsigned int * indices, FSHData::material* material, FSHData::texture * texture, FSHData::blendShape * blendShapes, unsigned int blendShapeCount);

private:
	enum
	{
		Vertex_Data,
		blendShape_Data,

		NO_OF_VBO
	};

	unsigned int blendShapeCount;
	GLuint * vertexBuffer;
};