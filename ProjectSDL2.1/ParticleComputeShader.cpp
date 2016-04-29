#include "ParticleComputeShader.h"



ParticleComputeShader::ParticleComputeShader()
{
}


ParticleComputeShader::~ParticleComputeShader()
{
}

void ParticleComputeShader::Initialize(EmitterType type, int nrMaxParticles, ParticleRenderingUpdateData data) {

	//glGenBuffers(1, &this->transSSbo);
	//glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->transSSbo);
	//glBufferData(GL_SHADER_STORAGE_BUFFER, nrMaxParticles * sizeof(posParticleStruct), NULL, GL_STATIC_DRAW);

	//GLint bufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;

	//velsTest = (struct posParticleStruct*) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, nrMaxParticles * sizeof(posParticleStruct), bufMask);

	//

	//glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

	//glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, this->transSSbo);



	//glGenBuffers(1, &this->transSSbo);
	//glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->transSSbo);
	//glBufferData(GL_SHADER_STORAGE_BUFFER, nrMaxParticles * sizeof(struct ParticleComputeStruct), NULL, GL_STATIC_DRAW);

	//GLint bufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;

	//particleData = (struct ParticleComputeStruct*) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, nrMaxParticles * sizeof(struct ParticleComputeStruct), bufMask);

	//for (int i = 0; i < nrMaxParticles; i++) {
	//	this->particleData[i].position = glm::vec4(0);
	//	this->particleData[i].velocity = glm::vec4(0);
	//	this->particleData[i].transformMatrix = glm::mat4(0);
	//}

	////for (int i = 0; i < nrMaxParticles; i++) {
	////	this->particleData[i].position = data.position[i];// p_pos[i];
	////	this->particleData[i].velocity = data.velocity[i];
	////	this->particleData[i].transformMatrix = data.transformMatrix[i];
	////}


	//glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

	//glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, this->transSSbo);

	glGenBuffers(1, &this->transSSbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->transSSbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, nrMaxParticles * sizeof(ParticleTestPos), NULL, GL_STATIC_DRAW);

	GLint bufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;

	ParticleTestPos1 = (struct ParticleTestPos*) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, nrMaxParticles * sizeof(ParticleTestPos), bufMask);

	for (int i = 0; i < 2; i++) {
		ParticleTestPos1[i].x = 0;
		ParticleTestPos1[i].y = 0;
		ParticleTestPos1[i].z = 0;
		ParticleTestPos1[i].w = 1;
	}

	//for (int i = 0; i < nrMaxParticles; i++) {
	//	this->particleData[i].position = data.position[i];// p_pos[i];
	//	this->particleData[i].velocity = data.velocity[i];
	//	this->particleData[i].transformMatrix = data.transformMatrix[i];
	//}


	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, this->transSSbo);


	compute_program = glCreateProgram();

	compute_shader = CreateShader(LoadShader("ParticleProjectileComputeShader.glsl"), GL_COMPUTE_SHADER);
	
	glCompileShader(compute_shader);

	int rvalue;

	glGetShaderiv(compute_shader, GL_COMPILE_STATUS, &rvalue);

	glAttachShader(compute_program, compute_shader);

	glLinkProgram(compute_program);

	CheckShaderError(compute_program, GL_LINK_STATUS, true);



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

void ParticleComputeShader::Update(const float & deltaTime, int nrActiveParticles, ParticleRenderingUpdateData&data) {
	glUseProgram(this->compute_program);
	glDispatchCompute(nrActiveParticles, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

	std::cout << ParticleTestPos1[0].x << std::endl;

	//for (int i = 0; i < nrActiveParticles; i++) {
	//	if (particleData[i].position.x > 1) {
	//		int k = 0;
	//	}
	//}

	//for (int i = 0; i < nrActiveParticles; i++) {
	//	data.position[i] = particleData[i].position;
	//	data.velocity[i] = particleData[i].velocity;
	//	data.transformMatrix[i] = particleData[i].transformMatrix;
	//}

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
