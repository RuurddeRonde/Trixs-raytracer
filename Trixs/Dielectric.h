#pragma once
#include "Material.h"
#include "Random.h"
namespace Trixs
{

class Dielectric : public Material
{
public:
	Dielectric(float ri) : ref_idx(ri) {}
	virtual bool scatter(Ray r_in, const hitRecord& rec, vec3& attenuation, Ray& scattered)const;
private:
	float ref_idx;
};
}
