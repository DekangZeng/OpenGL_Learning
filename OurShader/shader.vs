#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 ourColor;
uniform float shift;
void main()
{
   gl_Position = vec4(aPos.x+shift,aPos.y+shift,aPos.z, 1.0);
   ourColor = vec3(aColor.x+shift,aColor.y+shift,aColor.z+shift);
}
