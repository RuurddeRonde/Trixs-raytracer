#pragma once
#include <string>
#include <vector>
#include "Scene.h"

namespace Trixs
{

class Project
{
public:
	Project();
	~Project();
	bool saveProject(std::string path);
	Scene* getCurrentScene();
	std::vector<Scene*> getAllScenes();
	void addScene();
private:
	bool loadProject(std::string path);
	std::string name;
	std::vector<Scene*> scenes;
	Scene* currentScene;
};

}
