#pragma once
#include "glad.h"
class EBO
{
    public:
        GLuint ID;
        unsigned int count;
        EBO(GLuint* vertices , GLsizeiptr size ,unsigned int count );

        void bind();
        void unbind();
        void Delete();

};