#include "GLUtil.h"

struct ParticleComputeStruct {
	glm::vec4 position;
	glm::vec4 velocity;
	glm::vec4 acceleration;
	float scale;
	bool alive;

};

struct ParticleRenderingUpdateData {
	glm::vec4* position;
	glm::vec4* velocity;
	glm::vec4* acceleration;
	float* scale;
	bool *alive;
};

struct ParticleTestPos {
	GLfloat x, y, z, w;
};

class ParticleComputeShader
{
private:
	GLuint transSSbo, velSSbo;
	GLuint compute_program, compute_shader;
	glm::vec4* testPos;
	ParticleComputeStruct* particleData;

	ParticleTestPos* ParticleTestPos1;

	GLuint CreateShader(const std::string& text, GLenum shaderType);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram);
	std::string LoadShader(const std::string& fileName);

	void readBuffer();
public:
	ParticleComputeShader();
	~ParticleComputeShader();

	void Initialize(EmitterType type, int nrMaxParticles, ParticleRenderingUpdateData data);
	void InitializeProjectileShader();

	void Update(const float & deltaTime, int nrActiveParticles, ParticleRenderingUpdateData &data);
};

//g321