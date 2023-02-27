#version 330 core
out vec4 FragColor;

// input 
in vec3 Color;

in vec2 textCoordinate;

uniform sampler2D m_Texture;


void main()
{
    FragColor = texture(m_Texture, textCoordinate);
}