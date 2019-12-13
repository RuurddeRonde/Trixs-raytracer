#pragma once
#include "Hitable.h"
namespace Trixs
{

class Sphere : public Hittable
{
public:
	Sphere(){}
	Sphere(vec3 cen, float rad, Material* mat): center(cen), radius(rad), matPtr(mat){}
	virtual bool hit(const Ray& r, float t_min, float t_max, hitRecord& rec)const;
private:
	vec3 center;
	float radius;
	Material* matPtr;
};

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