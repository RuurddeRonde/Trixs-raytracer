#pragma once
#include "Scene.h"
#include "Random.h"
#include "Sphere.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"
#include "Triangle.h"
#include "Mesh.h"
#include "FileIO.h"
#include "ModelLoader.h"
#include <sstream>

namespace Trixs
{

	Scene::Scene(std::string path) : cam(vec3(0, 0, -3), vec3(0, 0, 0), vec3(0, 1, 0), 20, float(1920) / float(1080), 0.1, 5.0)
	{
		this->size = 0;
		loadScene(path);
	}


	Scene::~Scene()
	{
		for (auto i = 0; i < hittables.size(); i++)
		{
			delete hittables.at(i);
		}
		hittables.clear();
		size = 0;
	}

	void Scene::loadScene(std::string path)
	{
		std::vector<std::string> file = FileIO::readFile(path);

		this->name = file[0];
		int offset = 2;//the meshes start at row 2 in the scene file
		int objectsize = 6; //the meshes consist of 6 rows (type, path, pos, rot, scale, material)
		for (auto i = 0; i < std::stoi(file[1]); i++)
		{
			if (strcmp(file[6 * i + offset].c_str(), "MESH"))
			{
				std::istringstream in(file[6 * i + offset + 5]); //material
				std::istringstream inpos(file[6 * i + offset + 2]); //position
				std::istringstream inrot(file[6 * i + offset + 3]); //rotation
				std::istringstream inscale(file[6 * i + offset + 4]); //]scale
				std::string type;//mat type
				in >> type;           
				vec3 pos, rot, scale;
				inpos >> pos.e[0] >> pos.e[1] >> pos.e[2];
				inpos >> rot.e[0] >> rot.e[1] >> rot.e[2];
				inpos >> scale.e[0] >> scale.e[1] >> scale.e[2];
				if (type == "LAMBERTIAN")
				{
					float x, y, z;
					in >> x >> y >> z;       //now read the whitespace-separated floats
					submit(ModelLoader::LoadMesh(file[6 * i + offset + 1], new Lambertian(vec3(x, y, z)), Transform(pos, rot, scale)));
				}
			}
		}

	}
	void Scene::saveScene(std::string path)
	{
		std::string towrite;
		towrite.append(name + "\n");
		towrite.append(std::to_string(hittables.size()) + "\n");
		for (auto i = 0; i < hittables.size(); i++)
		{
			towrite.append(hittables.at(i)->getWritable());
		}
		bool succes = FileIO::writeFile(path.append(name.append(".t3ds")), towrite);
		return;
	}

	Hittable* Scene::getGraph()
	{
		Hittable **list = new Hittable*[size];
		int i = 0;
		for (i = 0; i < hittables.size(); i++)
		{
			list[i] = hittables.at(i);
		}

		return new HittableList(list, i);
	}

	void Scene::submit(Hittable* nh)
	{
		hittables.push_back(nh);
		size++;
	}

}