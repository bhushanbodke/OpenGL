#include "renderer.h"

void Renderer::Draw(VAO &vao, EBO &ebo, Shader &shader) const
{
    vao.bind();
    GLCALL(shader.Activate());
    GLCALL(glDrawElements(GL_TRIANGLES,ebo.count,GL_UNSIGNED_INT,0));
}
void Renderer::Clear() const
{
    GLCALL(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Clear(const float r, const float g, const float b, const float a) const
{
    glClearColor(r, g, b, a);
}
