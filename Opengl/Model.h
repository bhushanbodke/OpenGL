#pragma once
#include "Utils.h"
#include "stb_Image.h"
#include "Mesh.h"

class Model
{
public:
	unsigned int NoTriangles;
	Model(std::string path);
	void Draw(Shader& shader);

	int GetMeshNo();
private:
	std::vector<Mesh> Meshes;
	std::vector<Texture> loaded_textures;

	std::string directory;  // for texture refrence

	void LoadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string TypeName);

	unsigned int GetTextureID(std::string path, std::string directory);
};

