#pragma once
#include "Hitable.h"
#include "aabb.h"
#include <vector>
namespace Trixs
{
	class Triangle : public Hittable
	{
	public:
		Triangle(int A, int B, int C, std::vector<vec3>* indices, vec3 normal, Material* mat);
		Triangle(int A, int B, int C, std::vector<vec3>* indices, Material* mat);
		virtual bool hit(const Ray& r, float t_min, float t_max, hitRecord& rec)const;
		virtual void draw() const override;
		inline vec3 getNormal()const
		{
			return normal;
		}
		inline aabb getBoundingBox() { return boundingBox; }
		virtual std::string getWritable()const override;
	private:
		std::vector<vec3>* indices;
		int A, B, C;
		vec3 normal;
		Material* matPtr;
		aabb boundingBox;

		void createBoundingBox();
	};

}

