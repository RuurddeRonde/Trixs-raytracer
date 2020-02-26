#pragma once
#include "Material.h"
#include "Random.h"
#include <string>
namespace Trixs
{

	class Lambertian : public Material
	{
	public:
		Lambertian(const vec3& a) : albedo(a) {}
		virtual bool scatter(Ray r_in, const hitRecord& rec, vec3& attenuation, Ray& scattered)const;
		virtual std::string getWritable()const
		{
			std::string writable ="LAMBERTIAN " + std::to_string( albedo.x()) + std::to_string(albedo.y()) + std::to_string(albedo.z()) + "\n";
			
			return writable;
		}
		virtual vec3 getColor()const { return albedo; }
		vec3* getAlbedo() { return &albedo; }
	private:
		vec3 albedo;
	};
}