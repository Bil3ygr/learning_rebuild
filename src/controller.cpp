#include "controller.h"

Controller::Controller(const char *vsfile, const char *fsfile, const char *gsfile)
{
	m_pShader = new Shader(vsfile, fsfile, gsfile);
}

Controller::~Controller()
{
	glDeleteVertexArrays(1, &m_nVAO);
	delete m_pShader;
	glBindVertexArray(0);
}

void Controller::setVertexInfo(
	float *vertices, int vertices_size,
	int *pointers, int pointer_count, bool *pointer_enable,
	int *indices, int indices_size)
{
	m_nVAO = createVertexInfo(vertices, vertices_size, pointers, pointer_count, pointer_enable, indices, indices_size);
}

int Controller::addTexture(const char *filepath)
{
	m_lTexture.push_back(create2DTextureFromFile(filepath));
	return (int)(m_lTexture.size() - 1);
}

void Controller::setDepthEnable()
{
	if (m_bDepthEnable)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
}

void Controller::setDepthEnable(bool enable)
{
	m_bDepthEnable = enable;
}

void Controller::use()
{
	m_pShader->use();
	glBindVertexArray(m_nVAO);
}

void Controller::setClearColor(float r, float g, float b, float a)
{
	m_fClearR = r;
	m_fClearG = g;
	m_fClearB = b;
	m_fClearA = a;
	m_bSetClearColor = true;
}

void Controller::clear()
{
	if (m_bSetClearColor)
	{
		m_bSetClearColor = false;
		glClearColor(m_fClearR, m_fClearG, m_fClearB, m_fClearA);
	}

	if (m_bDepthEnable)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	else
		glClear(GL_COLOR_BUFFER_BIT);
}

void Controller::activeTexture(GLenum texture_index, int index)
{
	if (index >= 0 && index < m_lTexture.size())
	{
		glActiveTexture(texture_index);
		glBindTexture(GL_TEXTURE_2D, m_lTexture[index]);
	}
	else
	{
		std::cout << "texture index error: " << index << std::endl;
	}
}
