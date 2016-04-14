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
};
#endif
