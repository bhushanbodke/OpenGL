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

    if (KeyBoard::key(GLFW_KEY_SPACE))
    {
        camera.MoveUp(deltaTime);
    }
    if (KeyBoard::key(GLFW_KEY_LEFT_ALT))
    {
        camera.MoveDown(deltaTime);
    }
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
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
     0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,  
     0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,  
     0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,  
    -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,  
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,  

    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,  
     0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,  
     0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,  
     0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,  
    -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,  
    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,  

    -0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f, 
    -0.5f,  0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 
    -0.5f, -0.5f,  0.5f, -1.0f, 0.0f, 0.0f, 
    -0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f, 

     0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f,-1.0f, 0.0f,
     0.5f, -0.5f, -0.5f, 0.0f,-1.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 0.0f,-1.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 0.0f,-1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 0.0f,-1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f,-1.0f, 0.0f,

    -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,

    };

    //make fullscreen
    /*GLFWmonitor* moniter = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(moniter);
     
    ScreenWidth = mode->width;
    ScreenHeight = mode->height;*/

    GLFWwindow* window = glfwCreateWindow(ScreenWidth,ScreenHeight,"Open GL",NULL,NULL);
    if(window==nullptr)
    {
        std::cout<< "failed to create window"<<std::endl;
        glfwTerminate();
        return - 1;
    }
    //glfwSetWindowMonitor(window, moniter, 0, 0, mode->width, mode->height, mode->refreshRate);

    // Set cursor to hide in window
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    gladLoadGL();
    glViewport(0,0,ScreenWidth,ScreenHeight);

    GLCALL(glEnable(GL_BLEND));
    GLCALL(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA));

    // shaders
    Shader shaders1("shaders/LightingShader.vert", "shaders/LightingShader.frag");
    Shader shaders2("shaders/LightingShader.vert" , "shaders/Light.frag");

    VAO VAO1;
    VAO1.bind();
    VBO VBO1(vertices1,sizeof(vertices1));

    VAO1.AddAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(GL_FLOAT), (void*)0);
    VAO1.AddAttrib(VBO1,1,3 ,GL_FLOAT,6*sizeof(GL_FLOAT),(void*)(3 * sizeof(GL_FLOAT)));
    VAO1.unbind();
    VBO1.unbind();
   

    glEnable(GL_DEPTH_TEST);

    Renderer renderer;
    
    ImGui::CreateContext();

    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();

    glfwSetKeyCallback(window, KeyBoard::KeyCallback);
    glfwSetCursorPosCallback(window, Mouse::MouseCallback);
    glfwSetMouseButtonCallback(window, Mouse::MouseButtonCallback);
    glfwSetScrollCallback(window, Mouse::MouseWheelCallback);
    glfwSetFramebufferSizeCallback(window, resizeCallback);
    std::vector<glm::vec3> matrix = {
        glm::vec3(0.0f,  0.0f,  -3.0f),  
        glm::vec3(2.0f,  5.0f, -3.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -4.3f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -5.5f)

    };
    int Frames = 0.0f;
    double lastFrame = glfwGetTime();
    float radius = 5.0f;
    glm::vec3 lightPos(0.0f, -0.4f,0.0f);
    glm::vec3 lightCol(0.5f, 0.5f, 0.5f);

    glm::vec3 objectColor(0.75f,0.20f,0.10f);
    float Shininess = 256.0f;
    while (!glfwWindowShouldClose(window))
    {
        ImGui_ImplGlfwGL3_NewFrame();

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - LastFrame;
        LastFrame = currentFrame;

        Frames++;

        float fps  = FPS(currentFrame , lastFrame, Frames);

        renderer.Clear((float)18 / 255, (float)35 / 255,(float)59 / 255, 1.0f);
        renderer.Clear();// clear the color buffer

        {
            shaders1.Activate();

            shaders1.SetUnifromVec3("viewPos", camera.CamPos.x, camera.CamPos.y, camera.CamPos.z);
            shaders1.SetUnifromVec3("material.Ambient", objectColor.r, objectColor.g, objectColor.b);
            shaders1.SetUnifromVec3("material.Diffuse", objectColor.r, objectColor.g, objectColor.b);
            shaders1.SetUnifromVec3("material.Specular", 0.628281f	,0.555802f,	0.366065f);
            shaders1.setUnifrom1F("material.Shininess", Shininess);
            //
            shaders1.SetUnifromVec3("light.Pos", lightPos.x, lightPos.y, lightPos.z);
            shaders1.SetUnifromVec3("light.Ambient", 0.2f, 0.2f, 0.2f);
            shaders1.SetUnifromVec3("light.Diffuse", lightCol.r, lightCol.g, lightCol.b);
            shaders1.SetUnifromVec3("light.Specular", 1.0f, 1.0f, 1.0f);



            for (auto& val : matrix)
            {
                // model matrix for moving and rotating models
                glm::mat4 model = glm::translate(glm::mat4(1.0f), val);
                //model = glm::rotate(model, (float)glfwGetTime() * glm::radians(-55.0f), glm::vec3(-0.5f, -0.5f, 0.0f));
                // projection matrix for perspective view
                glm::mat4 projection = camera.GetPerspective();
                //Camera matrix i.e view matrix

                glm::mat4 view = camera.GetLookAt();
                // resulting MVP
                glm::mat4 MVP = projection * view * model;

                shaders1.SetUniformMat4("MVP", MVP);
                shaders1.SetUniformMat4("model", model);

                renderer.DrawArrays(VAO1, 0, 36);
            }
        }
        shaders2.Activate();
        shaders2.SetUnifromVec3("LightColor", lightCol.r, lightCol.g, lightCol.b);
        glm::mat4 model = glm::translate(glm::mat4(1.0f), lightPos);
        glm::mat4 projection = camera.GetPerspective();
        glm::mat4 view = camera.GetLookAt();
        auto MVP = projection * view * model;
        shaders2.SetUniformMat4("MVP", MVP);
        renderer.DrawArrays(VAO1, 0, 36);

        {
            ImGui::Begin("window");
            ImGui::ColorEdit3("Light Color", &lightCol.r);
            ImGui::ColorEdit3("Object Color", &objectColor.r);
            ImGui::SliderFloat("Shininess", &Shininess, 256.0f, 10.0f);
            ImGui::End();

        }
        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
        InputHandle(window);
        
        VAO1.unbind();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //delete
    VAO1.Delete();
    VBO1.Delete();
   
    shaders1.Delete();
    shaders2.Delete();

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0 ; 
}

