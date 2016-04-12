#pragma once
#include "GLMesh.h"
#include "FishBox.h"
#include <vector>


namespace ModelDataConvert
{
	std::vector<Vertex> convertFSHVertex(std::vector<FSHVertexData> FSHVector);
	GLMesh::Material convertFSHMaterial(FSHMaterial);
}

