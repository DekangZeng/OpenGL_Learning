


#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;

out vec3 OurColor;

void main()
{
    //Gouraud Shading Implemented
    
    gl_Position =   projection * view * model * vec4(aPos, 1.0);
    vec3 Pos = vec3(model * vec4(aPos,1.0));
    vec3 Normal = mat3(transpose(inverse(model))) * aNormal;
    
    float specularStrength = 0.5;
    float ambientStrength = 0.1;
    float shininess = 32;
    
    //ambient light
    vec3 ambient = ambientStrength * lightColor;
    
    //diffuse light
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - Pos);
    float diff = max(dot(norm,lightDir),0.0);
    vec3 diffuse = diff * lightColor;
    //specualr light
    vec3 viewDir = normalize(viewPos-Pos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec= pow(max(dot(viewDir,reflectDir),0.0),shininess);
    vec3 specular = specularStrength * spec * lightColor;
    
    // Add three Together
    vec3 result = (ambient + diffuse + specular);
    OurColor = result;
}
