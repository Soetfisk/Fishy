#include "ParticleComputeShader.h"



ParticleComputeShader::ParticleComputeShader()
{
}


ParticleComputeShader::~ParticleComputeShader()
{
}

void ParticleComputeShader::Initialize(EmitterType type, int nrMaxParticles, glm::mat4*& pTransformMatrices, glm::vec4* pVelocitiesS, glm::vec4*& pos) {
	
	//glGenBuffers(1, &this->transSSbo);
	//glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->transSSbo);
	//glBufferData(GL_SHADER_STORAGE_BUFFER, nrMaxParticles * sizeof(posParticleStruct), NULL, GL_STATIC_DRAW);

	//GLint bufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;

	//velsTest = (struct posParticleStruct*) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, nrMaxParticles * sizeof(posParticleStruct), bufMask);

	//

	//glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

	//glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, this->transSSbo);



	glGenBuffers(1, &this->transSSbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->transSSbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, nrMaxParticles * sizeof(ParticleComputeStruct), NULL, GL_STATIC_DRAW);

	GLint bufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;

	particleData = (struct ParticleComputeStruct*) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, nrMaxParticles * sizeof(ParticleComputeStruct), bufMask);



	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, this->transSSbo);


	compute_program = glCreateProgram();

	compute_shader = CreateShader(LoadShader("ParticleProjectileComputeShader.glsl"), GL_COMPUTE_SHADER);

	glCompileShader(compute_shader);

	int rvalue;

	glGetShaderiv(compute_shader, GL_COMPILE_STATUS, &rvalue);

	glAttachShader(compute_program, compute_shader);

	glLinkProgram(compute_program);

	CheckShaderError(compute_program, GL_LINK_STATUS, true);




	glUseProgram(this->compute_program);
	glDispatchCompute(2, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
	

	switch (type)
	{
	case PROJECTILE:
		InitializeProjectileShader();
		break;
	case PLAYERFOLLOW:
		break;
	case STATICSTREAM:
		break;
	case EMITERTYPENR:
		break;
	default:
		break;
	}
}

void ParticleComputeShader::Update(const float & deltaTime, int nrActiveParticles) {
	glUseProgram(this->compute_program);
	glDispatchCompute(nrActiveParticles, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

	for (int i = 0; i < 2; i++) {
		 if (particleData[i].position.x != 0) {
			 int k = 0;
		 }
	}

	

}

void ParticleComputeShader::InitializeProjectileShader() {

}


GLuint ParticleComputeShader::CreateShader(const std::string & text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
	{
		OutputDebugStringA((char*)"Error: Shader creation failed!");
	}

	const char* shaderTextPtr = text.c_str();

	glShaderSource(shader, 1, &shaderTextPtr, nullptr);
	glCompileShader(shader);
	CheckShaderError(shader, GL_COMPILE_STATUS, false);

	return shader;
}

/*

*/
void ParticleComputeShader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram)
{
	GLint success = 0;

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
		{
			GLint msgLength = 0;
			glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &msgLength);
			GLchar* msg = new GLchar[msgLength];
			glGetProgramInfoLog(shader, msgLength, NULL, msg);

			OutputDebugStringA((char*)msg);
			glDeleteProgram(shader);
			delete[] msg;
		}
		else {
			GLint msgLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &msgLength);
			GLchar* msg = new GLchar[msgLength];
			glGetShaderInfoLog(shader, msgLength, NULL, msg);

			OutputDebugStringA((char*)msg);
			glDeleteShader(shader);
			delete[] msg;
		}
	}
}

/*
Read and load shaderfile into a string and return it
*/
std::string ParticleComputeShader::LoadShader(const std::string & fileName)
{
	std::ifstream shaderFile;
	shaderFile.open((fileName).c_str());

	std::string shaderText((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());
	shaderFile.close();

	return shaderText;
}
