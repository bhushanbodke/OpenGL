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
        -0.5f , -0.5f, 0.0f, 1.0f,1.0f,1.0f, 0.0f , 0.0f,
        -0.5f ,  0.5f, 0.0f, 1.0f,1.0f,1.0f, 0.0f , 1.0f,
         0.5f ,  0.5f , 0.0f, 1.0f,1.0f,1.0f, 1.0f , 1.0f,
         0.5f , -0.5f , 0.0f, 1.0f,1.0f,1.0f, 1.0f , 0.0f,
    };

    GLuint indices1[] =
    {
        0,1,2,
        0,3,2,
    };

    GLFWwindow* window = glfwCreateWindow(800,600,"new window",NULL,NULL);
    if(window==NULL)
    {
        std::cout<< "failed to create window"<<std::endl;
        glfwTerminate();
        return - 1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    gladLoadGL();
    glViewport(0,0,800,600);

    GLCALL(glEnable(GL_BLEND));
    GLCALL(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA));

    // shaders
    Shader shaders("shaders/default.vert" , "shaders/default.frag");

    VAO VAO1;
    VAO1.bind();
    VBO VBO1(vertices1,sizeof(vertices1));
    EBO EBO1(indices1,sizeof(indices1), 6);

    VAO1.AddAttrib(VBO1,0 ,GL_FLOAT,8*sizeof(GL_FLOAT),(void*)0);
    VAO1.AddAttrib(VBO1,1 ,GL_FLOAT,8*sizeof(GL_FLOAT),(void*)(3*(sizeof(GL_FLOAT))));
    VAO1.AddAttrib(VBO1,2 ,GL_FLOAT,8*sizeof(GL_FLOAT),(void*)(6*(sizeof(GL_FLOAT))));
    VAO1.unbind();
    VBO1.unbind();
    EBO1.unbind();
    


   /* glm::mat4 proj = glm::ortho(-2.0, 2.0, -1.5, 1.5, -1.0, 1.0);

    shaders.SetUniformMat4("u_MVP", proj);*/

    Texture  texture("tree.png");
    //GLCALL(glUniform1f(glGetUniformLocation(shaders.ID, "scale"), 2.0f));
    shaders.SetUniform1i("m_Texture",0);


    Renderer renderer;
    float r = 0 ;
    float  increment = 0.5f;
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