#include "MainManager.h"
#include "ImGuiUIManager.h"
#include <iostream>
namespace Trixs
{

	MainManager::MainManager()
	{
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
		MainManager::projectPath = project;
	}
}