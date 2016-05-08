#include "GLUtil.h"

struct ParticleStruct {
	glm::vec4 pos;
	glm::vec4 emiterPosition;
	glm::vec4 velocity;
	glm::vec4 acceleration;
	glm::vec4 customVariables; //x= scale, y=lifeTime, z = speed, w = is alive
};

struct ParticleTestPos {
	GLfloat x, y, z, w;
};

class ParticleComputeShader
{
private:

	GLuint atomicBuffer;
	GLuint compute_program, compute_shader;
	glm::vec4* testPos;

	ParticleTestPos* ParticleTestPos1;

	GLuint CreateShader(const std::string& text, GLenum shaderType);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram);
	std::string LoadShader(const std::string& fileName);

	void spawnParticleAt(int index);
	void readBuffer();
	int nrParticles;
public:
	ParticleComputeShader();
	~ParticleComputeShader();

	void Initialize(EmitterType type, int nrMaxParticles, GLuint &ParticleSSBO);
	void InitializeProjectileShader();

	void Update(const float & deltaTime, int nrActiveParticles, GLuint &ParticleSSBOS);
	bool editComputeData(int index, GLuint &ParticleSSBO);

	int getNrParticles();
	void spawnParticle(GLuint &ParticleSSBO);
	void updateEmitterPosition(glm::vec4 pos, GLuint &ParticleSSBO);
	void bind();
};

//g321