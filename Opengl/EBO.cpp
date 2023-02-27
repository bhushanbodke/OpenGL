#include "EBO.h"
#include "errorhandle.h"

EBO::EBO(GLuint* indices , GLsizeiptr size,unsigned int count)
    :count(count)
{
    GLCALL(glGenBuffers(1, &ID));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW));
}
void EBO::bind()
{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID));
}
void EBO::unbind()
{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
void EBO::Delete()
{
    GLCALL(glDeleteBuffers(1, &ID));
}