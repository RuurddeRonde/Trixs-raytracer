#include "Project.h"
#include "FileIO.h"

//temp
#include "Mesh.h"
#include "Lambertian.h"
#include "ModelLoader.h"
namespace Trixs
{

	Project::Project(std::string path, bool isNewProject, std::string name)
	{
		savePath = path;
		this->name = name;
		if (!isNewProject)
		{
			loadProject(path);
		}
		scenes.push_back(new Scene("testscene"));
		currentScene = scenes.at(0);
		//currentScene->submit(new Mesh("models/cube.obj", new Lambertian(vec3(0.4, 0.2, 0.1))));
		currentScene->submit(ModelLoader::LoadMesh("models/stl/Dragon.stl", new Lambertian(vec3(0.4, 0.2, 0.1))));
	}


	Project::~Project()
	{
	}


	bool Project::saveProject()
	{
		std::string SaveString;
		SaveString += "TRIXSANIMATOR\n";
		SaveString += name + "\n";
		for (auto i = 0; i < scenes.size(); i++)
		{
			scenes.at(i)->saveScene(savePath +"scenes/");
			SaveString += scenes.at(i)->getName() + "\n";
		}
		return FileIO::writeFile(savePath.append(name.append(".trixs")), SaveString);
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
		scenes.push_back(new Scene("testScene"));
	}
	std::vector<Scene*> Project::getAllScenes()
	{
		return scenes;
	}
}
