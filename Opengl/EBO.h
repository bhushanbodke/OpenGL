#pragma once
#include "glad.h"
class EBO
{
    public:
        GLuint ID;
        EBO(GLuint* indices , GLsizeiptr size);

        void bind();
        void unbind();
        void Delete();

};