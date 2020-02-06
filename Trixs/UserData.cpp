#include "UserData.h"
#include "FileIO.h"
namespace Trixs
{
	UserSettings UserData::LoadUserSettings()
	{
		UserSettings loadedSettings;

		std::vector<std::string> settingsfile = FileIO::readFile("C:\\Users\\Ruurd\\Documents\\Trixs\\TrixsAnimator\\settings.txt");

		if (settingsfile.size() == 4)
		{
			if (settingsfile[0] == "true")
			{
				loadedSettings.FirstStartupEver = true;
			}
			else
			{
				loadedSettings.FirstStartupEver = false;
			}
			loadedSettings.defaultSavePath = settingsfile[1];
			loadedSettings.lastVisitedProjectPath = settingsfile[2];
			loadedSettings.lastVisitedProjectName = settingsfile[3];
		}
		else
		{
			loadedSettings.FirstStartupEver = false;
			loadedSettings.defaultSavePath = "%USERPROFILE%\Documents\Trixs\TrixsAnimator\Projects";
			loadedSettings.lastVisitedProjectPath = "%USERPROFILE%/Documents/Trixs/TrixsAnimator/Projects/testProject/";
			loadedSettings.lastVisitedProjectName = "testProject";

		}

		return loadedSettings;
	}
	void UserData::SaveUserSettings(UserSettings userSettings)
	{
		std::string settings;
		settings += userSettings.FirstStartupEver ? "true\n" : "false\n";
		settings += userSettings.defaultSavePath;
		settings += userSettings.lastVisitedProjectPath;
		settings += userSettings.lastVisitedProjectName;
		FileIO::writeFile("%USERPROFILE%\Documents\Trixs\TrixAnimator\settings.txt", settings);
	}
}