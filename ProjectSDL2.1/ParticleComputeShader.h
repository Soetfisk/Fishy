#include "GLUtil.h"

struct ParticleComputeStruct {
	glm::mat4 transformMatrix;
	glm::vec4 position;
	glm::vec4 velocity;
};

class ParticleComputeShader
{
private:
	GLuint transSSbo, velSSbo;
	GLuint compute_program, compute_shader;
	glm::vec4* testPos;
	ParticleComputeStruct* particleData;

	GLuint CreateShader(const std::string& text, GLenum shaderType);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram);
	std::string LoadShader(const std::string& fileName);
public:
	ParticleComputeShader();
	~ParticleComputeShader();

	void Initialize(EmitterType type, int nrMaxParticles, glm::mat4*& pTransformMatrices, glm::vec4* pVelocities , glm::vec4*& pos);
	void InitializeProjectileShader();

	void Update(const float & deltaTime, int nrActiveParticles);
};

//g321