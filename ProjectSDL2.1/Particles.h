#ifndef PARTICLES_H
#define PARTICLES_H

#include "GLUtil.h"

namespace particle {
	const int NUM_PARTICLES = 1024 * 1024; //Number of particles
	const int WORK_GROUP_SIZE = 128;       //items per work group
}

struct pos {
	float x, y, z, w;
};

struct vel {
	float vx, vy, vz, vw;
};

struct color {
	float r, g, b, a;
};


class Particles
{
private:
	//Shader storage buffer bjects of position, velocity, color
	GLuint posSSbo, velSSbo, colSSbo;
	GLuint compute_shader, compute_program;
	pos* points;

	GLuint CreateShader(const std::string& text, GLenum shaderType);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram);
	std::string LoadShader(const std::string& fileName);


	enum
	{
		POSITION_VB,

		NUM_BUFFERS
	};

	GLuint m_vertexArrayObject;
	GLuint m_vertexDrawBuffer;


public:
	void Draw();
	void Update();
	Particles();
	~Particles();
};

#endif