#include "Utils.h"

float x = 0.0f;
float y = 0.0f;
float z = 3.0f;
float angle = 0.0f;
int windowWidth = 1275;
int windowHeight = 600;
int ViewportWidth1 = ((float)75 / 100) * windowWidth;
int ViewportHeight1 =windowHeight;
int viewportWidth2 = (windowWidth - ViewportWidth1) < 100?100: (windowWidth - ViewportWidth1);
int viewportHeight2 = windowHeight;
bool changeImgui = true;
float deltaTime = 0.0f;
float LastFrame = 0.0f;

void resizeCallback(GLFWwindow* window, int width, int height)
{
    windowWidth = width;
    windowHeight = height;
    ViewportWidth1 = ((float)75 / 100) * windowWidth;
    ViewportHeight1 = windowHeight;
    viewportWidth2 = (windowWidth - ViewportWidth1) < 100 ? 100 : (windowWidth - ViewportWidth1);
    viewportHeight2 = windowHeight;
    glViewport(0, 0, ViewportWidth1, ViewportHeight1);
    changeImgui = true;
}


Camera camera({ 0.0f,0.0f,3.0f }, 3.0f, (float)ViewportWidth1 / ViewportHeight1,45.0f, 0.1f, 100.0f);
float SpeedMultiplier = 1.0f;

void InputHandle(GLFWwindow *window)
{
    float dx = Mouse::GetDX();
    float dy = Mouse::GetDY();
    float scroll = Mouse::GetScrollDY();

    
    
    if (KeyBoard::keyWentDown(GLFW_KEY_LEFT_CONTROL))
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    if (KeyBoard::keyWentUp(GLFW_KEY_LEFT_CONTROL))
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    if (!KeyBoard::key(GLFW_KEY_LEFT_CONTROL))
    {
        if(KeyBoard::key(GLFW_KEY_LEFT_SHIFT))
        {
            SpeedMultiplier = 2.0f;
        }
        else
        {
            SpeedMultiplier = 1.0f;
        }
        camera.UpdateCameraDir(dx, dy);
        camera.UpdateZoom(scroll);
        if (KeyBoard::key(GLFW_KEY_SPACE))
        {
            camera.MoveUp(deltaTime, SpeedMultiplier);
        }
        if (KeyBoard::key(GLFW_KEY_LEFT_ALT))
        {
            camera.MoveDown(deltaTime, SpeedMultiplier);
        }
        if (KeyBoard::key(GLFW_KEY_A))
        {
            camera.MoveLeft(deltaTime , SpeedMultiplier);
        }
        if (KeyBoard::key(GLFW_KEY_D))
        {
            camera.MoveRight(deltaTime , SpeedMultiplier);
        }
        if (KeyBoard::key(GLFW_KEY_S))
        {
            camera.MoveBack(deltaTime, SpeedMultiplier);
        }
        if (KeyBoard::key(GLFW_KEY_W))
        {
            camera.MoveFront(deltaTime, SpeedMultiplier);
        }
        if (KeyBoard::key(GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(window, true);
        }

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
       //vertex data       // Normals       //text cordinate
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f , 0.0f,
     0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f , 0.0f, 
     0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f , 1.0f,
     0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0  , 1.0f,  
    -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f , 1.0f,  
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f , 0.0f,

    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,  0.0f , 0.0f,
     0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,  1.0f , 0.0f, 
     0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,  1.0f , 1.0f,
     0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,  1.0  , 1.0f, 
    -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,  0.0f , 1.0f, 
    -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,  0.0f , 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

     0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f,-1.0f, 0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 0.0f,-1.0f, 0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 0.0f,-1.0f, 0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 0.0f,-1.0f, 0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 0.0f,-1.0f, 0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f,-1.0f, 0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  0.0f, 1.0f,

    };

    //make fullscreen
    /*GLFWmonitor* moniter = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(moniter);
     
    ScreenWidth = mode->width;
    ScreenHeight = mode->height;*/

    GLFWwindow* window = glfwCreateWindow(windowWidth,windowHeight,"Open GL",NULL,NULL);
    if(window==nullptr)
    {
        std::cout<< "failed to create window"<<std::endl;
        glfwTerminate();
        return - 1;
    }
    //glfwSetWindowMonitor(window, moniter, 0, 0, mode->width, mode->height, mode->refreshRate);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowPos(window, 50, 50);


    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    gladLoadGL();
    glViewport(0, 0, ViewportWidth1, ViewportHeight1);

    GLCALL(glEnable(GL_BLEND));
    GLCALL(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA));

    // shaders
    Shader shaders1("shaders/default.vert", "shaders/default.frag");
    //texture 
    Texture block("woodBlock.png");
    Texture blockEdge("blockEdge.png");
    Texture Tree("tree.png");

    VAO VAO1;
    VAO1.bind();
    VBO VBO1(vertices1,sizeof(vertices1));

    VAO1.AddAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(GL_FLOAT), (void*)0);
    VAO1.AddAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
    VAO1.AddAttrib(VBO1,2,2 ,GL_FLOAT,8*sizeof(GL_FLOAT),(void*)(6 * sizeof(GL_FLOAT)));
    VAO1.unbind();
    VBO1.unbind();
   

    glEnable(GL_DEPTH_TEST);
    // depth test always pass in this 
    //glDepthFunc(GL_ALWAYS);

    Renderer renderer;
    
    ImGui::CreateContext();

    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 0.0f;

    ImGui::SetNextWindowPos(ImVec2(ViewportWidth1, 0), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(viewportWidth2, viewportHeight2), ImGuiCond_FirstUseEver);

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
        glm::vec3(-3.8f, -2.0f, -9.3f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -5.5f)

    };
    int Frames = 0.0f;
    double lastFrame = glfwGetTime();
    float radius = 5.0f;
    glm::vec4 backColor(0.5f,0.5f,0.5f,1.0f);

    glm::vec3 lightPos(0.0f, -0.4f,0.0f);
    glm::vec3 lightCol(1.0f, 1.0f, 1.0f);

    float Shininess = 32.0f;
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - LastFrame;
        LastFrame = currentFrame;

        Frames++;

        float fps = FPS(currentFrame, lastFrame, Frames);

        // first view port
        {
            
            renderer.Clear(backColor.r,backColor.g,backColor.b,backColor.a);
            renderer.Clear();// clear the color buffer

            shaders1.Activate();
            block.bind(0);
            blockEdge.bind(1);
            Tree.bind(2);

            shaders1.SetUniform1i("m_Texture1", 0);
            shaders1.SetUniform1i("m_Texture2", 1);
            shaders1.SetUniform1i("m_Texture3", 2);

            for (auto& val : matrix)
            {
                // model matrix for moving and rotating models
                glm::mat4 model = glm::translate(glm::mat4(1.0f), val);
                // projection matrix for perspective view
                glm::mat4 projection = camera.GetPerspective();
                //Camera matrix i.e view matrix

                glm::mat4 view = camera.GetLookAt();
                // resulting MVP
                glm::mat4 MVP = projection * view * model;

                shaders1.SetUniformMat4("MVP", MVP);

                renderer.DrawArrays(VAO1, 0, 36);
            }

        }
        //Imgui View port

        {
            ImGui_ImplGlfwGL3_NewFrame();
            
            if (changeImgui)
            {
                ImGui::SetNextWindowPos(ImVec2(ViewportWidth1, 0));
                ImGui::SetNextWindowSize(ImVec2(viewportWidth2, viewportHeight2));
                changeImgui = false;
            }
            ImGui::Begin("window");
            
            ImGui::ColorEdit4("BackGround Color", &backColor.r);
            ImGui::ColorEdit3("Light Color", &lightCol.r);
            ImGui::SliderFloat("Shininess", &Shininess, 256.0f, 10.0f);
           
            ImGui::End();
            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
            InputHandle(window);

        }

        VAO1.unbind();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //delete
    VAO1.Delete();
    VBO1.Delete();
   
    shaders1.Delete();

    block.Delete();
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0 ; 
}

