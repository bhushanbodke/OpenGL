#pragma once
#include "Test.h"

namespace test
{
	class TestClearColor : public Test
	{
	public:
		float u_Color[4] = {};
		
		TestClearColor();
		~TestClearColor() override;

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void ImguiRender() override;
	};
}
