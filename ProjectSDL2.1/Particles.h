#ifndef PARTICLES_H
#define PARTICLES_H

#include "GLUtil.h"
#include "GLShader.h"

namespace particle {
	//const int NUM_PARTICLES = 1024 * 1024; //Number of particles
	//const int WORK_GROUP_SIZE = 128;       //items per work group

	const int NUM_PARTICLES = 1*2; //Number of particles
	const int WORK_GROUP_SIZE = 1;       //items per work group
}

struct pos {
	GLfloat x, y, z, w;
};

struct vel {
	GLfloat vx, vy, vz, vw;
};

struct color {
	GLfloat r, g, b, a;
};

struct PTest {
	glm::vec4 pos;
	glm::vec4 vel;
	glm::vec4 color;

	PTest() : pos(glm::vec4(0, 0, 3, 1)), vel(), color() {}
};


class Particles
{
private:
	//Shader storage buffer bjects of position, velocity, color
	GLuint posSSbo, velSSbo, colSSbo;
	GLuint compute_shader, compute_program;
	GLuint p_SizeLocation;
	pos* points;
	std::vector<pos>* pointsTest;
	glm::mat4* worldMatrices;

	GLuint CreateShader(const std::string& text, GLenum shaderType);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram);
	std::string LoadShader(const std::string& fileName);
	float p_size;

	enum
	{
		POSITION_VB,

		NUM_BUFFERS
	};

	GLuint m_vertexArrayObject;
	GLuint m_vertexDrawBuffer;


public:
	void Draw(GLShader * shader);
	void Update();
	Particles(GLShader * shader);
	~Particles();
};

#endif