#ifndef FILTER_COMPUTE_SHADER_H
#define FILTER_COMPUTE_SHADER_H
#include "GLUtil.h"
class FilterComputeShader
{
private:
	GLuint program;

public:
	FilterComputeShader(std::string fileName);
	~FilterComputeShader();
	std::string LoadShader(const std::string& fileName);
	GLuint CreateShader(const std::string& text, GLenum shaderType);
};
#endif
