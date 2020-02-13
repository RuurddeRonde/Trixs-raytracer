#include "Project.h"
#include "FileIO.h"

//temp
#include "Mesh.h"
#include "Lambertian.h"
#include "ModelLoader.h"
#include <Windows.h>
#include <shlobj.h>


namespace Trixs
{

	Project::Project(std::string path, bool isNewProject, std::string name)
	{
		savePath = path;
		this->name = name;
		if (!isNewProject)
		{
			loadProject(path, name);
			currentScene = scenes.at(0);
			return;
		}
		scenes.push_back(new Scene("emptyScene", true));
		currentScene = scenes.at(0);
		//currentScene->submit(new Mesh("models/cube.obj", new Lambertian(vec3(0.4, 0.2, 0.1))));
		currentScene->submit(ModelLoader::LoadMesh("models/stl/Dragon.stl", new Lambertian(vec3(0.4, 0.2, 0.1))));
	}


	Project::~Project()
	{
	}

	///saveproject file
	///project type (TRIXSANIMATOR)
	///name
	///nr scenes
	///scene1 filepath
	///scene2 filepath
	///etc.

	///save folder structure
	///projectname
	///		project save file.psf
	///		scenes
	///			scene1.ssf
	///			scene2.ssf
	///		models
	///			model1.obj
	///			model2.obj
	///		textures
	///			texture1.obj


	bool Project::saveProject()
	{
		std::string SaveString;
		SaveString += "TRIXSANIMATOR\n";
		SaveString += name + "\n";
		for (auto i = 0; i < scenes.size(); i++)
		{
			scenes.at(i)->saveScene(savePath +"//scenes//");
			SaveString += savePath + "//scenes//"+scenes.at(i)->getName() + "\n";
		}
		return FileIO::writeFile(savePath + "//" + name + ".trixs", SaveString);
	}

	bool Project::loadProject(std::string path, std::string name)
	{
		//open file
		std::string projectPath = path + "//" + name + ".trixs";
		std::vector<std::string> projectfile = FileIO::readFile(projectPath);
		this->name = name;
		//load all scenes
		for (auto i = 2; i < projectfile.size(); i++)
		{
			addScene(projectfile[i]);
		}
		return false;
	}

	bool Project::switchScene(int sceneID)
	{
		if (sceneID > scenes.size())
		{
			return false;
		}
		currentScene->saveScene();
		currentScene = scenes.at(sceneID);
		return true;
	}

	Scene* Project::getCurrentScene()
	{
		return currentScene;
	}
	void Project::addScene(std::string path)
	{
		scenes.push_back(new Scene(path, false));
	}
	void Project::createNewScene(std::string name)
	{
		scenes.push_back(new Scene(savePath + "/scenes/" + name, true));
	}
	std::vector<Scene*> Project::getAllScenes()
	{
		return scenes;
	}
}
