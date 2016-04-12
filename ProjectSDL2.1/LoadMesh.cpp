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

GLMesh::Material ModelDataConvert::convertFSHMaterial(FSHMaterial originalMaterial)
{

	GLMesh::Material temp;

	temp.ambient = glm::vec3(
		originalMaterial.getAmbient()[0],
		originalMaterial.getAmbient()[1],
		originalMaterial.getAmbient()[2]);


	temp.diffuse = glm::vec3(
		originalMaterial.getDiffuse()[0],
		originalMaterial.getDiffuse()[1],
		originalMaterial.getDiffuse()[2]);

	temp.specular = glm::vec3(
		originalMaterial.getSpecular()[0],
		originalMaterial.getSpecular()[1],
		originalMaterial.getSpecular()[2]);

	temp.shininess = originalMaterial.getShinyness();



	return temp;
}



