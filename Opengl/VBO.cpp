#include "VBO.h"
#include "errorhandle.h"
VBO::VBO(GLfloat* vertices , GLsizeiptr size)
{
    GLCALL(glGenBuffers(1, &ID));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, ID));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
}
void VBO::bind()
{
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, ID));
}
void VBO::unbind()
{
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
void VBO::Delete()
{
    GLCALL(glDeleteBuffers(1, &ID));
}