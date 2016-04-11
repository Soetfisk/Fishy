#include "LoadMesh.h"


std::vector<Vertex> ModelDataConvert::convertFSHVertex(std::vector<FSHVertexData> FSHVector)
{
	std::vector<Vertex> returnVector;

	for (int i = 0; i < FSHVector.size(); i++)
	{
		Vertex temp(
			FSHVector[i].pos[0],
			FSHVector[i].pos[1],
			FSHVector[i].pos[2],
			FSHVector[i].uv[0],
			FSHVector[i].uv[1],
			FSHVector[i].normal[0],
			FSHVector[i].normal[1],
			FSHVector[i].normal[2]
			);
		returnVector.push_back(temp);

	}


	return returnVector;
}



