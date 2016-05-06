#include "GLUtil.h"

struct ParticleComputeStruct {
	glm::vec4 position;
	glm::vec4 velocity;
	glm::vec4 customVariables;
};

struct ParticleRenderingUpdateData {
	glm::vec4* position;
	glm::vec4* velocity;
	glm::vec4* customVariables;
};

struct ParticleStruct {
	glm::vec4 pos;
	glm::vec4 emiterPosition;
	glm::vec4 velocity;
	glm::vec4 customVariables;
	glm::vec4 acceleration;
};

struct ParticleTestPos {
	GLfloat x, y, z, w;
};

class ParticleComputeShader
{
private:
	
	GLuint spawnSSBO;
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

	void Initialize(EmitterType type, int nrMaxParticles, GLuint &ParticleSSBO);
	void InitializeProjectileShader();

	void Update(const float & deltaTime, int nrActiveParticles, GLuint &ParticleSSBOS);
	bool editComputeData(int index, GLuint &ParticleSSBO);
};

//g321