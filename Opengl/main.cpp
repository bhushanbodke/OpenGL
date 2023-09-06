#include "Utils.h"
#include "ParticlesSystem.h"
#include "Model.h"
#include "Cube.h"

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
   


    GLFWwindow* window = glfwCreateWindow(windowWidth,windowHeight,"Open GL",NULL,NULL);
    if(window==nullptr)
    {
        std::cout<< "failed to create window"<<std::endl;
        glfwTerminate();
        return - 1;
    }
    //glfwSetWindowMonitor(window, moniter, 0, 0, mode->width, mode->height, mode->refreshRate);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetWindowPos(window, 50, 50);


    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    gladLoadGL();
    glViewport(0, 0, ViewportWidth1, ViewportHeight1);

    GLCALL(glEnable(GL_BLEND));
    GLCALL(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA));

    // shaders
    Shader shader("shaders/LightingShader.vert", "shaders/LightingShader.frag");
    //texture
    Shader cubeShader("shaders/default.vert", "shaders/Light.frag");

    Model backpack("models/backpack/backpack.obj");
    Cube cube1;
    Cube cube2;

    glEnable(GL_DEPTH_TEST);
    
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
    
    int Frames = 0.0f;
    double lastFrame = glfwGetTime();
    float radius = 5.0f;
    glm::vec4 backColor(0,0,0,1.0f);

    glm::vec3 lightPos(0.0f, -0.4f, 0.0f);
    glm::vec3 lightCol(1.0f, 1.0f, 1.0f);

    glm::vec3 pointLightPositions[] = {
        glm::vec3(0.0f,  0.1f, -4.0f),
        glm::vec3(1.0f,  0.1f, -4.0f),
    };
    int rad = 5;
    float intensity = 1.0f;
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - LastFrame;
        LastFrame = currentFrame;

        Frames++;

        pointLightPositions[0].x = sin(currentFrame) * rad;
        pointLightPositions[0].z = cos(currentFrame) * rad;

        pointLightPositions[1].x = sin(currentFrame) * rad;
        pointLightPositions[1].y = cos(currentFrame) * rad;

        int fps = FPS(currentFrame, lastFrame, Frames);
        glfwSetWindowTitle(window,("FPS : " + std::to_string(fps) + "  Model Loading").c_str());


        // first view port
        {
            
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(backColor.r, backColor.g, backColor.b,backColor.a);


            shader.Activate();
             // model matrix for moving and rotating models
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
            model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
             // projection matrix for perspective view
             glm::mat4 projection = camera.GetPerspective();
             //Camera matrix i.e view matrix
             glm::mat4 view = camera.GetLookAt();

             glm::mat4 mvp = projection * view *  model;
             shader.SetUniformMat4("MVP", mvp);
             shader.SetUniformMat4("model",model);
             shader.SetUniformVec3("viewPos", camera.CamPos);

             shader.SetUniform1i("is_DirLights", 0);
             shader.SetUniform1i("is_PointLights", 1);
             shader.SetUniformVec3("point_lights[0].Pos", pointLightPositions[0]);
             shader.SetUniformVec3("point_lights[0].ambient", lightCol);
             shader.SetUniformVec3("point_lights[0].diffuse", lightCol);
             shader.SetUniformVec3("point_lights[0].specular", lightCol);
             shader.SetUniform1F("point_lights[0].intensity", intensity);

             shader.SetUniformVec3("point_lights[1].Pos", pointLightPositions[1]);
             shader.SetUniformVec3("point_lights[1].ambient", lightCol);
             shader.SetUniformVec3("point_lights[1].diffuse", lightCol);
             shader.SetUniformVec3("point_lights[1].specular", lightCol);
             shader.SetUniform1F("point_lights[1].intensity", intensity);

             backpack.Draw(shader);

             cubeShader.Activate();
             cube1.Draw(cubeShader, projection * view, pointLightPositions[0], lightCol);
             cube2.Draw(cubeShader,projection * view,pointLightPositions[1], lightCol);
             

           
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
            ImGui::DragFloat("Intensity", &intensity,0.50,0.0,50.0);

            ImGui::Text(("No of Triangles : " + std::to_string(backpack.NoTriangles)).c_str());
            ImGui::Text(("Draw Calls : " + std::to_string(backpack.GetMeshNo())).c_str());
            ImGui::ColorEdit4("Light Color", &lightCol.r);
           
            ImGui::End();
            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
            InputHandle(window);

        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    //delete
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0 ; 
}

