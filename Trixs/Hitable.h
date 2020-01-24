#pragma once
#include "Ray.h"
#include "Transform.h"
namespace Trixs
{

	class Material;
	struct hitRecord
	{
		float t;
		vec3 p;
		vec3 normal;
		Material* matPtr;
	};

	class Hittable
	{
	public:
		virtual bool hit(const Ray& r, float t_min, float t_max, hitRecord& rec) const = 0;
		virtual std::string getWritable()const { return ""; }
		virtual void draw()const {}
		Transform getTransform()const { return transform; }
	private:
		Transform transform;
	};
}