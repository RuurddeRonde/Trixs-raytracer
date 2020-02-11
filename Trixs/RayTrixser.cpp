#include "RayTrixser.h"
#include "MainManager.h"
#include "Camera.h"
#include "Scene.h"
#include "Sphere.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"
#include "HitableList.h"
#include "ImageIO.h"
namespace Trixs
{
	bool RayTrixser::render(RenderSubmission* submission)
	{
#define CHANNEL_NUM 3
		uint8_t* pixels = new uint8_t[submission->width * submission->height * CHANNEL_NUM];
		int index = 0;

		int width = submission->width;
		int height = submission->height;

		Hittable *world = NULL;
		if (submission->scene == nullptr)
		{
			return false;
		}
		else
		{
			world = submission->scene->getGraph();
		}

		vec3 lookfrom(0, 0, 80);
		vec3 lookat(0, 0, 0);
		float dist_to_focus = 80.0;
		float aperture = 0.1;

		Camera cam = submission->scene->getCamera();

		for (int j = height - 1; j >= 0; j--) {
			for (int i = 0; i < width; i++) {
				vec3 col(0, 0, 0);
				for (int s = 0; s < submission->samplesPerPixel; s++) {
					float u = float(i + Core::Random::randomDouble()) / float(width);
					float v = float(j + Core::Random::randomDouble()) / float(height);
					Ray r = cam.getRay(u, v);
					col += color(r, world, 0);
				}
				col /= float(submission->samplesPerPixel);
				col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
				int ir = int(255.99*col[0]);
				int ig = int(255.99*col[1]);
				int ib = int(255.99*col[2]);
				//std::cout << ir << " " << ig << " " << ib << "\n"; 

				pixels[index++] = ir;
				pixels[index++] = ig;
				pixels[index++] = ib;
			}
		}

		std::string filepath = "renders\\" + submission->outputfile;
		switch (submission->outputType)
		{
		case JPG:
			filepath = filepath + ".jpg";
			Core::ImageIO::WriteJPG(filepath.c_str(), width, height, 3, pixels, 100);
			break;
		case PNG:
			filepath = filepath + ".png";
			Core::ImageIO::WritePNG(filepath.c_str(), width, height, 3, pixels, width*3);
			break;
		case BPM:
			filepath = filepath + ".BPM";
			Core::ImageIO::WriteBPM(filepath.c_str(), width, height, 3, pixels);
			break;
		case TGA:
			filepath = filepath + ".TGA";
			Core::ImageIO::WriteTGA(filepath.c_str(), width, height, 3, pixels);
			break;
		case HDR:
			filepath = filepath + ".hdr";
			Core::ImageIO::WriteHDR(filepath.c_str(), width, height, 3, pixels);
			break;
		default:
			break;
		}
		delete[] pixels;
		return true;
	}
	vec3 RayTrixser::color(const Ray& r, Hittable* world, int depth) {
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
		else //background
		{
			vec3 unit_direction = unit_vector(r.direction());
			float t = 0.5*(unit_direction.y() + 1.0);
			return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t * vec3(MainManager::getInstance().getProgramSettings()->backgroundColor.x(), MainManager::getInstance().getProgramSettings()->backgroundColor.y(), MainManager::getInstance().getProgramSettings()->backgroundColor.z());
		}
	}
}