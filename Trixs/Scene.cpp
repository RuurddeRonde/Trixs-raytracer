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

namespace Trixs
{

	Scene::Scene(std::string name) : cam(vec3(0, 0, 5), vec3(0, 0, 0), vec3(0, 1, 0), 20, float(1920) / float(1080), 0.1, 5.0)
	{
		this->name = name;
		this->size = 0;
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