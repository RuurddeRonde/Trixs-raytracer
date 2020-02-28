#pragma once
#include "Metal.h"
#include "Dielectric.h"
#include "Lambertian.h"
#include "RayBehaviour.h"
namespace Trixs
{
	bool Metal::scatter(Ray r_in, const hitRecord& rec, vec3& attenuation, Ray& scattered)const
	{
		vec3 reflected = RayBehaviour::reflect(unit_vector(r_in.direction()), rec.normal);
		scattered = Ray(rec.p, reflected + fuzz * Trixs::Core::Random::random_in_unit_sphere());
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal) > 0);
	}
	bool Lambertian::scatter(Ray r_in, const hitRecord& rec, vec3& attenuation, Ray& scattered)const
	{
		vec3 target = rec.p + rec.normal + Trixs::Core::Random::random_in_unit_sphere();
		scattered = Ray(rec.p, target - rec.p);
		attenuation = albedo->value(rec.u, rec.v, rec.p);
		return true;
	}
	bool Dielectric::scatter(Ray r_in, const hitRecord& rec, vec3& attenuation, Ray& scattered)const
	{
		vec3 outward_normal;
		vec3 reflected = RayBehaviour::reflect(r_in.direction(), rec.normal);
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

		if (RayBehaviour::refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
		{
			reflect_prob = RayBehaviour::schlick(cosine, ref_idx);
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
}