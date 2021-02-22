#include "shader.h"
#include "texture.h"

Shader::Shader(const char *vsfile, const char *fsfile, const char *gsfile)
{
	ID = createProgram(vsfile, fsfile, gsfile);
}

Shader::~Shader()
{
	glDeleteProgram(ID);
	glUseProgram(0);
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
{
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string &name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
{
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

GLuint createShader(GLenum shaderType, const char *shaderSource)
{
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "Shader compile failed:\n"
				  << infoLog << std::endl;
		glDeleteShader(shader);
		shader = NULL;
	}
	return shader;
}

GLuint createProgram(GLuint vs, GLuint fs, GLuint gs)
{
	GLuint program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	if (gs != NULL)
		glAttachShader(program, gs);
	glLinkProgram(program);
	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "Program link failed:\n"
				  << infoLog << std::endl;
		glDeleteProgram(program);
		program = NULL;
	}

	glDeleteShader(vs);
	glDeleteShader(fs);
	if (gs != NULL)
		glDeleteShader(gs);
	return program;
}

GLuint createProgram(const char *vsfile, const char *fsfile, const char *gsfile)
{
	GLuint vs = createShader(GL_VERTEX_SHADER, readFile(vsfile));
	if (vs == NULL)
		return NULL;
	GLuint fs = createShader(GL_FRAGMENT_SHADER, readFile(fsfile));
	if (fs == NULL)
		return NULL;
	GLuint gs = NULL;
	if (gsfile != nullptr)
	{
		gs = createShader(GL_GEOMETRY_SHADER, readFile(gsfile));
		if (gs == NULL)
			return NULL;
	}
	return createProgram(vs, fs, gs);
}
