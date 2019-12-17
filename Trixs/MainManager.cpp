#include "MainManager.h"
#include "ImGuiUIManager.h"
#include <iostream>
namespace Trixs
{

	MainManager::MainManager()
	{
		window = new Window(800, 600);
		uiManager = new ImGuiUIManager(window);
		//uiManager->initWindows();
	}
	MainManager::~MainManager()
	{
		delete uiManager;
		delete window;
	}

	void MainManager::run()
	{
		while (running)
		{
			uiManager->update();
			uiManager->render();
			window->render();
		}

	}
	
	void MainManager::stop()
	{
		running = false;
	}
}