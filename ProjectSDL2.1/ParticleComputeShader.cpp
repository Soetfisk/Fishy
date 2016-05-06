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

bool ParticleComputeShader::editComputeData(int index, GLuint &ParticleSSBO) {
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ParticleSSBO);

	struct ParticleStruct* particle;

	GLint bufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT; // the invalidate makes a big difference when re-writing
	particle = (struct ParticleStruct *) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, index*sizeof(ParticleStruct), sizeof(ParticleStruct), bufMask);

	if (particle[0].customVariables.w == 1) {
		glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

		return false;
	}

	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

	return false;


	//int index = i;
	//particles[index].pos = glm::vec4(0 + ParticleSSBO % 5, i, 3, 1);
	//particles[index].customVariables = glm::vec4(.2f, 5.f, .5f, 1); //Scale, Lifetime, Speed, IsAlive(1,0)
	//particles[index].velocity = glm::vec4(1, 0, 0, 0);
	//particles[index].emiterPosition = glm::vec4(0 + ParticleSSBO % 5, i, 3, 1);
	//particles[index].acceleration = glm::vec4(0.f, -.98f, 0.f, 0);

	
}

void ParticleComputeShader::Initialize(EmitterType type, int nrMaxParticles, GLuint &ParticleSSBO) {
	glGenBuffers(1, &ParticleSSBO);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ParticleSSBO);
	glBufferData(GL_SHADER_STORAGE_BUFFER, nrMaxParticles*sizeof(ParticleStruct), NULL, GL_STATIC_DRAW);

	struct ParticleStruct* particles;

	GLint bufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT; // the invalidate makes a big difference when re-writing
	particles = (struct ParticleStruct *) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, nrMaxParticles * sizeof(ParticleStruct), bufMask);

	for (float i = 0; i < nrMaxParticles; i++) {
		int index = i;
		particles[index].pos = glm::vec4(0 + ParticleSSBO%5, i, 3, 1);
		particles[index].customVariables = glm::vec4(.2f, 5.f, .5f, 1); //Scale, Lifetime, Speed, IsAlive(1,0)
		particles[index].velocity = glm::vec4(1, 0, 0, 0);
		particles[index].emiterPosition = glm::vec4(0 + ParticleSSBO % 5, i, 3, 1);
		particles[index].acceleration = glm::vec4(0.f, -.98f, 0.f,0);
	}

	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

	//delete[]particles;

	//struct ParticleStruct* redata;

	//redata = (struct ParticleStruct *) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, sizeof(ParticleStruct), sizeof(ParticleStruct), bufMask);

	//int index = 0;
	//redata[index].pos = glm::vec4(1, index+1, 3, 1);
	//redata[index].customVariables = glm::vec4(.2f, 5.f, .5f, 1); //Scale, Lifetime, Speed, IsAlive(1,0)
	//redata[index].velocity = glm::vec4(1, 0, 0, 0);
	//redata[index].emiterPosition = glm::vec4(1, index+1, 3, 1);
	//redata[index].acceleration = glm::vec4(0.f, -.98f, 0.f, 0);

	//glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

	//glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	//particles = (struct ParticleStruct*) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, n*sizeof(Particle), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

	//glGenBuffers(1, &transSSbo);
	//glBindBuffer(GL_SHADER_STORAGE_BUFFER, transSSbo);
	//glBufferData(GL_SHADER_STORAGE_BUFFER, nrMaxParticles * sizeof(ParticleComputeStruct), NULL, GL_STATIC_DRAW);
	//GLint bufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT; // the invalidate makes a big difference when re-writing
	//particleData = (struct ParticleComputeStruct *) glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, nrMaxParticles * sizeof(ParticleComputeStruct), bufMask);
	////for (int i = 0; i < nrMaxParticles; i++)
	////{
	////	particleData[i].position.x = data.position[i].x;
	////	particleData[i].position.y = data.position[i].y;
	////	particleData[i].position.z = data.position[i].z;
	////	particleData[i].position.w = data.position[i].z;
	////}
	//glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);


	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, ParticleSSBO);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	compute_program = glCreateProgram();

	compute_shader = CreateShader(LoadShader("ParticleTestShader.glsl"), GL_COMPUTE_SHADER);

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

void ParticleComputeShader::Update(const float & deltaTime, int nrActiveParticles, GLuint& ParticleSSBO) {
	
	//if (nrActiveParticles == 2)
	//	int k = 0;
	//for (int i = 0; i < nrActiveParticles; i++) {
	//	particleData[i].position = data.position[i];
	//	particleData[i].scaling = data.scaling[i];
	//	particleData[i].velocity = data.velocity[i];
	//}
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, ParticleSSBO);

	glUseProgram(compute_program);
	glUniform1fv(glGetUniformLocation(compute_program, "DT"), 1, &deltaTime);
	glDispatchCompute((nrActiveParticles/128)+1, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	//Copying data
	//for (int i = 0; i < nrActiveParticles; i++) {
	//	data.position[i] = particleData[i].position;
	//	data.scaling[i] = particleData[i].scaling;
	//	data.velocity[i] = particleData[i].velocity;
	//}

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
