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
	bool loadProject(std::string path,std::string name);
	bool switchScene(int sceneID);
	void addScene(std::string path);
	void createNewScene(std::string name);
	std::vector<Scene*> getAllScenes();
	Scene* getCurrentScene();
	std::string getName() { return name; }
	std::string getSavePath() { return savePath; }
private:
	std::string name;
	std::string savePath;
	std::vector<Scene*> scenes;
	Scene* currentScene;
};

}
