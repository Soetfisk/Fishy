#pragma once
#include "GLUtil.h"
#include "GLCamera.h"
#include "GLMesh.h"
#include <glm\gtc\type_ptr.hpp>
class GLShader
{
public:
	GLShader(const std::string& fileName, const bool& geometry);
	GLShader() {};

	void Bind();
	void Update(GLMesh& mesh, const GLCamera& camera);
	void Update(GLTransform& tranform, const GLCamera& camera);
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
	GLuint m_program;
	GLuint* m_shaders; 
	GLuint m_uniforms[NUM_UNIFORMS];

	GLuint CreateShader(const std::string& text, GLenum shaderType);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram);
	std::string LoadShader(const std::string& fileName);
};
