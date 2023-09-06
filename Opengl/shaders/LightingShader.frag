#version 330 core
out vec4 FragColor;

// input 
const int num_point_lights = 2 ;

in vec3 FragPos;
in vec3 Normal;
in vec2 TextCoord;

const int max_diffuse_textures = 10 ;
const int max_specular_textures = 10 ;

const float constant = 1.0f;
const float linear = 0.9f;
const float quadratic = 0.032f;
float cutoff = 0.9366f;


struct Material
{
    sampler2D texture_diffuse[max_diffuse_textures];
    sampler2D texture_specular[max_specular_textures];
    int num_specular_textures;
    int num_diffuse_textures;
    float Shininess;
};

struct DirLight
{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 Pos;
    vec3 diffuse; 
    vec3 specular; 
    vec3 ambient;
    float intensity;
};

struct Light
{
    vec3 Pos;
    vec3 Direction;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};


uniform int is_DirLights;
uniform int is_PointLights;
uniform Light light;
uniform Material material;
uniform DirLight dirlight;
uniform PointLight point_lights[num_point_lights];

uniform vec3 viewPos;


vec3 CalPointLight(PointLight light, vec3 normal ,vec3 FragPos ,  vec3 viewDir)
{
    vec3 lightDir   = normalize(light.Pos - FragPos);
    float diff      = max(dot(normal,lightDir),0.0);
    vec3 reflectDir = reflect(-lightDir , normal);
    float spec      = pow(max(dot(viewDir,reflectDir),0.0),material.Shininess);
    float dist      = length(light.Pos - FragPos);
    float attenuation = 1.0/(constant+linear*dist+quadratic*(dist*dist));
    vec3 ambient    = vec3(0);
    vec3 diffuse    = vec3(0);
    vec3 specular   = vec3(0);
    for (int i = 0 ; i < material.num_diffuse_textures;i++)
    {
        ambient += light.ambient * vec3(texture(material.texture_diffuse[i],TextCoord)) * light.intensity;
        diffuse += light.diffuse * diff * vec3(texture(material.texture_diffuse[i],TextCoord)) *light.intensity;
    }
    for(int i = 0 ; i < material.num_specular_textures;i++)
    {
        specular += light.specular * spec * vec3(texture(material.texture_specular[i],TextCoord))*light.intensity;
    }
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + specular + diffuse);
}

vec3 CalDirLight(DirLight light , vec3 normal , vec3 viewDir)
{   
    vec3 lightDir   = normalize(-light.direction);
    float diff      =  max(dot(normal , lightDir),0.0);
    vec3 reflectDir = reflect(-lightDir ,normal);
    float spec      = pow(max(dot(viewDir,reflectDir),0.0),material.Shininess);
    vec3 ambient    = vec3(0);
    vec3 diffuse    = vec3(0);
    vec3 specular   = vec3(0);
    for (int i = 0 ; i < material.num_diffuse_textures;i++)
    {
        ambient += light.ambient * vec3(texture(material.texture_diffuse[i],TextCoord));
        diffuse += light.diffuse * diff * vec3(texture(material.texture_diffuse[i],TextCoord));
    }
    for(int i = 0 ; i < material.num_specular_textures;i++)
    {
        specular += light.specular * spec * vec3(texture(material.texture_specular[i],TextCoord));
    }
    return (ambient + diffuse + specular);
}


void main()
{
    vec3 lightDir =normalize(light.Pos - FragPos);
    vec3 norm = normalize(Normal);
    vec3 viewDir =normalize(viewPos - FragPos);

    vec3 result = vec3(0);    
    if(is_DirLights == 1)
        // calculations for Directional lights
        vec3 result = CalDirLight(dirlight , norm , viewDir);
    // calculations for point lights 
    if(is_PointLights == 1)
    {
        for(int i = 0 ; i < num_point_lights;i++)
            result += CalPointLight(point_lights[i],norm,FragPos,viewDir);
    }

    FragColor = vec4(result,1.0);          

}