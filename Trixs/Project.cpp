#include "Project.h"

namespace Trixs
{

	Project::Project()
	{

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
		scenes.push_back(Scene());
	}
	std::vector<Scene> Project::getAllScenes()
	{
		return scenes;
	}
}
