#pragma once
#include "Scene.h"
#include "Random.h"
#include "Sphere.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"
#include "diffuseLight.h"
#include "Triangle.h"
#include "Mesh.h"
#include "FileIO.h"
#include "ModelLoader.h"
#include "Translate.h"
#include "Rotate.h"
#include "Texture.h"
#include <sstream>

namespace Trixs
{

	Scene::Scene(std::string path, bool IsNew) : cam(vec3(0, 0, -8), vec3(0, 0, 0), vec3(0, 1, 0), 20, float(200) / float(100), 0.1f, 8.0)
	{
		this->size = 0;
		this->path = path;
		if (IsNew)
		{
			name = path.substr((path.find_last_of('/') + 1));
			name.append(".t3ds");
			saveScene(path); //generate save file
		}
		else
		{
			loadScene(path);
		}
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
			if (strcmp(file[(6 * i) + offset].c_str(), "MESH") == 0)
			{
				std::istringstream in(file[(6 * i) + offset + 5]); //material
				std::istringstream inpos(file[(6 * i) + offset + 2]); //position
				std::istringstream inrot(file[(6 * i) + offset + 3]); //rotation
				std::istringstream inscale(file[(6 * i) + offset + 4]); //scale
				std::string type;//mat type
				std::string temp;
				inpos >> temp;
				inrot >> temp;
				inscale >> temp;
				vec3 pos, rot, scale;
				inpos >> pos.e[0] >> pos.e[1] >> pos.e[2];
				inrot >> rot.e[0] >> rot.e[1] >> rot.e[2];
				inscale >> scale.e[0] >> scale.e[1] >> scale.e[2];
				in >> type;
				if (type == "LAMBERTIAN") //todo add other types
				{
					float x, y, z;
					in >> x >> y >> z;       //now read the whitespace-separated floats
					submit(ModelLoader::LoadMesh(file[6 * i + offset + 1], new Lambertian(new ConstantTexture(vec3(x, y, z))), Transform(pos, rot, scale)));
				}
			}
		}
	}

	void Scene::saveScene()
	{
		saveScene(path);
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
		bool succes = FileIO::writeFile(path.append(name), towrite);
		return;
	}

	Hittable* Scene::getGraph()
	{
		Hittable **list = new Hittable*[size];
		int i = 0;
		for (i = 0; i < hittables.size(); i++)
		{
			hittables.at(i)->triangulate();

			list[i] =
				new translate(
					new rotate_z(
						new rotate_y(
							new rotate_x(
								hittables[i], hittables[i]->getTransform()->getRot().x()),
							hittables[i]->getTransform()->getRot().y()),
						hittables[i]->getTransform()->getRot().z()),
					hittables[i]->getTransform()->getPos());
		}

		return new HittableList(list, i);

	}

#include "external\stb_image.h"
	Hittable* Scene::getTestGraph()
	{
		//int n = 500;
		//Hittable **list = new Hittable*[n + 1];
		//list[0] = new Sphere(vec3(0, -1000, 0), 1000, new Lambertian(vec3(0.5, 0.5, 0.5)));
		//int i = 1;
		//for (int a = -11; a < 11; a++) {
		//	for (int b = -11; b < 11; b++) {
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
		//				list[i++] = new Sphere(center, 0.2, new diffuseLight(new vec3(1.0f, 1.0f, 1.0f)));
		//			}
		//		}
		//	}
		//}

		//list[i++] = new Sphere(vec3(0, 1, 0), 1.0, new Dielectric(1.5));
		//list[i++] = new Sphere(vec3(-4, 1, 0), 1.0, new Lambertian(vec3(0.4, 0.2, 0.1)));
		//list[i++] = new Sphere(vec3(4, 1, 0), 1.0, new Metal(vec3(0.7, 0.6, 0.5), 0.0));

		Hittable **list = new Hittable *[4];
		Texture *checker = new CheckerTexture(
			new ConstantTexture(vec3(0.2, 0.3, 0.1)),
			new ConstantTexture(vec3(0.9, 0.9, 0.9)));
		list[0] = new Sphere(vec3(0, -1000, 0), 1000, new Lambertian(checker));
		{
			int nx, ny, nn;
			unsigned char *tex_data = stbi_load("earthmap.jpg", &nx, &ny, &nn, 0);
			Material *mat = new Lambertian(new Imagetexture(tex_data, nx, ny));
			list[1] = new Sphere(vec3(0, 2, 0), 2, mat);
		}
		{
			int nx, ny, nn;
			unsigned char *tex_data = stbi_load("moon.jpg", &nx, &ny, &nn, 0);
			Material *mat = new Lambertian(new Imagetexture(tex_data, nx, ny));
			list[2] = new Sphere(vec3(4, 4, -1), 1, mat);
		}


		list[3] = new Sphere(vec3(0, 7, 0), 2, new diffuseLight(new vec3(4, 4, 4)));
		//list[2] = new Sphere(vec3(-1, 7, 5), 2, new diffuseLight(new vec3(4, 4, 4)));

		return new HittableList(list, 4);
	}

	void Scene::submit(Hittable* nh)
	{
		hittables.push_back(nh);
		size++;
	}

}