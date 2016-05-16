#pragma once
#include "GLMesh.h" 


class GLMeshBS : public GLMesh
{
public:
	GLMeshBS
		(
		FSHData::mesh * meshData,
		FSHData::vertexData * vertices,
		unsigned int * indices,
		FSHData::material* material,
		FSHData::texture * texture, 
		FSHData::blendShape ** blendShapes
		);
	GLMeshBS
		(
			FSHData::mesh * meshData,
			FSHData::vertexData * vertices,
			unsigned int * indices,
			FSHData::material* material,
			GLuint textureID,
			FSHData::blendShape ** blendShapes
			);
private:
	enum
	{
		Vertex_Data,
		blendShape0_Data,
		blendShape1_Data,
		blendShape2_Data,
		blendShape3_Data,
		blendShape4_Data,
		blendShape5_Data,
		blendShape6_Data,
		NO_OF_VBO
	};

	unsigned int blendShapeCount;
	GLuint vertexBuffer[NO_OF_VBO];
};