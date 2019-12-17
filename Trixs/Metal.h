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
	virtual bool scatter(Ray r_in, const hitRecord& rec, vec3& attenuation, Ray& scattered)const;
private:
	vec3 albedo;
	float fuzz;
};
}