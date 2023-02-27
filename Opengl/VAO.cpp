#include "VAO.h"
#include "errorhandle.h"

VAO::VAO()
{
    GLCALL(glGenVertexArrays(1, &ID));
}
void VAO::AddAttrib(VBO& vbo , GLuint layout, GLuint type, GLuint stride, void* offset)
{
    vbo.bind();
    GLCALL(glVertexAttribPointer(layout, 4, type, GL_FALSE, stride, offset));
    GLCALL(glEnableVertexAttribArray(layout));
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