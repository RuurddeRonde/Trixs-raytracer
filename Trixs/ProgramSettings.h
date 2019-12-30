#pragma once
#include <string>
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
};
