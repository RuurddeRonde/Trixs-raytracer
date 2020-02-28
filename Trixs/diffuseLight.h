#pragma once
#include "Material.h"

namespace Trixs
{
	class diffuseLight : public Material {
	public:
		diffuseLight(vec3 *a) : emit(a) {}
		virtual bool scatter(Ray r_in, const hitRecord& rec, vec3& attenuation, Ray& scattered) const 
		{
			return false;
		}
		virtual vec3 emitted(float u, float v, const vec3& p) const 
		{
			return *emit;
		}
		virtual std::string getWritable()const
		{
			return std::string("Diffuse light");
		}
		virtual vec3 getColor() const
		{
			return *emit;
		}
		vec3* getEmit() { return emit; }

		vec3 *emit;
	};
}