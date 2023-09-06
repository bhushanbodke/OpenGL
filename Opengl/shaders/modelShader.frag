#version 330 core
out vec4 FragColor;

in vec2 TextCoord;

uniform sampler2D texture_diffuse1;

void main()
{    
    FragColor = texture(texture_diffuse1, TextCoord);
}