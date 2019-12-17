#pragma once
#include "Material.h"
#include "Random.h"
namespace Trixs
{

class Lambertian : public Material
{
public:
	Lambertian(const vec3& a) : albedo(a){}
	virtual bool scatter(Ray r_in, const hitRecord& rec, vec3& attenuation, Ray& scattered)const;
private:
	vec3 albedo;
};
}