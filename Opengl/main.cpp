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


void key_callback(GLFWwindow* window, int key,int scancode,int action,int mods)
{
    if (key == GLFW_KEY_ESCAPE)
    {
        glfwSetWindowShouldClose(window,true);
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
         -0.5f , -0.5f ,0.0f,  0.0f , 0.0f,
          0.5f , -0.5f, 0.0f,  1.0f , 0.0f,
          0.5f  , 0.5f ,0.0f ,  1.0f , 1.0f,
         -0.5f  , 0.5f ,0.0f ,  0.0f , 1.0f,
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
    EBO EBO1(indices1,sizeof(indices1), 6);

    VAO1.AddAttrib(VBO1,0,3 ,GL_FLOAT,5*sizeof(GL_FLOAT),(void*)0);
    VAO1.AddAttrib(VBO1,1 ,2,GL_FLOAT,5*sizeof(GL_FLOAT),(void*)(3*(sizeof(GL_FLOAT))));
    VAO1.unbind();
    VBO1.unbind();
    EBO1.unbind();
   

    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    Texture  texture("tree.png");
    shaders.SetUniform1i("m_Texture",0);



    Renderer renderer;
    
    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window,true);
    ImGui::StyleColorsDark();

    glfwSwapBuffers(window);
    glm::vec3 translationA(0, 0, 0);
    glm::vec3 translationB(0, 0, 0);

    float angle = 0.0f;
    while (!glfwWindowShouldClose(window))
    {
        angle += 0.5f;
        renderer.Clear(0.2f,0.78f, 0.92f,1.0f);
        renderer.Clear();// clear the color buffer
        ImGui_ImplGlfwGL3_NewFrame();   

        glfwSetKeyCallback(window, key_callback);

        texture.bind();
        
        {

            ImGui::SliderFloat3("TranslationB", &translationB.x, -1.0f, 1.0f);        // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }

        
        {
            glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
            glm::mat4 mvp = rotate;
            shaders.SetUniformMat4("u_mvp", mvp);
            renderer.Draw(VAO1, EBO1, shaders);
        }

        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //delete
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
   
    shaders.Delete();
    texture.Delete(); 

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0 ; 
}