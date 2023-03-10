#include "Utils.h"


float x = 0.0f;
float y = 0.0f;
float z = 3.0f;
float angle = 0.0f;
int ScreenWidth = 960;
int ScreenHeight = 540;
float deltaTime = 0.0f;
float LastFrame = 0.0f;

void resizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    ScreenWidth = width;
    ScreenHeight = height;
}


Camera camera({ 0.0f,0.0f,3.0f }, 3.0f, (float)ScreenWidth / ScreenHeight,45.0f, 0.1f, 100.0f);


void InputHandle(GLFWwindow *window)
{
    float dx = Mouse::GetDX();
    float dy = Mouse::GetDY();
    float scroll = Mouse::GetScrollDY();

    camera.UpdateCameraDir(dx, dy);
    camera.UpdateZoom(scroll);


    if (KeyBoard::key(GLFW_KEY_A))
    {
        camera.MoveLeft(deltaTime);
    }
    if (KeyBoard::key(GLFW_KEY_D))
    {
        camera.MoveRight(deltaTime);
    }
    if (KeyBoard::key(GLFW_KEY_S))
    {
        camera.MoveBack(deltaTime);
    }
    if (KeyBoard::key(GLFW_KEY_W))
    {
        camera.MoveFront(deltaTime);
    }
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

    //make fullscreen
    /*GLFWmonitor* moniter = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(moniter);
     
    ScreenWidth = mode->width;
    ScreenHeight = mode->height;*/

    GLFWwindow* window = glfwCreateWindow(ScreenWidth,ScreenHeight,"new window",NULL,NULL);
    if(window==nullptr)
    {
        std::cout<< "failed to create window"<<std::endl;
        glfwTerminate();
        return - 1;
    }
    //glfwSetWindowMonitor(window, moniter, 0, 0, mode->width, mode->height, mode->refreshRate);

    // Set cursor to hide in window
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    

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
   
   
    Texture  texture("block.png");
    shaders.SetUniform1i("m_Texture",0);

    glEnable(GL_DEPTH_TEST);

    Renderer renderer;
    
    glfwSetKeyCallback(window, KeyBoard::KeyCallback);
    glfwSetCursorPosCallback(window, Mouse::MouseCallback);
    glfwSetMouseButtonCallback(window, Mouse::MouseButtonCallback);
    glfwSetScrollCallback(window, Mouse::MouseWheelCallback);
    glfwSetFramebufferSizeCallback(window, resizeCallback);
    std::vector<glm::vec3> matrix = {
        glm::vec3(0.0f,  0.0f,  -3.0f),  
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)

    };
    int Frames = 0.0f;
    double lastFrame = glfwGetTime();
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - LastFrame;
        LastFrame = currentFrame;

        Frames++;

        FPS(currentFrame , lastFrame, Frames);


        renderer.Clear((float)18 / 255, (float)35 / 255,(float)59 / 255, 1.0f);
        renderer.Clear();// clear the color buffer

        texture.bind();
        //camera circle

        for (auto& val : matrix)
        {
        // model matrix for moving and rotating models
        glm::mat4 model = glm::translate(glm::mat4(1.0f), val);
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(-55.0f), glm::vec3(-0.5f,-0.5f,0.0f));
        // projection matrix for perspective view
        glm::mat4 projection = camera.GetPerspective();
        //Camera matrix i.e view matrix

        glm::mat4 view = camera.GetLookAt();
        // resulting MVP
        glm::mat4 MVP = projection * view * model;
        shaders.SetUniformMat4("MVP", MVP);

        renderer.DrawArrays(VAO1, shaders, 0, 36);
        }
       
        InputHandle(window);
       
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

