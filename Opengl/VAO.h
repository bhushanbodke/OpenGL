#pragma once
#include "glad.h"
#include "VBO.h"
class VAO
{
    public:
        GLuint ID;
        VAO();
        void AddAttrib(VBO& vbo , GLuint layout, GLuint type, GLuint stride, void* offset);
        void bind();
        void unbind();
        void Delete();

};