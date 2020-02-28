#pragma once
#include "Material.h"
#include "Random.h"
#include "Texture.h"
#include <string>
namespace Trixs
{

	class Lambertian : public Material
	{
	public:
		Lambertian(Texture* a) : albedo(a) {}
		virtual bool scatter(Ray r_in, const hitRecord& rec, vec3& attenuation, Ray& scattered)const;
		virtual std::string getWritable()const
		{
			std::string writable ="LAMBERTIAN " + albedo->getWritable() + "\n";
			
			return writable;
		}
		virtual vec3 getColor()const { return albedo->value(0.0f, 0.0f, vec3(0.0f, 0.0f, 0.0f)); }
		vec3* getAlbedo() { return &albedo->value(0.0f, 0.0f, vec3(0.0f, 0.0f, 0.0f)); }
	private:
		Texture* albedo;
	};
}