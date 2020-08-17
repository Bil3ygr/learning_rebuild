#pragma once

#include "mesh.h"
#include "texture.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <iostream>

class Model
{
public:
	Model(const char *path);
	void Draw(Shader shader);

private:
	vector<Texture> m_vTexturesLoaded;
	vector<Mesh> m_vMeshes;
	string m_sDirectory;

	void loadModel(string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
};
