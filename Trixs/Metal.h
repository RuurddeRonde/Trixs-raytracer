#pragma once
#include "Material.h"
#include "Random.h"

namespace Trixs
{

	class Metal : public Material
	{
	public:
		Metal(const vec3& a, float f) : albedo(a)
		{
			if (f < 1.0)
			{
				fuzz = f;
			}
			else
			{
				fuzz = 1.0;
			}
		}
		virtual bool scatter(Ray r_in, const hitRecord& rec, vec3& attenuation, Ray& scattered)const;
		virtual std::string getWritable()const
		{
			std::string writable;
			writable += "METAL ";
			writable += albedo.x();
			writable += " ";
			writable += albedo.y();
			writable += " ";
			writable += albedo.z();
			writable += " ";
			writable += fuzz;
			writable += "\n";
			return writable;
		}
		virtual vec3 getColor()const { return albedo; }
		vec3* getAlbedo() { return &albedo; }
		float* getFuzz() { return &fuzz; }
	private:
		vec3 albedo;
		float fuzz;
	};
}