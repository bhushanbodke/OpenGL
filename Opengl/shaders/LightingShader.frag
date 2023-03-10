#version 330 core
out vec4 FragColor;

// input 


uniform vec3 lightingColor;
uniform vec3 objectColor;


void main()
{
    FragColor = vec4(objectColor * lightingColor,1.0);
}