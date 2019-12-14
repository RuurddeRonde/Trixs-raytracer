#include "MainManager.h"
#include "ImGuiUIManager.h"
#include <iostream>
namespace Trixs
{
	bool MainManager::loadnewproject = false;
	std::string MainManager::projectPath = "";

	MainManager::MainManager()
	{
		loadnewproject = false;

		renderManager = new RenderManager();
		uiManager = new ImGuiUIManager(renderManager->getWindow());
		uiManager->initWindows(renderManager);
		renderManager->setUI(uiManager);

	}
	MainManager::~MainManager()
	{
		delete uiManager;
		delete renderManager;
	}

	void MainManager::run()
	{
		while (!renderManager->WindowShouldClose())
		{
			renderManager->render();
		}

	}
	void MainManager::SetNewProject(std::string project)
	{
		MainManager::loadnewproject = true;
		MainManager::projectPath = project;
	}
}