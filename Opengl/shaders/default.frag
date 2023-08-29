#version 330 core
out vec4 FragColor;

// input 

in vec2 textCoordinate;

uniform sampler2D m_Texture1;
uniform sampler2D m_Texture2;
uniform sampler2D m_Texture3;


void main()
{
    FragColor = mix(texture(m_Texture1, textCoordinate),texture(m_Texture2,textCoordinate),0.5);
    FragColor = mix(FragColor,texture(m_Texture3,textCoordinate),0.2);
}