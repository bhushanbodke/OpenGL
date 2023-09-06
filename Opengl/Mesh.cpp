#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	setupMesh();
}

void Mesh::DrawMesh(Shader& shader)
{

	int specularNo = 1; 
	int diffuseNo = 1; 
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		GLCALL(glActiveTexture(GL_TEXTURE0 + i));
			 
		std::string number;
		std::string name = textures[i].type;

		if (name == "texture_diffuse")
		{ 
			number = std::to_string(diffuseNo);
			diffuseNo++;
		}
		else if (name =="texture_specular")
		{
			number = std::to_string(specularNo);
			specularNo++;
		}
		shader.SetUniform1i(("material."+name+"["+number+"]").c_str(), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}
	shader.SetUniform1F("material.Shininess", 32.0f);
	shader.SetUniform1i("material.num_specular_textures", specularNo - 1);
	shader.SetUniform1i("material.num_diffuse_textures", diffuseNo - 1);
	GLCALL(glBindVertexArray(vao));
	GLCALL(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0));
	GLCALL(glBindVertexArray(0));
	GLCALL(glActiveTexture(GL_TEXTURE0));

}

void Mesh::setupMesh()
{
	
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,Normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex , TexCoord));

	glBindVertexArray(0);
}
