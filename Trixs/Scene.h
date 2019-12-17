#pragma once
#include "HitableList.h"
//
//#include "Sphere.h"
//#include "Lambertian.h"
//#include "Metal.h"
//#include "Dielectric.h"

namespace Trixs
{

class Scene
{
public:
	Scene();
	~Scene();
	Hittable* getGraph();
	void submit(Hittable* nh);
private:
	Hittable* hittables;
};

}
