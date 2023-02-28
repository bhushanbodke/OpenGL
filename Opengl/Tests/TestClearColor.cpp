#include "TestClearColor.h"
#include "errorhandle.h"
#include <Imgui/imgui.h>
#include <Imgui/imgui_impl_glfw_gl3.h>

namespace test
{
	TestClearColor::TestClearColor()
		:u_Color{0.2f,0.3,0.8f,1.0}
	{

	}
	TestClearColor::~TestClearColor()
	{

	}
	void TestClearColor::OnUpdate(float deltaTime)
	{
		
	}
	void TestClearColor::OnRender()
	{
		GLCALL(glClearColor(u_Color[0], u_Color[1], u_Color[2], u_Color[3]));
		GLCALL(glClear(GL_COLOR_BUFFER_BIT));
	}
	void TestClearColor::ImguiRender()
	{
		ImGui::ColorEdit4("Clear Colour", u_Color);
	}
}