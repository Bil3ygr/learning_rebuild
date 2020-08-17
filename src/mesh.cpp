#include "mesh.h"
#include <iostream>

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures) : m_vVertices(vertices), m_vIndices(indices), m_vTextures(textures)
{
	GLuint VBO, EBO = NULL;
	glGenVertexArrays(1, &m_nVAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(m_nVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, m_vVertices.size() * sizeof(Vertex), &m_vVertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_vIndices.size() * sizeof(unsigned int), &m_vIndices[0], GL_STATIC_DRAW);

	// 顶点位置
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
	// 顶点法线
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Normal));
	// 顶点纹理坐标
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, TexCoords));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Mesh::Draw(Shader fs)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	for (unsigned int i = 0; i < m_vTextures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		string number;
		string name = m_vTextures[i].type;
		if (name == "texture_diffuse")
			number = to_string(diffuseNr++);
		else if (name == "texutre_specular")
			number = to_string(specularNr++);

		fs.setFloat(("material." + name + number).c_str(), (float)i);
		glBindTexture(GL_TEXTURE_2D, m_vTextures[i].id);
	}
	glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(m_nVAO);
	glDrawElements(GL_TRIANGLES, (GLsizei)m_vIndices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
