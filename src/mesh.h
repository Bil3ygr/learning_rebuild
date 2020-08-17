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
	unsigned int id;
	string type;
	string path;
};

class Mesh
{
public:
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	void Update(Controller *controller);

private:
	vector<Vertex> m_vVertices;
	vector<unsigned int> m_vIndices;
	vector<Texture> m_vTextures;

	GLuint m_nVAO;
};
