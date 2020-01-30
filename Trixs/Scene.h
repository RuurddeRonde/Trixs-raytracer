#pragma once
#include "HitableList.h"
#include <vector>
#include "Camera.h"
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
	void submit(Hittable* nh);

	Hittable* getGraph();
	std::vector<Hittable*>* getObjects() { return &hittables; }
	std::string getName() { return name; }
	Camera getCamera() { return cam; }
	Camera* getCamPTR() { return &cam; }
private:
	std::vector<Hittable*> hittables;
	int size;
	std::string name;
	Camera cam;
};

}
