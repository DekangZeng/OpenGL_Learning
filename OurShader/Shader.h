//
//  Shader.h
//  OpenGL_Template
//
//  Created by 曾德康 on 1/13/22.
//

#ifndef SHADER_H
#define SHADER_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

class Shader
{
public:
    
    unsigned int ID;
    
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    
    void use();
    
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name,int value) const;
    void setFloat(const std::string &name, float value)const;
    
};

#endif /* Shader_h */
