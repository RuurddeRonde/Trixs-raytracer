#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "Ray.h"
#include "HitableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Random.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"
namespace Trixs
{

	class RayTrixser
	{
	public:
		RayTrixser()
		{
		}
		static void render(int randomObjects, int nx, int ny, int ns, std::string filename)
		{
			FILE *fp;
			fopen_s(&fp, filename.c_str(), "w+"); 
			(void)fprintf(fp, "P3\n%d %d\n255\n", nx, ny);
			Hittable *world = random_scene(randomObjects);

			vec3 lookfrom(13, 2, 3);
			vec3 lookat(0, 0, 0);
			float dist_to_focus = 10.0;
			float aperture = 0.1;

			Camera cam(lookfrom, lookat, vec3(0, 1, 0), 20, float(nx) / float(ny), aperture, dist_to_focus);

			for (int j = ny - 1; j >= 0; j--) {
				for (int i = 0; i < nx; i++) {
					vec3 col(0, 0, 0);
					for (int s = 0; s < ns; s++) {
						float u = float(i + Core::Random::randomDouble()) / float(nx);
						float v = float(j + Core::Random::randomDouble()) / float(ny);
						Ray r = cam.getRay(u, v);
						col += color(r, world, 0);
					}
					col /= float(ns);
					col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
					int ir = int(255.99*col[0]);
					int ig = int(255.99*col[1]);
					int ib = int(255.99*col[2]);
					//std::cout << ir << " " << ig << " " << ib << "\n"; 
					(void)fprintf(fp, "%d %d %d\n", ir, ig, ib);
				}
			}

			(void)fclose(fp);
		}

	private:
		static Hittable *random_scene(int randomObjects) {
			int n = 500;
			Hittable **list = new Hittable*[n+1];
			list[0] = new Sphere(vec3(0, -1000, 0), 1000, new Lambertian(vec3(0.5, 0.5, 0.5)));
			int i = 1;

			for (int a = -11; a < 11; a++) 
			{
				for (int b = -11; b < 11; b++) 
				{

					float choose_mat = Core::Random::randomDouble();
					vec3 center(a + 0.9*Core::Random::randomDouble(), 0.2, b + 0.9*Core::Random::randomDouble());
					if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
						if (choose_mat < 0.8) {  // diffuse
							list[i++] = new Sphere(center, 0.2,
								new Lambertian(vec3(Core::Random::randomDouble()*Core::Random::randomDouble(),
									Core::Random::randomDouble()*Core::Random::randomDouble(),
									Core::Random::randomDouble()*Core::Random::randomDouble())
								)
							);
						}
						else if (choose_mat < 0.95) { // metal
							list[i++] = new Sphere(center, 0.2,
								new Metal(vec3(0.5*(1 + Core::Random::randomDouble()),
									0.5*(1 + Core::Random::randomDouble()),
									0.5*(1 + Core::Random::randomDouble())),
									0.5*Core::Random::randomDouble()));
						}
						else {  // glass
							list[i++] = new Sphere(center, 0.2, new Dielectric(1.5));
						}
					}
				}
			}
			list[i++] = new Sphere(vec3(0, 1, 0), 1.0, new Dielectric(1.5));
			list[i++] = new Sphere(vec3(-4, 1, 0), 1.0, new Lambertian(vec3(0.4, 0.2, 0.1)));
			list[i++] = new Sphere(vec3(4, 1, 0), 1.0, new Metal(vec3(0.7, 0.6, 0.5), 0.0));

			return new HittableList(list, i);
		}
		static vec3 color(const Ray& r, Hittable* world, int depth) {
			hitRecord rec;
			if (world->hit(r, 0.001, FLT_MAX, rec)) {
				Ray scattered;
				vec3 attenuation;
				if (depth < 50 && rec.matPtr->scatter(r, rec, attenuation, scattered)) {
					return attenuation * color(scattered, world, depth + 1);
				}
				else {
					return vec3(0, 0, 0);
				}
			}
			else
			{
				vec3 unit_direction = unit_vector(r.direction());
				float t = 0.5*(unit_direction.y() + 1.0);
				return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
			}
		}

	};
}
