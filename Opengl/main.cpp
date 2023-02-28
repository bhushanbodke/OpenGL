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


int main(void)
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    // vertices of triangle
    GLfloat vertices1[] = 
    {
         100.0f , 100.0f , 0.0f , 0.0f,
         300.0f , 100.0f, 1.0f , 0.0f,
         300.0f , 300.0f , 1.0f , 1.0f,
         100.0f , 300.0f , 0.0f , 1.0f,
    };

    GLuint indices1[] =
    {
        0,1,2,
        2,3,0
    };
    float ScreenWidth, ScreenHeight;
    ScreenWidth = 960.f;
    ScreenHeight = 540.f;
    GLFWwindow* window = glfwCreateWindow(ScreenWidth,ScreenHeight,"new window",NULL,NULL);
    if(window==NULL)
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
    EBO EBO1(indices1,sizeof(indices1), 6);

    VAO1.AddAttrib(VBO1,0,2 ,GL_FLOAT,4*sizeof(GL_FLOAT),(void*)0);
    VAO1.AddAttrib(VBO1,1 ,2,GL_FLOAT,4*sizeof(GL_FLOAT),(void*)(2*(sizeof(GL_FLOAT))));
    VAO1.unbind();
    VBO1.unbind();
    EBO1.unbind();
    


    glm::mat4 proj = glm::ortho(0.0f , ScreenWidth,0.0f, ScreenHeight, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(200, 0, 0));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(100, 100, 0));

    glm::mat4 mvp = proj * view * model;
    shaders.SetUniformMat4("u_mvp", mvp);

    Texture  texture("tree.png");
    shaders.SetUniform1i("m_Texture",0);

    Renderer renderer;
    glfwSwapBuffers(window);

    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear(0.07f, 0.13f , 0.17f ,1.0f);
        renderer.Clear();    // clear the color buffer
        texture.bind();
        renderer.Draw(VAO1, EBO1, shaders);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //delete
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
   
    shaders.Delete();
    texture.Delete(); 

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0 ; 
}