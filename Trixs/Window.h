#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <imgui\imgui.h>

class Window
{
public:
	Window(int width, int size);
	~Window();
	void update();
	void render();
	int getWidth() { return width; }
	int getHeight() { return height; }
	void setSize(int width, int height);
	GLFWwindow* getWindow() { return window; }
	void setWindow(GLFWwindow* window) { this->window = window; }
private:
	int width;
	int height;
	GLFWwindow* window;
};

