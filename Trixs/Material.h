#pragma once
#include "Hitable.h"
namespace Trixs
{
	class Material
	{
	public:
		virtual bool scatter(Ray r_in, const hitRecord& rec, vec3& attenuation, Ray& scattered) const = 0;
		virtual std::string getWritable()const = 0;
		virtual vec3 getColor() const = 0;
	private:

	};
}