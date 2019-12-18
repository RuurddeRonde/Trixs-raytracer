#include "Project.h"

namespace Trixs
{

	Project::Project()
	{
		addScene();
		currentScene = scenes.at(0);
	}


	Project::~Project()
	{
		scenes.clear();
		currentScene = NULL;
	}


	bool Project::saveProject(std::string path)
	{
		return false;
	}

	bool Project::loadProject(std::string path)
	{
		return false;
	}
	Scene* Project::getCurrentScene()
	{
		return currentScene;
	}
	void Project::addScene()
	{
		scenes.push_back(new Scene());
	}
	std::vector<Scene*> Project::getAllScenes()
	{
		return scenes;
	}
}
