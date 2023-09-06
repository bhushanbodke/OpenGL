#version 330 core
out vec4 FragColor;

// input 

in vec2 textCoordinate;

uniform sampler2D m_Texture1;
uniform sampler2D m_Texture2;


void main()
{
    FragColor = mix(texture(m_Texture1, textCoordinate),texture(m_Texture2,textCoordinate),0.5);
}