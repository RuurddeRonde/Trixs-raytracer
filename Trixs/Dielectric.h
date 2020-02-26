#pragma once
#include "Material.h"
#include "Random.h"
#include <string>
namespace Trixs
{
	class Dielectric : public Material
	{
	public:
		Dielectric(float ri) : ref_idx(ri) {}
		virtual bool scatter(Ray r_in, const hitRecord& rec, vec3& attenuation, Ray& scattered)const;
		virtual std::string getWritable()const
		{
			std::string writable;
			writable += "DIELECTRIC ";
			writable += ref_idx;
			writable += "\n";
			return writable;
		}
		virtual vec3 getColor()const { return vec3(0.1f, 0.1f, 0.1f); }
		float* getRef() { return &ref_idx; }
	private:
		float ref_idx;
	};
}
