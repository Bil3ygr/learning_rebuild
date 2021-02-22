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

void Controller::setVertexInfo(float *vertices, int *pointers, int *indices, bool *pointer_enable)
{
	m_nVAO = createVertexInfo(vertices, pointers, indices, pointer_enable);
}

int Controller::addTexture(const char *filepath)
{
	m_lTexture.push_back(create2DTextureFromFile(filepath));
	return (int)(m_lTexture.size() - 1);
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

void Controller::setDepthEnable()
{
	if (m_bDepthEnable)
	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(m_eDepthFunc);
	}
	else
		glDisable(GL_DEPTH_TEST);
}

void Controller::setDepthEnable(bool enable, GLenum depthFunc)
{
	m_bDepthEnable = enable;
	m_eDepthFunc = depthFunc;
}

void Controller::setStencilEnable()
{
	if (m_bStencilEnable)
	{
		glEnable(GL_STENCIL_TEST);
		glStencilFunc(m_eStencilFunc, m_nStencilFuncRef, m_nStencilFuncMask);
		glStencilOp(m_eStencilFuncFail, m_eStencilFuncDpFail, m_eStencilFuncDpPass);
		glStencilMask(m_nStencilMask);
	}
	else
		glDisable(GL_STENCIL_TEST);
}

void Controller::setStencilEnable(bool enable)
{
	m_bStencilEnable = enable;
}

void Controller::setStencilOptions(GLenum func, GLint ref, GLuint mask, GLenum sfail, GLenum dpfail, GLenum dppass)
{
	m_eStencilFunc = func;
	m_nStencilFuncRef = ref;
	m_nStencilFuncMask = mask;
	m_eStencilFuncFail = sfail;
	m_eStencilFuncDpFail = dpfail;
	m_eStencilFuncDpPass = dppass;
}

void Controller::setStencilMask(GLuint mask)
{
	m_nStencilMask = mask;
}

void Controller::setBlendEnable()
{
	if (m_bBlendEnable)
	{
		glEnable(GL_BLEND);
		if (m_eBlendSrcFactorRGB == NULL)
		{
			glBlendFunc(m_eBlendSrcFactorA, m_eBlendDstFactorA);
			glBlendEquation(m_eBlendModeA);
		}
		else
		{
			glBlendFuncSeparate(m_eBlendSrcFactorRGB, m_eBlendDstFactorRGB, m_eBlendSrcFactorA, m_eBlendDstFactorA);
			glBlendEquationSeparate(m_eBlendModeRGB, m_eBlendModeA);
		}
	}
	else
		glDisable(GL_BLEND);
}

void Controller::setBlendEnable(bool enable)
{
	m_bBlendEnable = enable;
}

void Controller::setBlendOptions(GLenum sfactor, GLenum dfactor, GLenum mode)
{
	m_eBlendSrcFactorA = sfactor;
	m_eBlendDstFactorA = dfactor;
	m_eBlendModeA = mode;
}

void Controller::setBlendOptions(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorA, GLenum dfactorA, GLenum modeRBG, GLenum modeA)
{
	m_eBlendSrcFactorRGB = sfactorRGB;
	m_eBlendDstFactorRGB = dfactorRGB;
	m_eBlendSrcFactorA = sfactorA;
	m_eBlendDstFactorA = dfactorA;
	m_eBlendModeRGB = modeRBG;
	m_eBlendModeA = modeA;
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

	GLbitfield mask = GL_COLOR_BUFFER_BIT;
	if (m_bDepthEnable)
		mask |= GL_DEPTH_BUFFER_BIT;
	if (m_bStencilEnable)
		mask |= GL_STENCIL_BUFFER_BIT;
	glClear(mask);
}

void Controller::use()
{
	m_pShader->use();
	glBindVertexArray(m_nVAO);
}

void Controller::update(bool clear_color)
{
	setDepthEnable();
	setStencilEnable();
	setBlendEnable();

	if (clear_color)
		clear();

	use();
}

GLuint createVertexInfo(float *vertices, int *pointers, int *indices,
						bool *pointer_enable)
{
	return createVertexInfo(vertices, sizeof(vertices), pointers,
							indices, sizeof(indices), pointer_enable);
}
GLuint createVertexInfo(const void *vertices, int vertices_size, int *pointers,
						const void *indices, int indices_size, bool *pointer_enable)
{
	GLuint VAO, VBO, EBO = NULL;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// 绑定顶点数组
	glBindVertexArray(VAO);
	// 绑定顶点缓存
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);
	// 绑定索引信息
	if (indices)
	{
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW);
	}
	// 设置顶点读取信息
	int pointer_count = sizeof(pointers) / sizeof(pointers[0]);
	int total = 0;
	for (int i = 0; i < pointer_count; i++)
		total += pointers[i];
	int offset = 0;
	for (int i = 0; i < pointer_count; i++)
	{
		if (!pointer_enable || pointer_enable[i])
		{
			glVertexAttribPointer(
				i, pointers[i], GL_FLOAT, GL_FALSE, total * sizeof(float),
				(void *)(offset * sizeof(float)));
			glEnableVertexAttribArray(i);
		}
		offset += pointers[i];
	}
	// 清空
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	// 删除
	glDeleteBuffers(1, &VBO);
	if (indices)
		glDeleteBuffers(1, &EBO);
	return VAO;
}
