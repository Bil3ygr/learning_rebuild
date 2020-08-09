#pragma once

#include <vector>
#include "main.h"
#include "shader.h"
#include "texture.h"

class Controller
{
public:
	Controller(const char *vsfile, const char *fsfile, const char *gsfile = nullptr);
	~Controller();

	void setVertexInfo(
		float *vertices, int vertices_size,
		int *pointers, int pointer_count, bool *pointer_enable,
		int *indices = nullptr, int indices_size = NULL);
	int addTexture(const char *filepath);
	void setDepthEnable();
	void setDepthEnable(bool enable);
	void setClearColor(float r, float g, float b, float a = 1.0f);
	void clear();
	void use();
	void activeTexture(GLenum texture_index, int index);

private:
	Shader *m_pShader = nullptr;
	unsigned int m_nVAO = NULL;
	std::vector<unsigned int> m_lTexture;
	float m_fClearR, m_fClearG, m_fClearB, m_fClearA;
	bool m_bDepthEnable = false;
};
