#pragma once
#include "GLUtil.h"
#include "GLCamera.h"
//#include "GLMesh.h"
#include <glm\gtc\type_ptr.hpp>
class GLShader
{
public:
	GLShader(const std::string& fileName, const bool& geometry = false);
	GLShader() {};

	GLuint m_program;

	void Bind();
	void Update(GLCamera& camera);
	void Uniform1f(std::string name, float number);
	void UniformVec3(std::string name, glm::vec3 vector);
	void Uniform1i(std::string name, unsigned int number);
	/*void Update(GLMesh& mesh, GLCamera& camera);
	void Update(GLTransform& tranform, GLCamera& camera);*/
	GLuint& GetUnifromLocation(std::string name);

	virtual ~GLShader();
private:
	int nrOfShaders;

	enum
	{
		TRANSFROM_U,
		PROJVIEW_U,
		VIEWPOS_U,

		NUM_UNIFORMS
	};
	
	GLuint m_shaders[3]; 
	GLuint m_uniforms[NUM_UNIFORMS];

	GLuint CreateShader(const std::string& text, GLenum shaderType);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram);
	std::string LoadShader(const std::string& fileName);

};
