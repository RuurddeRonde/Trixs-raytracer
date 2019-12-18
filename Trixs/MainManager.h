#pragma once
#include "UIManager.h"
#include "Project.h"
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
		void stop();
		Window* getWindow() { return window; }
		Project* getProject() { return &project; }

		MainManager(MainManager const&) = delete;
		void operator=(MainManager const&) = delete;
	private:
		MainManager();
		//RenderManager* renderManager;
		Window* window;
		UIManager* uiManager;
		Project project;
		bool running = true;
	};

}