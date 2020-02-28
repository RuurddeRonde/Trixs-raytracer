#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "Hitable.h"
#include "RenderSubmission.h"
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
	class RayTrixser
	{
	public:
		RayTrixser() {}
		static bool render(RenderSubmission* submission);

	private:
		static vec3 color(const Ray& r, Hittable* world, int depth);
		static Camera* cam;
		static Hittable *world;
		static vec3 calcPixel(RenderSubmission* submission, int i, int j);
	};
}
