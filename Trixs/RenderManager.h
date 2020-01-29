#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw.h>
#include <imgui\imgui_impl_opengl3.h>
#include "Window.h"
#include "Shader.h"
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
		unsigned int getFrame() { return textureColorbuffer; }
		void framebufferSizeCallback(int width, int height);
		void setNewSize(int width, int height);
	private:
		int shaderProgram;

		Window* basewindow;
		unsigned int VBO, VAO, EBO, framebuffer, textureColorbuffer;
		int width, height;
		Shader* shader;


		//depreciated
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

		//grid
		float vertices[60] = {
			//vertical
		 -2.0f, 0.0f, 3.0f,
		 -2.0f, 0.0f,-3.0f,
		 -1.0f, 0.0f, 3.0f,
		 -1.0f,0.0f, -3.0f,
		 0.0f, 0.0f, 3.0f,
		 0.0f,0.0f, -3.0f,
		 1.0f, 0.0f, 3.0f,
		 1.0f, 0.0f,-3.0f,
		 2.0f, 0.0f, 3.0f,
		 2.0f, 0.0f,-3.0f,
		 //horizontal
		 //x y z
		 -3.0f, 0.0f,2.0f,
		 3.0f, 0.0f, 2.0f,
		 -3.0f,0.0f, 1.0f,
		 3.0f,0.0f, 1.0f,
		 -3.0f,0.0f, 0.0f,
		 3.0f, 0.0f,0.0f,
		 -3.0f, 0.0f,-1.0f,
		 3.0f, 0.0f,-1.0f,
		 -3.0f,0.0f, -2.0f,
		 3.0f, 0.0f,-2.0f,

		};
		unsigned int indices[20] = {  // note that we start from 0!
			0,1,
			2,3,
			4,5,
			6,7,
			8,9,
			10,11,
			12,13,
			14,15,
			16,17,
			18,19
		};
		void drawGrid();
	};

}