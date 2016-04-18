
#include "Particles.h"
#include <ctime>





Particles::Particles()
{
	srand(time(0));

	glGenBuffers(1, &this->posSSbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, posSSbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, particle::NUM_PARTICLES * sizeof(pos), NULL, GL_STATIC_DRAW);

	GLint bufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;

	points = (struct pos*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, particle::NUM_PARTICLES * sizeof(pos), bufMask);

	//Temporary randoming numbers
/*	for (int i = 0; i < particle::NUM_PARTICLES; i++) {
		points[i].x = 0 + i*.1;
		points[i].y = 0 + i*.1;
		points[i].z = 0;
		points[i].w = 1;
	}    */         
	points[0].x = -1.0f;
	points[0].y = 1.0f;
	points[0].z = 0.0f;
	points[0].w = 1.0f;

	points[1].x = -1.0f;
	points[1].y = -1.0f;
	points[1].z = 0.0f;
	points[1].w = 1.0f;

	points[2].x = 1.0f;
	points[2].y = 1.0f;
	points[2].z = 0.0f;
	points[2].w = 1.0f;

	points[3].x = 1.0f;
	points[3].y = -1.0f;
	points[3].z = 0.0f;
	points[3].w = 1.0f;



	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);


	glGenBuffers(1, &this->velSSbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, velSSbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, particle::NUM_PARTICLES * sizeof(vel), NULL, GL_STATIC_DRAW);

	vel* vels = (struct vel*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, particle::NUM_PARTICLES * sizeof(vel), bufMask);

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

	color* Colors = (struct color*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, particle::NUM_PARTICLES * sizeof(color), bufMask);

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


	glGenBuffers(1, &m_vertexDrawBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexDrawBuffer);
	glBufferData(GL_ARRAY_BUFFER, particle::NUM_PARTICLES * sizeof(points[0]), &points[0], GL_STATIC_DRAW);


	glGenVertexArrays(1, &m_vertexArrayObject); 
	glBindVertexArray(m_vertexArrayObject);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	
	
	
	//glBindVertexArray(0);


	//glGenVertexArrays(1, &m_vertexArrayObject);
	//glBindVertexArray(m_vertexArrayObject);
	//glBindBuffer(GL_ARRAY_BUFFER, posSSbo);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	//glBindVertexArray(0);


	//glGenBuffers(1, m_vertexArrayBuffers);
	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	//glBufferData(GL_ARRAY_BUFFER, particle::NUM_PARTICLES * sizeof(points[0]), &points[0], GL_STATIC_DRAW);


	//glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	//glDispatchCompute(particle::NUM_PARTICLES / particle::WORK_GROUP_SIZE, 1, 1);
	//Use program(Compute Program)
	

	//Use program (Rendering porgram)

}

void Particles::Update() {
	glUseProgram(compute_program);
	glDispatchCompute(particle::NUM_PARTICLES / particle::WORK_GROUP_SIZE, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

	for (int i = 0; i < particle::NUM_PARTICLES; i++) {
		//printf(i + " : " + (int)points[i].x);
		//std::cout<<i<<" : " << points[i].x << std::endl;
	}
	
}

void Particles::Draw() {
	//glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, posSSbo);

	glBindVertexArray(m_vertexArrayObject);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, particle::NUM_PARTICLES);
	glBindVertexArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, posSSbo);
	//glVertexPointer(4, GL_FLOAT, 0, (void *)0);
	//glEnableClientState(GL_VERTEX_ARRAY);
	//glDrawArrays(GL_POINTS, 0, particle::NUM_PARTICLES);
	//glDisableClientState(GL_VERTEX_ARRAY);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
}


Particles::~Particles()
{
	glDetachShader(compute_program, compute_shader);
	glDeleteShader(compute_shader);
	glDeleteProgram(compute_program);
	glDeleteVertexArrays(1, &m_vertexArrayObject);
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
