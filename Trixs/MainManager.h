#pragma once
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
		Window* getWindow() { return window; }
		void stop();
		MainManager(MainManager const&) = delete;
		void operator=(MainManager const&) = delete;
	private:
		MainManager();
		//RenderManager* renderManager;
		Window* window;
		UIManager* uiManager;

		bool running = true;
	};

}