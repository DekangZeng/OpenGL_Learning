



#version 330 core
out vec4 FragColor;

struct Material{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
struct Light{
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    // point light
    float cutOff;
    float outerCutOff;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;
void main()
{
    // this shader implemented Phong Shader
    vec3 lightDir = normalize(light.position - FragPos);
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp( (theta - light.outerCutOff) / epsilon, 0.0 , 1.0);
    
    //ambient light
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    
    //diffuse light
    vec3 norm = normalize(Normal);
  
    float diff = max(dot(norm,lightDir),0.0);
    vec3 diffuse = diff * light.diffuse * vec3(texture(material.diffuse,TexCoords));
    //specular light
    vec3 viewDir = normalize(viewPos-FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec= pow(max(dot(viewDir,reflectDir),0.0),material.shininess * 128);
    vec3 specular = spec * light.specular * vec3(texture(material.specular,TexCoords));
    
   
    // Add three Together
    vec3 result = (ambient + diffuse + specular) * intensity ;
    
   
   
    FragColor = vec4(result,1.0);
}
