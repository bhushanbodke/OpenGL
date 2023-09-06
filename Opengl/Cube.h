#pragma once
#include "VAO.h"
#include "EBO.h"

class Cube
{
public:
	Cube()
	{
        float vertices[] = {
            // Positions            // Texture Coordinates
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,

             0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, 1.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f
        };

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 36, indices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*5, (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) *5 , (void*)(sizeof(float) * 3));
        glBindVertexArray(0);
	}
    ~Cube()
    {
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
        glDeleteVertexArrays(1, &vao);
    }

    void Draw(Shader& shader,glm::mat4 PV,glm::vec3 Pos ,glm::vec3 color)
    {
        shader.Activate();
        glm::mat4 model = glm::translate(glm::mat4(1.0), Pos);
        auto MVP = PV * model;
        shader.SetUniformMat4("MVP",MVP);
        shader.SetUniformVec3("LightColor",color);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

private:
     unsigned int vao ,vbo , ebo;
     unsigned int indices[36] =
     {
         0, 1, 2,  // First triangle (front face)
         2, 3, 0,  // Second triangle

         4, 5, 6,  // First triangle (back face)
         6, 7, 4,  // Second triangle

         8, 9, 10, // First triangle (left face)
        10, 11, 8, // Second triangle

        12, 13, 14, // First triangle (right face)
        14, 15, 12, // Second triangle

        16, 17, 18, // First triangle (bottom face)
        18, 19, 16,  // Second triangle

        20, 21, 22, // First triangle (top face)
        22, 23, 20  // Second triangle
     };
};
