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

	void setVertexInfo(float *vertices, int *pointers, int *indices = nullptr,
					   bool *pointer_enable = nullptr);

	int addTexture(const char *filepath);
	void activeTexture(GLenum texture_index, int index);

	void setDepthEnable();
	void setDepthEnable(bool enable, GLenum depthFunc = GL_LESS);

	void setStencilEnable();
	void setStencilEnable(bool enable);
	void setStencilOptions(GLenum func, GLint ref, GLuint mask, GLenum sfail, GLenum dpfail, GLenum dppass);
	void setStencilMask(GLuint mask);

	void setBlendEnable();
	void setBlendEnable(bool enable);
	void setBlendOptions(GLenum sfactor, GLenum dfactor, GLenum mode);
	void setBlendOptions(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorA, GLenum dfactorA, GLenum modeRBG, GLenum modeA);

	void setClearColor(float r, float g, float b, float a = 1.0f);
	void clear();

	void use();
	void update(bool clear_color = true);

protected:
	GLuint m_nVAO = NULL;
	std::vector<unsigned int> m_lTexture;
	bool m_bDepthEnable = false, m_bStencilEnable = false, m_bBlendEnable = false;

	float m_fClearR, m_fClearG, m_fClearB, m_fClearA;
	bool m_bSetClearColor = false;

	GLenum m_eDepthFunc = GL_LESS;

	GLenum m_eStencilFunc = GL_ALWAYS;
	GLint m_nStencilFuncRef = 1;
	GLuint m_nStencilFuncMask = 0xff;
	GLenum m_eStencilFuncFail = GL_KEEP;
	GLenum m_eStencilFuncDpFail = GL_KEEP;
	GLenum m_eStencilFuncDpPass = GL_KEEP;
	GLuint m_nStencilMask = 0xff;

	GLenum m_eBlendSrcFactorA = GL_SRC_ALPHA, m_eBlendDstFactorA = GL_ONE_MINUS_SRC_ALPHA;
	GLenum m_eBlendSrcFactorRGB = NULL, m_eBlendDstFactorRGB = NULL;
	GLenum m_eBlendModeRGB = GL_FUNC_ADD, m_eBlendModeA = GL_FUNC_ADD;
};

GLuint createVertexInfo(float *vertices, int *pointers, int *indices = nullptr,
						bool *pointer_enable = nullptr);

GLuint createVertexInfo(const void *vertices, int vertices_size, int *pointers,
						const void *indices = nullptr, int indices_size = 0,
						bool *pointer_enable = nullptr);
