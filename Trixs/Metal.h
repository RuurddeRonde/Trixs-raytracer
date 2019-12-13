#pragma once
#include "Material.h"
#include "Random.h"

namespace Trixs
{

class Metal : public Material
{
public:
	Metal(const vec3& a, float f) : albedo(a) 
	{
		if (f < 1.0)
		{
			fuzz = f;
		}
		else
		{
			fuzz = 1.0;
		}
	}
	virtual bool scatter(Ray r_in, const hitRecord& rec, vec3& attenuation, Ray& scattered)const
	{
		vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
		scattered = Ray(rec.p, reflected + fuzz * Trixs::Core::Random::random_in_unit_sphere());
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal) > 0);
	}
private:
	vec3 albedo;
	float fuzz;
};
}