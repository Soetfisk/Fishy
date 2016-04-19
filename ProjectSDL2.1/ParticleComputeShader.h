#include "GLUtil.h"
class ParticleComputeShader
{
private:
	GLuint transSSbo, velSSbo;
	GLuint compute_program, compute_shader;


	GLuint CreateShader(const std::string& text, GLenum shaderType);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram);
	std::string LoadShader(const std::string& fileName);
public:
	ParticleComputeShader();
	~ParticleComputeShader();

	void Initialize(EmitterType type, int nrMaxParticles, glm::mat4* pTransformMatrices, glm::vec4* pVelocities);
	void InitializeProjectileShader();
};

//g321