#pragma once
#include <string>
namespace Trixs
{

	struct UserSettings
	{
		bool FirstStartupEver;
		std::string defaultSavePath;
		std::string lastVisitedProjectPath;
		std::string lastVisitedProjectName;
	};

	class UserData
	{
	public:
		static UserSettings LoadUserSettings();
	};

}
