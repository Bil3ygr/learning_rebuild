#pragma once

#include "main.h"
#include "shader.h"
#include "texture.h"
#include <vector>

class Controller
{
public:
	Shader *m_pShader = nullptr;

	Controller(const char *vsfile, const char *fsfile, const char *gsfile = nullptr);
	~Controller();

	void setVertexInfo(
		float *vertices, int vertices_size,
		int *pointers, int pointer_count, bool *pointer_enable,
		int *indices = nullptr, int indices_size = NULL);
	int addTexture(const char *filepath);
	void setDepthEnable();
	void setDepthEnable(bool enable, GLenum depthFunc = GL_LESS);
	void setStencilEnable();
	void setStencilEnable(bool enable);
	void setStencilOptions(GLenum func, GLint ref, GLuint mask, GLenum sfail, GLenum dpfail, GLenum dppass);
	void setClearColor(float r, float g, float b, float a = 1.0f);
	void setStencilMask(GLuint mask);
	void clear();
	void use();
	void activeTexture(GLenum texture_index, int index);
	void update(bool clear_color = true);

protected:
	GLuint m_nVAO = NULL;
	std::vector<unsigned int> m_lTexture;
	float m_fClearR, m_fClearG, m_fClearB, m_fClearA;
	GLuint m_nStencilMask = 0xff;
	bool m_bDepthEnable = false, m_bStencilEnable = false, m_bSetClearColor = false;
	GLenum m_eDepthFunc = GL_LESS, m_eStencilFunc = GL_ALWAYS;
	GLint m_nStencilFuncRef = 1;
	GLuint m_nStencilFuncMask = 0xff;
	GLenum m_eStencilFuncFail = GL_KEEP;
	GLenum m_eStencilFuncDpFail = GL_KEEP;
	GLenum m_eStencilFuncDpPass = GL_KEEP;
};
