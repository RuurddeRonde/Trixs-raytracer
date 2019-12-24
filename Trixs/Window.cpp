#include "Window.h"


Window::Window(int width, int height)
{
	this->width = width;
	this->height = height; //gett overwriten to fit screen

}


Window::~Window()
{
}

void Window::setSize(int width, int height)
{
	this->width = width;
	this->height = height;
}

void Window::update()
{
	//processInput(basewindow->getWindow());

}
void Window::render()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}
