#include "ParticleComputeShader.h"



ParticleComputeShader::ParticleComputeShader()
{
}


ParticleComputeShader::~ParticleComputeShader()
{
	glDetachShader(compute_program, compute_shader);
	glDeleteShader(compute_shader);
	glDeleteProgram(compute_program);
}

void ParticleComputeShader::Initialize(EmitterType type, int nrMaxParticles, ParticleRenderingUpdateData data) {
	

	glGenBuffers(1, &transSSbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, transSSbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, transSSbo * sizeof(ParticleComputeStruct), NULL, GL_STATIC_DRAW);
	GLint bufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT; // the invalidate makes a big difference when re-writing
	particleData = (struct ParticleComputeStruct *) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, nrMaxParticles * sizeof(ParticleComputeStruct), bufMask);
	//for (int i = 0; i < nrMaxParticles; i++)
	//{
	//	particleData[i].position.x = data.position[i].x;
	//	particleData[i].position.y = data.position[i].y;
	//	particleData[i].position.z = data.position[i].z;
	//	particleData[i].position.w = data.position[i].z;
	//}
	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);


	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, this->transSSbo);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	compute_program = glCreateProgram();

	compute_shader = CreateShader(LoadShader("ParticleProjectileComputeShader.glsl"), GL_COMPUTE_SHADER);

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
	
	for (int i = 0; i < nrActiveParticles; i++) {
		particleData[i].transformMatrix = data.transformMatrix[i];
		particleData[i].position = data.position[i];
		particleData[i].scaling = data.scaling[i];
		particleData[i].rotation = data.rotation[i];
		particleData[i].velocity = data.velocity[i];
	}


	glUseProgram(compute_program);
	glUniform1fv(glGetUniformLocation(compute_program, "DT"), 1, &deltaTime);
	glDispatchCompute(2, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

	readBuffer();

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	//Copying data
	for (int i = 0; i < nrActiveParticles; i++) {
		data.position[i] = particleData[i].position;
		data.transformMatrix[i] = particleData[i].transformMatrix;
		data.scaling[i] = particleData[i].scaling;
		data.rotation[i] = particleData[i].rotation;
		data.velocity[i] = particleData[i].velocity;
	}

	//std::cout<<"TEST: X: "<< ParticleTestPos1[0].x <<", Y: "<< ParticleTestPos1[0].y<<", Z: "<< ParticleTestPos1[0].z<< std::endl;

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

void ParticleComputeShader::readBuffer() {
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, transSSbo);
	particleData = (struct ParticleComputeStruct *) glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);
	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
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
