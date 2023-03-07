#include<iostream>
#include "glad.h"
#include <GLFW/glfw3.h>
#include <string>
#include<fstream>
#include <iostream>
#include <sstream>
#include "ShaderClass.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "errorhandle.h"
#include "renderer.h"
#include  "texture.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Imgui/imgui.h>
#include <Imgui/imgui_impl_glfw_gl3.h>
#include <Tests/TestClearColor.h>
#include "KeyBoard.h"
#include "Mouse.h"





void resizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


float increment = 0.05f;

void InputHandle(GLFWwindow *window)
{
    
    if (KeyBoard::key(GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(window, true);
    }
}

int main(void)
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    // vertices of triangle
   GLfloat vertices1[] = 
    {
     -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f

    };

   
    
    float ScreenWidth = 960.0f;
    float ScreenHeight = 540.f;
    GLFWwindow* window = glfwCreateWindow(ScreenWidth,ScreenHeight,"new window",NULL,NULL);
    if(window==nullptr)
    {
        std::cout<< "failed to create window"<<std::endl;
        glfwTerminate();
        return - 1;
    }
    

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    gladLoadGL();
    glViewport(0,0,ScreenWidth,ScreenHeight);

    GLCALL(glEnable(GL_BLEND));
    GLCALL(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA));

    // shaders
    Shader shaders("shaders/default.vert" , "shaders/default.frag");

    VAO VAO1;
    VAO1.bind();
    VBO VBO1(vertices1,sizeof(vertices1));

    VAO1.AddAttrib(VBO1,0,3 ,GL_FLOAT,5*sizeof(GL_FLOAT),(void*)0);
    VAO1.AddAttrib(VBO1,1,2,GL_FLOAT,5*sizeof(GL_FLOAT),(void*)(3*(sizeof(GL_FLOAT))));
    VAO1.unbind();
    VBO1.unbind();
   
    float x = 0.0f;
    float y = 0.0f;
    float z = 3.0f;
    float angle = 0.0f;
    

    

   
    Texture  texture("block.png");
    shaders.SetUniform1i("m_Texture",0);

    glEnable(GL_DEPTH_TEST);

    Renderer renderer;
    
    glfwSetKeyCallback(window, KeyBoard::KeyCallback);
    glfwSetCursorPosCallback(window, Mouse::MouseCallback);
    glfwSetMouseButtonCallback(window, Mouse::MouseButtonCallback);
    glfwSetScrollCallback(window, Mouse::MouseWheelCallback);
    glfwSetFramebufferSizeCallback(window, resizeCallback);

    while (!glfwWindowShouldClose(window))
    {
        angle += increment;
        renderer.Clear((float)18 / 255, (float)35 / 255,(float)59 / 255, 1.0f);
        renderer.Clear();// clear the color buffer

        glm::mat4 model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime() * glm::radians(-55.0f), glm::vec3(-0.5f,-0.5f,0.0f));
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-x,-y,-z));
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)ScreenWidth /(float)ScreenHeight, 0.1f, 100.0f);

       
        InputHandle(window);
        texture.bind();
        
        glm::mat4 MVP = projection * view * model;
        shaders.SetUniformMat4("MVP", MVP);
        
        renderer.DrawArrays(VAO1,shaders,0,36);
        VAO1.unbind();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //delete
    VAO1.Delete();
    VBO1.Delete();
   
    shaders.Delete();
    texture.Delete(); 

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0 ; 
}