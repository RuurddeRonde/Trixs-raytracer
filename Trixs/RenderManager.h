#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw.h>
#include <imgui\imgui_impl_opengl3.h>
#include "Window.h"
namespace Trixs
{
	const unsigned int SCR_WIDTH = 1080;
	const unsigned int SCR_HEIGHT = 720;

	class UIManager;
	class RenderManager
	{
	public:
		RenderManager(Window* basewindow);
		~RenderManager();
		void render();
		bool WindowShouldClose();
		GLFWwindow* getWindow();
		unsigned int getFrame() { return framebuffer; }
		void framebufferSizeCallback(int width, int height);
		void setNewSize(int width, int height);
	private:
		int shaderProgram;
		Window* basewindow;
		unsigned int VBO, VAO, EBO, framebuffer;
		const char *vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"}\0";
		const char *fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"	FragColor = vec4(0.3,0.4,0.3, 1.0);\n"
			"}\n\0";
		float vertices[12] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
		};
		unsigned int indices[6] = {  // note that we start from 0!
			0, 1, 3,  // first Triangle
			1, 2, 3   // second Triangle
		};
	};

}