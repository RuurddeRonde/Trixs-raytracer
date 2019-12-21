#pragma once
#include "Hitable.h"
namespace Trixs
{
	class Triangle : public Hittable
	{
	public:
		Triangle(vec3* A, vec3* B, vec3* C, Material* mat);
		virtual bool hit(const Ray& r, float t_min, float t_max, hitRecord& rec)const;
		inline vec3 getNormal()const
		{
			vec3 CA(C->x() - A->x(), C->y() - A->y(), C->z() - A->z());
			vec3 BA(B->x() - A->x(), B->y() - A->y(), B->z() - A->z());
			return normalize(cross(CA, BA));
		}
	private:
		vec3* A, *B, *C;
		Material* matPtr;
	};

}

