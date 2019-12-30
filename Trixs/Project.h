#pragma once
#include <string>
#include <vector>
#include "Scene.h"

namespace Trixs
{

class Project
{
public:
	Project(std::string path, bool isNewProject, std::string name);
	~Project();
	bool saveProject();
	bool loadProject(std::string path);
	Scene* getCurrentScene();
	std::vector<Scene*> getAllScenes();
	void addScene();
private:
	std::string name;
	std::string savePath;
	std::vector<Scene*> scenes;
	Scene* currentScene;
};

}
