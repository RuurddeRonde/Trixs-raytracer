#include "HitableObject.h"

namespace Trixs
{


HitableObject::HitableObject(int nTriangles, int nVertices, const int * vertexIndices, const vec3 * positions, vec3 * normals)
{
	this->nTriangles = nTriangles;
	this->nVertices = nVertices;
	for (auto i = 0; i < nVertices; i++)
	{
		this->vertexIndices.push_back(vertexIndices[i]);
		this->vertexPositions[i] = positions[i];
		this->vertexNormals[i] = normals[i];
	}
	
}

bool HitableObject::hit(const Ray & r, float t_min, float t_max, hitRecord & rec) const
{
	return false;
}
}
