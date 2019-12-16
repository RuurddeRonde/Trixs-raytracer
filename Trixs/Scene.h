#pragma once
#include <vector>
#include "Hitable.h"
namespace Trixs
{

class Scene
{
public:
	Scene();
	~Scene();
	std::vector<Hittable*> getGraph();
	void submit(Hittable* nh);
private:
	std::vector<Hittable*> hittables;
};

}
