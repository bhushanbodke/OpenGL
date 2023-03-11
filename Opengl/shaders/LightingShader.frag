#version 330 core
out vec4 FragColor;

// input 
in vec3 FragPos;
in vec3 Normal;

struct Material
{
    vec3 Ambient;
    vec3 Diffuse;
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
    vec3 diffuse =  light.Diffuse * (diff * material.Diffuse);

    //Ambient Lighting
    vec3 ambient = light.Ambient * material.Ambient;

    //Specular Lighting
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir,norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.Shininess);
    vec3 specular = light.Specular * (spec * material.Specular);

    //result 
    vec3 result = ambient + diffuse + specular; 
    FragColor = vec4(result,1.0);
}