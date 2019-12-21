#pragma once
#include "Hitable.h"
#include <vector>
namespace Trixs
{
	class HitableObject : public Hittable
	{
	public:
		HitableObject(int nTriangles, int nVertices, const int *vertexIndices, const vec3* positions, vec3* normals);
		virtual bool hit(const Ray& r, float t_min, float t_max, hitRecord& rec)const;
	private:
		//transform objectToWorld
		int nTriangles;
		int nVertices;
		std::vector<int> vertexIndices;
		std::unique_ptr<vec3[]> vertexPositions;
		std::unique_ptr<vec3[]> vertexNormals;
	};


}
