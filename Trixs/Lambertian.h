#pragma once
#include "Material.h"
#include "Random.h"
namespace Trixs
{

class Lambertian : public Material
{
public:
	Lambertian(const vec3& a) : albedo(a){}
	virtual bool scatter(Ray r_in, const hitRecord& rec, vec3& attenuation, Ray& scattered)const
	{
		vec3 target = rec.p + rec.normal + Trixs::Core::Random::random_in_unit_sphere();
		scattered = Ray(rec.p, target - rec.p);
		attenuation = albedo;
		return true;
	}
private:
	vec3 albedo;
};
}