#include "FilterComputeShader.h"



FilterComputeShader::FilterComputeShader(std::string fileName)
{
}


FilterComputeShader::~FilterComputeShader()
{
}

std::string FilterComputeShader::LoadShader(const std::string & fileName)
{
	std::ifstream shaderFile;
	shaderFile.open((fileName).c_str());

	std::string shaderText((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());
	shaderFile.close();

	return shaderText;
}

GLuint FilterComputeShader::CreateShader(const std::string & text, GLenum shaderType)
{
	return GLuint();
}
