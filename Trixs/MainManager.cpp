#include "MainManager.h"
#include "ImGuiUIManager.h"
namespace Trixs
{
	MainManager::MainManager()
	{
		renderManager = new RenderManager();
		uiManager = new ImGuiUIManager(renderManager->getWindow());
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
}