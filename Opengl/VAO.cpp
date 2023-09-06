#include "VAO.h"
#include "errorhandle.h"

VAO::VAO()
{
    GLCALL(glGenVertexArrays(1, &ID));
}
void VAO::AddAttrib(VBO& vbo  , GLuint layout,int count , GLuint type, GLuint stride, void* offset)
{
    vbo.bind();
    GLCALL(glEnableVertexAttribArray(layout));
    GLCALL(glVertexAttribPointer(layout,count, type, GL_FALSE, stride, offset));
    vbo.unbind();
}

void VAO::bind()
{
    GLCALL(glBindVertexArray (ID));
}
void VAO::unbind()
{
    GLCALL(glBindVertexArray(0));
}
void VAO::Delete()
{
    glDeleteVertexArrays(1, &ID);
}