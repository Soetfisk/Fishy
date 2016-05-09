#include "GLShader.h"

GLShader::GLShader(const std::string& fileName, const bool& geometry)
{
	//create program
	m_program = glCreateProgram();

	if (geometry)
	{
		nrOfShaders = 3;
		//m_shaders = new GLuint[nrOfShaders];
		m_shaders[0] = CreateShader(LoadShader(fileName + ".vert"), GL_VERTEX_SHADER);
		m_shaders[1] = CreateShader(LoadShader(fileName + ".frag"), GL_FRAGMENT_SHADER); 
		m_shaders[2] = CreateShader(LoadShader(fileName + ".geom"), GL_GEOMETRY_SHADER);
	}
	else
	{
		nrOfShaders = 2;
		//m_shaders = new GLuint[nrOfShaders];
		m_shaders[0] = CreateShader(LoadShader(fileName + ".vert"), GL_VERTEX_SHADER);
		m_shaders[1] = CreateShader(LoadShader(fileName + ".frag"), GL_FRAGMENT_SHADER);
	}		

	for (int i = 0; i < nrOfShaders; i++)
	{
		glAttachShader(m_program, m_shaders[i]);
	}

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true);

	m_uniforms[TRANSFROM_U] =	glGetUniformLocation(m_program, "TransformMatrix");
	//m_uniforms[PROJECTIONVIEW_U] = glGetUniformLocation(m_program, "ProjectionViewMatrix");
	
	m_uniforms[PROJECTION_U] = glGetUniformLocation(m_program, "ProjectionMatrix");
	m_uniforms[VIEW_U] = glGetUniformLocation(m_program, "ViewMatrix");
	m_uniforms[VIEWPOS_U] =		glGetUniformLocation(m_program, "ViewPos");
	GLuint d = glGetUniformLocation(m_program, "diffuseTexture");

}

/*
	Use the shaders program
*/
void GLShader::Bind()
{
	glUseProgram(m_program);
}

void GLShader::Update(GLCamera& camera)
{

	glm::mat4 view_matrix = camera.GetViewMatrix();
	glm::mat4 proj_matrix = camera.GetProjectionMatrix();
	//glm::mat4 view_proj_matrix = camera.GetViewProjectionMatrix();
	glm::vec3 viewPos = camera.Position();
	glUniformMatrix4fv(m_uniforms[VIEW_U], 1, GL_FALSE, glm::value_ptr(view_matrix));
	glUniformMatrix4fv(m_uniforms[PROJECTION_U], 1, GL_FALSE, glm::value_ptr(proj_matrix));
	//glUniformMatrix4fv(m_uniforms[PROJECTIONVIEW_U], 1, GL_FALSE, glm::value_ptr(view_proj_matrix));

	glUniform3fv(m_uniforms[VIEWPOS_U], 1, glm::value_ptr(viewPos));
}


GLuint GLShader::GetUnifromLocation(std::string name)
{
	return glGetUniformLocation(m_program, name.c_str());
}

GLShader::~GLShader()
{
	for (int i = 0; i < nrOfShaders; i++)
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

/*
	Read and load shaderfile into a string and return it
*/
std::string GLShader::LoadShader(const std::string & fileName)
{
	std::ifstream shaderFile;
	shaderFile.open((fileName).c_str());

	std::string shaderText((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());
	shaderFile.close();

	return shaderText;
}

void GLShader::Uniform1f(std::string name, float number)
{
	glUniform1f(glGetUniformLocation(this->m_program, name.c_str()), number);
	
}


void GLShader::UniformVec3(std::string name, glm::vec3 vector)
{
	glUniform3fv(glGetUniformLocation(this->m_program, name.c_str()), 1, &vector[0]);
}

void GLShader::Uniform1ui(std::string name, GLuint number)
{
	//printf("\n%d", glGetUniformLocation(this->m_program, name.c_str()));
	glUniform1i(glGetUniformLocation(this->m_program, name.c_str()), number);

}

void GLShader::Uniform1fv(std::string name, float number[12])
{
	//printf("\n%d", glGetUniformLocation(this->m_program, name.c_str()));
	glUniform1fv(glGetUniformLocation(this->m_program, name.c_str()), 12, number);
}
