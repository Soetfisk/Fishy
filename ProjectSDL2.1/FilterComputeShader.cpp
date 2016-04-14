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

void FilterComputeShader::CreateShader(const std::string & text, GLenum shaderType)
{
	// Creating the compute shader, and the program object containing the shader
	this->program = glCreateProgram();
	this->shader = glCreateShader(GL_COMPUTE_SHADER);
	const char* shaderTextPtr = text.c_str();

	glShaderSource(this->shader, 2, &shaderTextPtr, NULL);
	glCompileShader(this->shader);

	int rvalue;
	glGetShaderiv(this->shader, GL_COMPILE_STATUS, &rvalue);
	if (!rvalue) {
		fprintf(stderr, "Error in compiling the compute shader\n");
		GLchar log[10240];
		GLsizei length;
		glGetShaderInfoLog(this->shader, 10239, &length, log);
		fprintf(stderr, "Compiler log:\n%s\n", log);
		exit(40);
	}
	glAttachShader(this->program, this->shader);

	glLinkProgram(this->program);
	glGetProgramiv(this->program, GL_LINK_STATUS, &rvalue);
	if (!rvalue) {
		fprintf(stderr, "Error in linking compute shader program\n");
		GLchar log[10240];
		GLsizei length;
		glGetProgramInfoLog(this->program, 10239, &length, log);
		fprintf(stderr, "Linker log:\n%s\n", log);
		exit(41);
	}
	glUseProgram(this->program);

	//glUniform1i(glGetUniformLocation(progHandle, "destTex"), 0);
}

void FilterComputeShader::BindShader()
{
	glUseProgram(this->program);
}

void FilterComputeShader::dispatchCompute(int width, int height, int depth)
{
	glDispatchCompute(width, height, depth);
}

GLint FilterComputeShader::getUniformLocation(std::string name)
{
	return glGetUniformLocation(this->program, name.c_str());
}
