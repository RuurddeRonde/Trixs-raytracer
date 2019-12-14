#pragma once
#include "RenderManager.h"
#include "UIManager.h"
#include <string>
namespace Trixs
{
	class MainManager
	{

	public:
		static MainManager& getInstance() 
		{ 
			static MainManager instance;
			return instance; 
		}
		~MainManager();
		void run();
		void SetNewProject(std::string project);
		MainManager(MainManager const&) = delete;
		void operator=(MainManager const&) = delete;
	private:
		MainManager();
		RenderManager* renderManager;
		UIManager* uiManager;
		std::string projectPath;
	};

}