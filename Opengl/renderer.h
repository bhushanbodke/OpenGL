#pragma once
#include "glad.h"
#include "VAO.h"
#include "EBO.h"
#include "ShaderClass.h"
#include "errorhandle.h"

class Renderer
{
    public:
        void DrawElements(VAO& vao, EBO& ebo, Shader& shader)const;
        void DrawArrays(VAO& vao , int start , int total)const;

        void Clear() const;
        void Clear(const float r , const float g , const float b , const float a) const;
};

