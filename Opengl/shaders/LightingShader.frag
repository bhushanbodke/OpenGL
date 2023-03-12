#version 330 core
out vec4 FragColor;

// input 
in vec3 FragPos;
in vec3 Normal;
in vec2 TextCoord;

struct Material
{
    sampler2D Diffuse;
    vec3 Specular;
    float Shininess;
};

struct Light
{
    vec3 Pos;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};

uniform Light light;
uniform Material material;

uniform vec3 viewPos;


void main()
{
    
    int shine = 256;

    // Diffuse Lighting 
    vec3 norm = normalize(Normal);
    vec3 lightDir =normalize(light.Pos - FragPos);
    float diff = max(dot(norm,lightDir),0.0);
    vec3 diffuse =  light.Diffuse * diff *vec3(texture(material.Diffuse , TextCoord));

    //Ambient Lighting
    vec3 ambient = light.Ambient * vec3(texture(material.Diffuse , TextCoord));;

    //Specular Lighting
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir,norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.Shininess);
    vec3 specular = light.Specular * (spec * material.Specular);

    //result 
    vec3 result = ambient + diffuse + specular; 
    FragColor = vec4(result,1.0);
}