#pragma once
#include "Utils.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoord;
};

struct Texture
{
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	void DrawMesh(Shader &shader);

private:
	unsigned int vao , vbo ,ebo;
	void setupMesh();
};

