#include <iostream>
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw.h>
#include <imgui\imgui_impl_opengl3.h>

#include "MainManager.h"

int main()
{
	Trixs::MainManager main;
	main.run();
	return 0;
}
