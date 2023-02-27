#include<iostream>
#include "glad.h"
#include <GLFW/glfw3.h>

const char* vertexShaderSource =  "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"out vec4 vertexColor;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(aPos.x,aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* FragShaderSource =  "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(0.8f,0.3f,0.02f,1.0f);\n"
"}\n\0";


int main(void)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    // vertices of triangle
    GLfloat vertices[] = 
    {
        -0.25f , -0.25f , 0.0f,
        0.5 , -0.5 , 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
    };

    GLuint indices[] =
    {
        0,1,2,
        1,2,3,
    };

    GLFWwindow* window = glfwCreateWindow(800,600,"new window",NULL,NULL);
    if(window==NULL)
    {
        std::cout<< "failed to create window"<<std::endl;
        glfwTerminate();
        return - 1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0,0,800,600);

    // shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader , 1 ,&vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint FragementShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragementShader , 1 , &FragShaderSource ,NULL);
    glCompileShader(FragementShader);

    // shader program 
    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program , vertexShader);
    glAttachShader(shader_program , FragementShader);
    glLinkProgram(shader_program);

    glDeleteShader(FragementShader);
    glDeleteShader(vertexShader);

    //VBO is actual vertex data that is used for rendering
    //VAO is how the data is stored in the vertex buffer
    GLuint VAO ,VBO ,EBO;
    glGenVertexArrays(1, &VAO); // create a VAO 
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);

    glBindVertexArray(VAO);    // make the VAO current used for subsequant function calls
    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GL_FLOAT),(void*)0); // how the data is stored in the vertex buffer
    glEnableVertexAttribArray(0); //enable the attribute

    glBindBuffer(GL_ARRAY_BUFFER,0);  
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);  

    
    glfwSwapBuffers(window);
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f,0.0f,0.0f,1.0f); // make the background color
        glClear(GL_COLOR_BUFFER_BIT); // clear the color buffer
        glUseProgram(shader_program); //shader program to use 
        glDrawElements(GL_TRIANGLES ,6,GL_UNSIGNED_INT,0) ;// Draw the triangle
        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shader_program);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0 ; 
}