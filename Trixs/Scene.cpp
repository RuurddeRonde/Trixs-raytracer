#pragma once
#include "Scene.h"
#include "Random.h"
#include "Sphere.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"
#include "Triangle.h"
#include "Mesh.h"


namespace Trixs
{

	Scene::Scene()
	{
	}


	Scene::~Scene()
	{
		delete hittables;
	}


	Hittable* Scene::getGraph()
	{
		int n = 1;
		Hittable **list = new Hittable*[n];
		int i = 0;

		list[i++] = new Mesh("models/suzanne.obj");
		//list[i++] = new Sphere(vec3(0, -1000, 0), 1000, new Lambertian(vec3(0.5, 0.5, 0.5)));

		//list[i++] = new Sphere(vec3(0, 1, 0), 1.0, new Dielectric(1.5));
		//list[i++] = new Sphere(vec3(-4, 1, 0), 1.0, new Lambertian(vec3(0.4, 0.2, 0.1)));
		//list[i++] = new Sphere(vec3(4, 1, 0), 1.0, new Metal(vec3(0.7, 0.6, 0.5), 0.0));

		//list[i++] = new Triangle(new vec3(0,2,0), new vec3(1,2,0), new vec3(1,3,0), new Lambertian(vec3(0.9, 0.0, 0.0)));
		//list[i++] = new Triangle(new vec3(-4, 2, 0), new vec3(-3, 2, 0), new vec3(-3, 3, 0), new Lambertian(vec3(0.0, 0.9, 0.0)));
		//list[i++] = new Triangle(new vec3(4, 2, 0), new vec3(5, 2, 0), new vec3(5, 3, 0), new Lambertian(vec3(0.0, 0.0, 0.9)));

		
		
		return new HittableList(list, i);
		
		//cube
		//{
		//	//front
		//	list[i++] = new Triangle(new vec3(0, 0, 0), new vec3(1, 0, 0), new vec3(0, 1, 0), new Lambertian(vec3(0.9, 0.0, 0.0)));
		//	list[i++] = new Triangle(new vec3(0, 1, 0), new vec3(1, 0, 0), new vec3(1, 1, 0), new Lambertian(vec3(0.9, 0.0, 0.0)));
		//	//top
		//	list[i++] = new Triangle(new vec3(0, 1, 0), new vec3(1, 1, 0), new vec3(0, 1, 1), new Lambertian(vec3(0.3, 0.0, 0.0)));
		//	list[i++] = new Triangle(new vec3(1, 1, 0), new vec3(1, 1, 1), new vec3(0, 1, 1), new Lambertian(vec3(0.3, 0.0, 0.0)));

		//	//
		//	//left
		//	list[i++] = new Triangle(new vec3(0, 0, 0), new vec3(0, 1, 0), new vec3(0, 1, 1), new Lambertian(vec3(0.0, 0.9, 0.0)));
		//	list[i++] = new Triangle(new vec3(0, 1, 1), new vec3(0, 0, 1), new vec3(0, 0, 0), new Lambertian(vec3(0.0, 0.9, 0.0)));

		//	//////right
		//	list[i++] = new Triangle(new vec3(1, 0, 0), new vec3(1, 0, 1), new vec3(1, 1, 0), new Lambertian(vec3(0.0, 0.9, 0.0)));
		//	list[i++] = new Triangle(new vec3(1, 1, 0), new vec3(1, 0, 1), new vec3(1, 1, 1), new Lambertian(vec3(0.0, 0.9, 0.0)));

		//	////back
		//	list[i++] = new Triangle(new vec3(0, 0, 1), new vec3(1, 1, 1), new vec3(1, 0, 1), new Lambertian(vec3(0.0, 0.0, 0.9)));
		//	list[i++] = new Triangle(new vec3(0, 0, 1), new vec3(0, 1, 1), new vec3(1, 1, 1), new Lambertian(vec3(0.0, 0.0, 0.9)));

		//	////bottom
		//	list[i++] = new Triangle(new vec3(0, 0, 0), new vec3(1, 0, 0), new vec3(0, 0, 1), new Lambertian(vec3(0.0, 0.0, 0.9)));
		//	list[i++] = new Triangle(new vec3(1, 0, 0), new vec3(1, 0, 1), new vec3(0, 0, 1), new Lambertian(vec3(0.0, 0.0, 0.9)));

		//}

		//random spheres
		{ 
		//for (int a = -11; a < 11; a++)
		//{
		//	for (int b = -11; b < 11; b++)
		//	{

		//		float choose_mat = Core::Random::randomDouble();
		//		vec3 center(a + 0.9*Core::Random::randomDouble(), 0.2, b + 0.9*Core::Random::randomDouble());
		//		if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
		//			if (choose_mat < 0.8) {  // diffuse
		//				list[i++] = new Sphere(center, 0.2,
		//					new Lambertian(vec3(Core::Random::randomDouble()*Core::Random::randomDouble(),
		//						Core::Random::randomDouble()*Core::Random::randomDouble(),
		//						Core::Random::randomDouble()*Core::Random::randomDouble())
		//					)
		//				);
		//			}
		//			else if (choose_mat < 0.95) { // metal
		//				list[i++] = new Sphere(center, 0.2,
		//					new Metal(vec3(0.5*(1 + Core::Random::randomDouble()),
		//						0.5*(1 + Core::Random::randomDouble()),
		//						0.5*(1 + Core::Random::randomDouble())),
		//						0.5*Core::Random::randomDouble()));
		//			}
		//			else {  // glass
		//				list[i++] = new Sphere(center, 0.2, new Dielectric(1.5));
		//			}
		//		}
		//	}
		//}
		}
	}
	void Scene::submit(Hittable* nh)
	{
		//todo add to scene
	}

}