#pragma once
#include "UIWindow.h"
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw.h>
#include <imgui\imgui_impl_opengl3.h>
#include <string>

namespace Trixs
{
	class ImGuiWindow :
		public UIWindow
	{
	public:
		ImGuiWindow();
		~ImGuiWindow();
		void update() override;
	protected:
		bool begin(std::string name);
		void end();
	};

}