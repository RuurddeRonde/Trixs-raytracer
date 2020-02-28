#include "RayTrixser.h"
namespace Trixs
{

	Camera* RayTrixser::cam;
	Hittable* RayTrixser::world;

	bool RayTrixser::render(RenderSubmission* submission)
	{
#define CHANNEL_NUM 3
		uint8_t* pixels = new uint8_t[submission->width * submission->height * CHANNEL_NUM];
		int index = 0;

		int width = submission->width;
		int height = submission->height;

		world = NULL;
		if (submission->scene == nullptr)
		{
			return false;
		}
		else
		{
			world = submission->scene->getTestGraph();
		}

		vec3 lookfrom(13, 2, 10);
		vec3 lookat(0, 2, 0);
		float dist_to_focus = 11.0;
		float aperture = 0.0;
		cam  = new Camera(lookfrom, lookat, vec3(0, 1, 0), 20.0f, float(width) / float(height), aperture, dist_to_focus);

		//cam = &submission->scene->getCamera();

		for (int j = height - 1; j >= 0; j--) {
			for (int i = 0; i < width; i++) {
				vec3 col = calcPixel(submission, i, j);
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
			vec3 emitted = rec.matPtr->emitted(rec.p);
			if (depth < 50 && rec.matPtr->scatter(r, rec, attenuation, scattered))
				return emitted + attenuation * color(scattered, world, depth + 1);
			else
				return emitted;
		}
		else //background
		{
			//vec3 unit_direction = unit_vector(r.direction());
			//float t = 0.5*(unit_direction.y() + 1.0);
			//return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t * MainManager::getInstance().getProgramSettings()->backgroundColor;
			return  MainManager::getInstance().getProgramSettings()->backgroundColor;
		}
	}
	vec3 RayTrixser::calcPixel(RenderSubmission* submission, int i, int j)
	{
		vec3 col(0, 0, 0);
		for (int s = 0; s < submission->samplesPerPixel; s++)
		{
			float u = float(i + Core::Random::randomDouble()) / float(submission->width);
			float v = float(j + Core::Random::randomDouble()) / float(submission->height);
			Ray r = cam->getRay(u, v);
			col += color(r, world, 0);
		}
		return col;
	}
}