#pragma once
#include "Hitable.h"
namespace Trixs
{
	class rotate_y : public Hittable {
	public:
		rotate_y(Hittable *p, float angle);
		virtual bool hit(
			const Ray& r, float t_min, float t_max, hitRecord& rec) const;
		Hittable *ptr;
		float sin_theta;
		float cos_theta;
	};

	rotate_y::rotate_y(Hittable *p, float angle) : ptr(p) 
	{
		float radians = (3.141592 / 180.) * angle;
		sin_theta = sin(radians);
		cos_theta = cos(radians);
	}

	bool rotate_y::hit(const Ray& r, float t_min, float t_max, hitRecord& rec) const 
	{
		vec3 origin = r.origin();
		vec3 direction = r.direction();
		origin[0] = cos_theta * r.origin()[0] - sin_theta * r.origin()[2];
		origin[2] = sin_theta * r.origin()[0] + cos_theta * r.origin()[2];
		direction[0] = cos_theta * r.direction()[0] - sin_theta * r.direction()[2];
		direction[2] = sin_theta * r.direction()[0] + cos_theta * r.direction()[2];
		Ray rotated_r(origin, direction);
		if (ptr->hit(rotated_r, t_min, t_max, rec)) {
			vec3 p = rec.p;
			vec3 normal = rec.normal;
			p[0] = cos_theta * rec.p[0] + sin_theta * rec.p[2];
			p[2] = -sin_theta * rec.p[0] + cos_theta * rec.p[2];
			normal[0] = cos_theta * rec.normal[0] + sin_theta * rec.normal[2];
			normal[2] = -sin_theta * rec.normal[0] + cos_theta * rec.normal[2];
			rec.p = p;
			rec.normal = normal;
			return true;
		}
		else
			return false;
	}
}