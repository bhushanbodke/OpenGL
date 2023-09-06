#version 330 core
layout (location = 0) in vec3 position;
layout (location = 2) in vec2 aTex;
//out put 
out vec2 textCoordinate;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(position,1.0f);
    textCoordinate = aTex;
}