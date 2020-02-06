#include "MainManager.h"
#include "ImGuiUIManager.h"
#include <iostream>
namespace Trixs
{

	MainManager::MainManager()
	{
		user = UserData::LoadUserSettings();

		//todo set all to false
		programSettings.loadPreviousProject = false;
		programSettings.loadProjectFromDisk = false;
		programSettings.newProject = false;
		programSettings.projectAdjusted = false;

		programSettings.quitCalled = false;
		programSettings.saveproject = false;
		programSettings.saveScene = false;
		programSettings.projectLoaded = false;

		window = new Window(800, 600);
		uiManager = new ImGuiUIManager(window);	
		//project = new Project("emptyProject", false, "emptyProject");
	}
	MainManager::~MainManager()
	{
		delete uiManager;
		delete window;
	}

	void MainManager::run()
	{
		while (!programSettings.quitCalled)
		{
			checkProgSettings();

			uiManager->update();
			uiManager->render();
			window->render();
		}

	}

	void MainManager::checkProgSettings()
	{
		if (programSettings.projectAdjusted)
		{
			if (programSettings.loadPreviousProject)
			{
				delete project;
				project = new Project(user.lastVisitedProjectPath, false, user.lastVisitedProjectName);
				programSettings.loadPreviousProject = false;
				programSettings.projectAdjusted = false;
				programSettings.projectLoaded = true;
			}
			else if (programSettings.loadProjectFromDisk)
			{
				delete project;	
				size_t found = programSettings.newProjectName.rfind("/");
				if (found == std::string::npos)
				{
					size_t found = programSettings.newProjectName.rfind('\\');
				}
				project = new Project(programSettings.newProjectName, false, programSettings.newProjectName.substr(found));
				programSettings.projectAdjusted = false;
				programSettings.loadProjectFromDisk = false;
				programSettings.projectLoaded = true;
				user.lastVisitedProjectName = project->getName();
				UserData::SaveUserSettings(user);
			}
			else if (programSettings.newProject)
			{
				delete project;
				project = new Project(user.defaultSavePath, true, programSettings.newProjectName);
				programSettings.projectLoaded = true;
				user.lastVisitedProjectName = project->getName();
				UserData::SaveUserSettings(user);
			}
		}
	}

	void MainManager::stop()
	{
		programSettings.quitCalled = true;
	}
}