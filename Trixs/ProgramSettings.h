#pragma once
#include <string>
#include "Vec3.h"
struct ProgramSettings
{
	bool projectAdjusted; //set true for loading/saving project etc.
	bool loadPreviousProject;
	bool loadProjectFromDisk;
	bool newProject;
	bool quitCalled;
	bool saveproject;
	bool saveScene;
	bool projectLoaded;
	std::string newProjectName;

	Trixs::vec3 backgroundColor = Trixs::vec3(0.2f, 0.3f, 0.3f);
};
