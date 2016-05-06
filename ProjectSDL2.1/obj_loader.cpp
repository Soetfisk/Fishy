#include "obj_loader.h"

GLMesh *objLoadFromFile(const std::string& fileName) {
	FILE * file = fopen(fileName.c_str(), "r");

	if (file == NULL)
	{
		return nullptr;
	}

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;
	GLMesh::Material	   temp_material;

	unsigned int numFaces = 0;

	while (true) {
		char lineHeader[128];

		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break;

		if (strcmp(lineHeader, "v") == 0)
		{
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return nullptr;

			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);

			numFaces += 3;
		}

	}
	fclose(file);
	//fcloseall();
	std::vector<Vertex> final_vertices;
	std::vector<unsigned int> indices;
	int final_Index = 0;
	for (unsigned int i = 0; i < numFaces; i++)
	{
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		glm::vec3 normal = temp_normals[normalIndex - 1];

		int index = -1;

		for (size_t j = 0; j < final_vertices.size(); j++)
		{
			if (final_vertices[j].Pos() == vertex && final_vertices[j].Normal() == normal
				&& final_vertices[j].TexCoord() == uv)
			{
				index = j;
				break;
			}
		}
		if (index != -1)
		{
			indices.push_back(index);
		}
		else
		{
			Vertex outVertex(vertex, uv, normal);
			final_vertices.push_back(outVertex);
			indices.push_back(final_Index++);
		}
	}

	return new GLMesh(final_vertices, final_vertices.size(), indices, indices.size(), temp_material);
}