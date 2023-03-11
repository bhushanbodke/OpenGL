#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location  = 1) in vec3 aNormal;
//out put 
out vec3 Normal;
out vec3 FragPos;

uniform mat4 MVP;
uniform mat4 model;


void main()
{
    gl_Position = MVP * vec4(aPosition,1.0f);
    FragPos = vec3(model * vec4(aPosition,1.0f));
    Normal =aNormal;
}