#pragma once
#include "UIManager.h"
#include "Project.h"
#include "ProgramSettings.h"
#include "UserData.h"
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
		Project* getProject() { return project; }
		ProgramSettings* getProgramSettings() { return &programSettings; }

		MainManager(MainManager const&) = delete;
		void operator=(MainManager const&) = delete;
	private:
		MainManager();
		void checkProgSettings();

		Window* window;
		UIManager* uiManager;
		Project* project;
		ProgramSettings programSettings;
		UserSettings user;
	};

}