
#version 330 core
out vec4 FragColor;

in vec3 LightPos;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
void main()
{
    // this shader implemented Phong Shader
    
    float specularStrength = 0.5;
    float ambientStrength = 0.1;
    float shininess = 64;
    
    //ambient light
    vec3 ambient = ambientStrength * lightColor;
    
    //diffuse light
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPos - FragPos);
    float diff = max(dot(norm,lightDir),0.0);
    vec3 diffuse = diff * lightColor;
    //specualr light
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec= pow(max(dot(viewDir,reflectDir),0.0),shininess);
    vec3 specular = specularStrength * spec * lightColor;
    
    // Add three Together
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result,1.0);
}
