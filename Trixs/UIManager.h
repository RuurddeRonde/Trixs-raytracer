#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw.h>
#include <imgui\imgui_impl_opengl3.h>
#include "Window.h"
namespace Trixs
{
	class RenderManager;
	class UIManager
	{
	public:
		UIManager(Window* window);
		~UIManager();
		virtual void update() = 0;
		virtual void render() = 0;
		virtual	void initWindows(Window* window) = 0;
	private:
	};

}
