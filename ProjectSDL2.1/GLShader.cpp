#include "GLShader.h"
GLShader::GLShader(const std::string& fileName)
{
	//create program
	m_program = glCreateProgram();

	m_shaders[0] = CreateShader(LoadShader(fileName + ".vert.glsl"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileName + ".frag.glsl"), GL_FRAGMENT_SHADER);
	m_shaders[2] = CreateShader(LoadShader(fileName + ".geom.glsl"), GL_GEOMETRY_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glAttachShader(m_program, m_shaders[i]);
	}

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true);

	m_uniforms[TRANSFROM_U] =	glGetUniformLocation(m_program, "TransformMatrix");
	m_uniforms[PROJVIEW_U] =	glGetUniformLocation(m_program, "ProjectionViewMatrix");
	m_uniforms[VIEWPOS_U] =		glGetUniformLocation(m_program, "ViewPos");
}

void GLShader::Bind()
{
	glUseProgram(m_program);
}

void GLShader::Update(GLMesh& mesh, const GLCamera& camera)
{
	glm::mat4 model = mesh.GetTransform().GetModel();
	glm::mat4 projView = camera.GetViewProjectionMatrix();
	glm::vec3 viewPos = camera.GetPos();
	glUniformMatrix4fv(m_uniforms[TRANSFROM_U], 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(m_uniforms[PROJVIEW_U], 1, GL_FALSE, glm::value_ptr(projView));
	glUniform3fv(m_uniforms[VIEWPOS_U], 1, glm::value_ptr(viewPos));

	GLint matAmbientLoc =	glGetUniformLocation(m_program, "material.ambient");
	GLint matDiffuseLoc =	glGetUniformLocation(m_program, "material.diffuse");
	GLint matSpecularLoc =	glGetUniformLocation(m_program, "material.specular");
	GLint matShineLoc =		glGetUniformLocation(m_program, "material.shininess");

	glUniform3fv(matAmbientLoc, 1, glm::value_ptr(mesh.GetMaterial().ambient));
	glUniform3fv(matDiffuseLoc, 1, glm::value_ptr(mesh.GetMaterial().diffuse));
	glUniform3fv(matSpecularLoc, 1, glm::value_ptr(mesh.GetMaterial().specular));
	glUniform1f(matShineLoc, mesh.GetMaterial().shininess);

	mesh.GetMaterial().texture->Bind(0);
	glUniform1i(this->GetUnifromLocation("diffuseTexture"), 0);
}

void GLShader::Update(GLTransform & tranform, const GLCamera & camera)
{
	glm::mat4 model = tranform.GetModel();
	glm::mat4 projView = camera.GetViewProjectionMatrix();
	glm::vec3 viewPos = camera.GetPos();
	glUniformMatrix4fv(m_uniforms[TRANSFROM_U], 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(m_uniforms[PROJVIEW_U], 1, GL_FALSE, glm::value_ptr(projView));
	glUniform3fv(m_uniforms[VIEWPOS_U], 1, glm::value_ptr(viewPos));

	GLint matAmbientLoc = glGetUniformLocation(m_program, "material.ambient");
	GLint matDiffuseLoc = glGetUniformLocation(m_program, "material.diffuse");
	GLint matSpecularLoc = glGetUniformLocation(m_program, "material.specular");
	GLint matShineLoc = glGetUniformLocation(m_program, "material.shininess");

	glUniform3fv(matAmbientLoc, 1, glm::value_ptr(glm::vec3(1,1,1)));
	glUniform3fv(matDiffuseLoc, 1, glm::value_ptr(glm::vec3(1,1,1)));
	glUniform3fv(matSpecularLoc, 1, glm::value_ptr(glm::vec3(0,0,0)));
	glUniform1f(matShineLoc, 0.0f);
}

GLuint& GLShader::GetUnifromLocation(std::string name)
{
	GLuint unifrom = glGetUniformLocation(m_program, name.c_str());
	return unifrom;
}

GLShader::~GLShader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}

	glDeleteProgram(m_program);
}

GLuint GLShader::CreateShader(const std::string & text, GLenum shaderType)
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

void GLShader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram)
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

std::string GLShader::LoadShader(const std::string & fileName)
{
	std::ifstream shaderFile;
	shaderFile.open((fileName).c_str());

	std::string shaderText((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());
	shaderFile.close();

	return shaderText;
}
