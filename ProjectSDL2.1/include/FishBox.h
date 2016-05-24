// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the FISHBOX_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// FISHBOX_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef FISHBOX_EXPORTS
#define FISHBOX_API __declspec(dllexport)
#else
#define FISHBOX_API __declspec(dllimport)
#endif

#include <vector>
#include <iostream>
#include "stdio.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>

#include <Windows.h>

//Basic Util Includes
#include <iostream>
#include <vector>

//OpenGL Includes

#include <glm\glm.hpp>
#include <gl\GL.h>




//#include "GLUtil.h"
#include "SOIL.h"

namespace FSHData
{

	struct fileHeader
	{
		unsigned int meshCount;
		unsigned int materialCount;
		unsigned int directionalLightCount;
		unsigned int pointLightCount;
		unsigned int areaLightCount;
		unsigned int cameraCount;
	};
	struct mesh
	{
		char materialName[256];
		unsigned int vertexCount;
		unsigned int blendshapesCount;
		unsigned int indexCount;

	};
	struct vertexData
	{
		glm::vec3 pos;
		glm::vec3 normal;
		glm::vec2 uv;
	};
	struct index
	{
		unsigned int vertexIndex;
	};
	struct blendShape
	{
		glm::vec3 pos;
	};
	struct material
	{
		char materialName[256];
		char textureFilePath[256];
		char normalFilePath[256];

		float ambient[3];
		float diffuse[3];
		float spec[3];
		float shinyness;
	};
	struct directionalLight
	{
		float intensity;
		float lightColor;
		float direction[3];
	};
	struct pointLight
	{
		float intensity;
		float lightColor;
		float pos[3];
	};
	struct areaLight
	{
		float intensity;
		float lightColor;
		float pos[3];
		float direction[3];
		float scale[3];
	};
	struct camera
	{
		float pos[3];
		float rotation[3];
		float target[3];
		float upVec[3];
	};
	struct texture
	{
		int height;
		int width;
		unsigned char * textureData;
	};

}

using namespace FSHData;

class FISHBOX_API FSHMesh {

private: //variables 
	std::ifstream * infile;

	mesh meshHEADER;
	unsigned int* indices = nullptr;
	vertexData * vertices = nullptr;
	blendShape ** blendShapes = nullptr;

private: //functions
	void loadVertexData();
	void loadIndices();
	void loadBlendshapes();

public: //functiuons
	FSHMesh(void);
	FSHMesh(std::ifstream*& infile);
	~FSHMesh(void);

	mesh * GetMeshData();
	
	unsigned int * GetIndices();
	vertexData * GetVertices();
	unsigned int getVertexCount();
	unsigned int getIndexCount();
	blendShape ** GetBlendShapes();
	
	//getUVs();
	//getMaterial();
	//getTexture();
};





class FISHBOX_API FSHScene
{

private:
	fileHeader HEADER;
	std::ifstream * infile;
	std::vector<FSHMesh*> meshes;
	std::vector<material*> materials;
	std::vector<texture*> textures;
	std::vector<std::string> textureNames;
	std::vector<GLuint> textureIDs;

	std::vector<camera*> cameras;
	std::vector<directionalLight*> directionalLights;
	char*SCENE_ID;


private:

	void LoadMeshes();
	void LoadMaterials();
	void LoadCameras();
	void LoadDirectionalLights();
	FSHScene(void);
public:
	void setTextureIDs(std::vector<GLuint> textureIDs);
	void setTextureList(std::vector<texture*> textures, std::vector<std::string> textureNames);
	FSHScene(char * filePath);
	unsigned int GetMeshCount();
	unsigned int GetCameraCount();
	std::vector<FSHMesh*> GetMeshList();
	std::vector<material*> GetMaterialList();
	std::vector<std::string> GetTexureNameList();
	std::vector<GLuint> GetTextureIDs();
	std::vector<camera*> GetCameraList();
	void Release();
};








class FISHBOX_API FishBox {
private:


private: //varaibles
	std::vector<FSHScene> SceneList;
	std::vector<texture*> extraTextures;
	std::vector<texture*> textures;
	std::vector<std::string> textureNames;
	std::vector<GLuint> textureIDs;

	//functions
	void LoadTextures();


public: //variables


public: //functions 
	FishBox(void);
	FishBox::~FishBox();
	void clean();
	void freeTextures();

	void release();
	void Test();
	int GetModelCount();
	void LoadScene(char * filePath);

	//scene handling
	void MeshData(unsigned int model, unsigned int mesh, vertexData *&vertexData, unsigned int *&indexData);
	FSHData::mesh * MeshData(unsigned int model, unsigned int mesh);
	FSHData::vertexData * VertexData(unsigned int model, unsigned int mesh);
	unsigned int * IndexData(unsigned int model, unsigned int mesh);
	unsigned int ModelMeshCount(unsigned int model);
	FSHData::material * meshMaterial(unsigned int model, unsigned int mesh);
	GLuint meshTextureID(unsigned int model, unsigned int mesh);
	FSHData::blendShape** meshBlendShapes(unsigned int model, unsigned int mesh);

	FSHData::camera* CameraData(unsigned int model, unsigned int camera);
	void pikachufuck() {printf("pikachu"); };

	//extra functions
	texture * loadTexure(char* filepath);
};
#ifdef _DEBUG 
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 
#endif
#endif  // _DEBUG