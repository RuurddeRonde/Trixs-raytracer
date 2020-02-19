#pragma once
#include "Hitable.h"
#include "aabb.h"
#include <vector>
#include "vertex.h"
namespace Trixs
{
	class Triangle : public Hittable
	{
	public:
		Triangle(int A, int B, int C, std::vector<Vertex>* vertices, vec3 normal, Material* mat);
		Triangle(int A, int B, int C, std::vector<Vertex>* vertices, Material* mat);
		virtual bool hit(const Ray& r, float t_min, float t_max, hitRecord& rec)const;
		virtual void draw() const override;
		inline vec3 getNormal()const
		{
			return normal;
		}
		inline aabb getBoundingBox() { return boundingBox; }
		virtual std::string getWritable() override;
		void setVerticesPointer(std::vector<Vertex>* vertices) { this->vertices = vertices; }
	private:
		std::vector<Vertex>* vertices;
		int A, B, C;
		vec3 normal;
		Material* matPtr;
		aabb boundingBox;

		void createBoundingBox();
	};

}

