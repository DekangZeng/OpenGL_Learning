#include<iostream>
#include<math.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    //glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3); // set OPENGL major version 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //set OPENGL sub version 0.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // OPENGL CORE-PROFILE
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //  may need in MAX OS X
    
    
    //glfw window creation
    GLFWwindow *window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);
    if(window==NULL)
    {
        std::cout<<"Failed to create GLFW window"<<std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    //glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0,0,800,600);
    
    //GLSL
    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec3 aColor;\n"
        "out vec3 ourColor;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos, 1.0);\n"
        "   ourColor = aColor;\n"
        "}\0";
    //compile vertex shader
    unsigned int vertexShader;
    vertexShader=glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1, &vertexShaderSource,NULL);
    glCompileShader(vertexShader);
   
    
    // check vertex shader
    
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    //Fragment Shader
    const char *fragmentShaderSouce = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec3 ourColor;\n"
        "void main()\n"
        "{\n"
        "FragColor = vec4(ourColor,1.0);\n"
    "}\n";
    // compile fragment shader
    
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSouce,NULL);
    glCompileShader(fragmentShader);
    
    
    //shader program
    
    unsigned int ShaderProgram;
    ShaderProgram=glCreateProgram();
    
    //link shader with program
    glAttachShader(ShaderProgram,vertexShader);
    glAttachShader(ShaderProgram,fragmentShader);
    glLinkProgram(ShaderProgram);
    
    //check shader program
    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(ShaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::GROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    // data input
    float vertices[] ={
        0.5f, -0.5f, 0.0f, 1.0f,0.0f,0.0f,   // 右下角
       -0.5f, -0.5f, 0.0f, 0.0f,1.0f,0.0f,  // 左下角
        0.0f,  0.5f, 0.0f, 0.0f,0.0f,1.0f   // 顶部
        
    };
    unsigned int indices[]={
        0,1,3,
        1,2,3
    };
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    
    glGenBuffers(1,&VBO);
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
    //vertex shader
    

    
    //link vertex
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    
    //link color
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
    //glBindBuffer(GL_ARRAY_BUFFER,0);
    //glBindVertexArray(0);

    
    //use shader program
   
    //render loop
    while(!glfwWindowShouldClose(window))
    {
        //input
        processInput(window);
        
        //render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        
        //update uniform color
        //float timeValue = glfwGetTime();
       // float greenValue = sin(timeValue)/2.0f+0.5f;
        //int vertexColorLocation = glGetUniformLocation(ShaderProgram,"ourColor");
       // glUniform4f(vertexColorLocation,0.0f,greenValue,0.0f,1.0f);
        //draw our first triangle
        glUseProgram(ShaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,3);
        //glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        //glBindVertexArray(0);
        //glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwPollEvents();
        glfwSwapBuffers(window);
       
    }
    
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}


