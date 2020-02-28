#pragma once
#include "Hitable.h"
namespace Trixs
{
	class Material
	{
	public:
		virtual bool scatter(Ray r_in, const hitRecord& rec, vec3& attenuation, Ray& scattered) const = 0;
		virtual vec3 emitted(float u, float v, const vec3& p) const {
			return vec3(0, 0, 0);
		}
		virtual std::string getWritable()const = 0;
		virtual vec3 getColor() const = 0;
	private:

	};
}