

#version 330 core
out vec4 FragColor;

in vec3 OurColor;

uniform vec3 objectColor;
void main()
{
    FragColor = vec4(OurColor * objectColor,1.0);
}
