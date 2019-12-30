#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "Hitable.h"
#include "RenderSubmission.h"
namespace Trixs
{
	class RayTrixser
	{
	public:
		RayTrixser() {}
		static bool render(RenderSubmission* submission);

	private:
		static vec3 color(const Ray& r, Hittable* world, int depth);

	};
}
