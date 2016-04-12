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
//#include "GLUtil.h"


class FISHBOX_API FSHMaterial
{
private: //variables
	std::string materialName = "MaterialName";
	std::string textureFilePath;
	std::string normalFilePAth;
	float ambient[3];
	float diffuse[3];
	float specular[3];
	float shinyValue;
public: //functions
	FSHMaterial(void);
	std::string getMaterialName();
	std::string getTextureFilePath();
	float* getAmbient();
	float* getDiffuse();
	float* getSpecular();
	float getShinyness();
};



struct FSHVertexData
{
	float pos[3];
	float normal[3];
	float uv[2];
};



class FISHBOX_API FSHMesh {
private: //structs
	

private: //variables 
	std::string materialName;
	std::vector<FSHVertexData> vertexVector;
	unsigned int* indices = nullptr;
	unsigned int vertexCount;
	unsigned int indexCount;

private: //functions
	void loadVertexData();
	void loadIndices();

public: //functiuons
	FSHMesh(void);
	~FSHMesh(void);
	unsigned int getVertexCount();
	std::vector<FSHVertexData>& GetVertices();
	unsigned int getIndexCount();
	//getUVs();
	//getMaterial();
	//getTexture();
};








class FISHBOX_API FSHModel
{
private:
	std::vector <FSHMesh> MeshList;
	std::vector<FSHMaterial> MaterialList;
private:
	void LoadMeshes();
	void LoadMaterials();
public:
	FSHModel(void);
	 unsigned int GetMeshCount();
	std::vector<FSHMesh>& GetMeshList();
	std::vector<FSHMaterial>& GetMaterialList();
	void Release();
};








class FISHBOX_API FishBox {

private: //varaibles
	std::vector<FSHModel> ModelList;
public: //variables
	FishBox(void);
	void Test();
	void LoadModel(/*std::string FilePath*/);

public: //functions 
	std::vector<FSHModel>& GetModelList();

};






//extern FISHBOX_API int nFishBox;
//
//FISHBOX_API int fnFishBox(void);
