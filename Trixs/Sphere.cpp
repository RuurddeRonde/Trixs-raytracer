#include "Sphere.h"

namespace Trixs
{
	bool Sphere::hit(const Ray& r, float t_min, float t_max, hitRecord& rec) const
	{
		vec3 oc = r.origin() - center;
		float a = dot(r.direction(), r.direction());
		float b = dot(oc, r.direction());
		float c = dot(oc, oc) - radius * radius;
		float discriminant = b * b - a * c;
		if (discriminant > 0) {
			float temp = (-b - sqrt(discriminant)) / a;
			if (temp < t_max && temp > t_min) {
				rec.t = temp;
				rec.p = r.pointAtParameter(rec.t);
				rec.normal = (rec.p - center) / radius;
				rec.matPtr = matPtr;
				return true;
			}
			temp = (-b + sqrt(discriminant)) / a;
			if (temp < t_max && temp > t_min) {
				rec.t = temp;
				rec.p = r.pointAtParameter(rec.t);
				rec.normal = (rec.p - center) / radius;
				rec.matPtr = matPtr;
				return true;
			}
		}
		return false;
	}


}