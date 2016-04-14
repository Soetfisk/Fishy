
#include "Particles.h"
#include <ctime>





Particles::Particles()
{
	srand(time(0));

	glGenBuffers(1, &this->posSSbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, posSSbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, particle::NUM_PARTICLES * sizeof(pos), NULL, GL_STATIC_DRAW);

	GLint bufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;

	pos* points = (pos*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, particle::NUM_PARTICLES * sizeof(pos), bufMask);

	//Temporary randoming numbers
	for (int i = 0; i < particle::NUM_PARTICLES; i++) {
		points[i].x = rand() % 20 + 10;
		points[i].y = rand() % 20 + 10;
		points[i].z = rand() % 20 + 10;
		points[i].w = 1;
	}

	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);


	glGenBuffers(1, &this->velSSbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, velSSbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, particle::NUM_PARTICLES * sizeof(vel), NULL, GL_STATIC_DRAW);

	vel* vels = (vel*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, particle::NUM_PARTICLES * sizeof(vel), bufMask);

	for (int i = 0; i < particle::NUM_PARTICLES; i++) {
		vels[i].vx = rand() % 2 + 1;
		vels[i].vy = rand() % 2 + 1;
		vels[i].vz = rand() % 2 + 1;
		vels[i].vw = 0;
	}

	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);


	glGenBuffers(1, &this->colSSbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, colSSbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, particle::NUM_PARTICLES * sizeof(color), NULL, GL_STATIC_DRAW);

	color* Colors = (color*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, particle::NUM_PARTICLES * sizeof(color), bufMask);

	for (int i = 0; i < particle::NUM_PARTICLES; i++) {
		Colors[i].r = rand() % 255;
		Colors[i].g = rand() % 255;
		Colors[i].b = rand() % 255;
		Colors[i].a = rand() % 2;
	}

	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);


	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, this->posSSbo);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, this->velSSbo);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, this->colSSbo);
	
	compute_program = glCreateProgram();

	compute_shader = CreateShader(LoadShader("ParticleComputeShader.glsl"), GL_COMPUTE_SHADER);

	glAttachShader(compute_program, compute_shader);

	glLinkProgram(compute_program);

	CheckShaderError(compute_program, GL_LINK_STATUS, true);

	//glDispatchCompute(particle::NUM_PARTICLES / particle::WORK_GROUP_SIZE, 1, 1);
	//Use program(Compute Program)
	

	//Use program (Rendering porgram)

}

void Particles::Update() {
	glUseProgram(compute_program);
	glDispatchCompute(particle::NUM_PARTICLES / particle::WORK_GROUP_SIZE, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}

void Particles::Draw() {
	glBindBuffer(GL_ARRAY_BUFFER, posSSbo);
	glVertexPointer(4, GL_FLOAT, 0, (void *)0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawArrays(GL_POINTS, 0, particle::NUM_PARTICLES);
	glDisableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


Particles::~Particles()
{
	glDetachShader(compute_program, compute_shader);
	glDeleteShader(compute_shader);
	glDeleteProgram(compute_program);
}

GLuint Particles::CreateShader(const std::string & text, GLenum shaderType)
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
void Particles::CheckShaderError(GLuint shader, GLuint flag, bool isProgram)
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
std::string Particles::LoadShader(const std::string & fileName)
{
	std::ifstream shaderFile;
	shaderFile.open((fileName).c_str());

	std::string shaderText((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());
	shaderFile.close();

	return shaderText;
}
