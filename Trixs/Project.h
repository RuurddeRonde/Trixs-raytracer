#pragma once
#include <string>
#include <vector>
#include "Scene.h"
class Project
{
public:
	Project();
	~Project();
	bool loadProject();
	bool saveProject();
private:
	std::string name;
	std::vector<Scene> scenes;
	//vector scenes
};

