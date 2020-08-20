#pragma once

#include "controller.h"
#include <assimp/Importer.hpp>
#include <string>
#include <vector>

using namespace ::std;

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture
{
	GLuint id;
	string type;
	string path;
};

class Mesh
{
public:
	Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);
	void update(Controller *controller);

private:
	vector<Vertex> m_vVertices;
	vector<GLuint> m_vIndices;
	vector<Texture> m_vTextures;

	GLuint m_nVAO;
};
