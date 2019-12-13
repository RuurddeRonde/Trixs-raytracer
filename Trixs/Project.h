#pragma once
#include <string>
#include <vector>
#include "Scene.h"
class Project
{
public:
	Project();
	~Project();
	bool loadProject(std::string path);
	bool saveProject(std::string path);
private:
	std::string name;
	std::vector<Scene> scenes;
	//vector scenes
};

