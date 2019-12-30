#pragma once
#include "HitableList.h"
#include <vector>
//#include "Sphere.h"
//#include "Lambertian.h"
//#include "Metal.h"
//#include "Dielectric.h"

namespace Trixs
{

class Scene
{
public:
	Scene(std::string name);
	~Scene();
	void loadScene(std::string path);
	void saveScene(std::string path);
	Hittable* getGraph();
	std::vector<Hittable*>* getObjects();
	std::string getName() { return name; }
	void submit(Hittable* nh);
private:
	std::vector<Hittable*> hittables;
	int size;
	std::string name;
};

}
