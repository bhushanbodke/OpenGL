#pragma once
#include<iostream>
#include "glad.h"
#include <GLFW/glfw3.h>
#include <string>
#include<fstream>
#include <iostream>
#include <sstream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Imgui/imgui.h>
#include <Imgui/imgui_impl_glfw_gl3.h>
#include <Tests/TestClearColor.h>
#include <vector>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include "ShaderClass.h"
#include "errorhandle.h"
#include "glm/glm.hpp"
#include "KeyBoard.h"
#include "Mouse.h"
#include "Camera.h"


int FPS(float currentFrame,double& LastFrame, int& frames);
void ToggleHideMouse(GLFWwindow* window);