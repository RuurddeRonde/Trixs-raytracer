#include "UserData.h"

namespace Trixs
{
	UserSettings UserData::LoadUserSettings()
	{
		UserSettings loadedSettings;

		//todo load data from registry
		loadedSettings.FirstStartupEver = false;
		loadedSettings.defaultSavePath = "C:/Users/Ruurd/Documents/Trixs/TrixsAnimator/Projects";
		loadedSettings.lastVisitedProjectPath = "C:/Users/Ruurd/Documents/Trixs/TrixsAnimator/Projects/testProject/";
		loadedSettings.lastVisitedProjectName = "testProject";
		return loadedSettings;
	}
}