#pragma once
#include "Material.h"
#include "Random.h"
namespace Trixs
{

class Dielectric : public Material
{
public:
	Dielectric(float ri) : ref_idx(ri) {}
	virtual bool scatter(Ray r_in, const hitRecord& rec, vec3& attenuation, Ray& scattered)const
	{
		vec3 outward_normal;
		vec3 reflected = reflect(r_in.direction(), rec.normal);
		float ni_over_nt;
		attenuation = vec3(1.0, 1.0, 1.0);
		vec3 refracted;
		float reflect_prob;
		float cosine;

		if (dot(r_in.direction(), rec.normal) > 0) {
			outward_normal = -rec.normal;
			ni_over_nt = ref_idx;
			cosine = ref_idx * dot(r_in.direction(), rec.normal)
				/ r_in.direction().length();
		}
		else {
			outward_normal = rec.normal;
			ni_over_nt = 1.0 / ref_idx;
			cosine = -dot(r_in.direction(), rec.normal)
				/ r_in.direction().length();
		}

		if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
		{
			reflect_prob = schlick(cosine, ref_idx);
		}
		else {
			reflect_prob = 1.0;
		}

		if (Trixs::Core::Random::randomDouble() < reflect_prob) {
			scattered = Ray(rec.p, reflected);
		}
		else {
			scattered = Ray(rec.p, refracted);
		}

		return true;
	}
private:
	float ref_idx;
};
}
