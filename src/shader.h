#pragma once

#include <string>
#include <glm/glm.hpp>
#include "utils.h"

GLuint createShader(GLenum shaderType, const char *shaderSource);
GLuint createProgram(GLuint vs, GLuint fs, GLuint gs = NULL);
GLuint createProgram(const char *vsfile, const char *fsfile, const char *gsfile = nullptr);
GLuint createVertexInfo(
	float *vertices, int vertices_size,
	int *pointers, int pointer_count, bool *pointer_enable,
	int *indices = nullptr, int indices_size = 0);

class Shader
{
public:
	GLuint ID = 0;

	Shader(const char *vsfile, const char *fsfile, const char *gsfile = nullptr);
	~Shader();

	void use();
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setVec2(const std::string &name, const glm::vec2 &value) const;
	void setVec2(const std::string &name, float x, float y) const;
	void setVec3(const std::string &name, const glm::vec3 &value) const;
	void setVec3(const std::string &name, float x, float y, float z) const;
	void setVec4(const std::string &name, const glm::vec4 &value) const;
	void setVec4(const std::string &name, float x, float y, float z, float w) const;
	void setMat2(const std::string &name, const glm::mat2 &mat) const;
	void setMat3(const std::string &name, const glm::mat3 &mat) const;
	void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:
};
