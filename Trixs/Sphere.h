#pragma once
#include "Hitable.h"
namespace Trixs
{

	class Sphere : public Hittable
	{
	public:
		Sphere() {}
		Sphere(vec3 cen, float rad, Material* mat) : center(cen), radius(rad), matPtr(mat) {}
		virtual bool hit(const Ray& r, float t_min, float t_max, hitRecord& rec)const;
	private:
		vec3 center;
		float radius;
		Material* matPtr;
	};

}