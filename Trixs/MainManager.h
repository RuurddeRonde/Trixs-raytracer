#pragma once
#include "RenderManager.h"
#include "UIManager.h"
#include <string>
namespace Trixs
{
	class MainManager
	{

	public:
		MainManager();
		~MainManager();
		void run();
		static void SetNewProject(std::string project);
	private:
		RenderManager* renderManager;
		UIManager* uiManager;
		static bool loadnewproject; //indicates if a new project should be loaded
		static std::string projectPath;
	};

}