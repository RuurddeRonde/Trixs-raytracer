#include "Scene.h"

namespace Trixs
{

	Scene::Scene()
	{
	}


	Scene::~Scene()
	{
		hittables.clear();
	}


	std::vector<Hittable*> Scene::getGraph()
	{
		return hittables;
	}
	void Scene::submit(Hittable* nh)
	{
		hittables.push_back(nh);
	}

}