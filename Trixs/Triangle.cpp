#include "Triangle.h"


namespace Trixs
{
	Triangle::Triangle(vec3* A, vec3* B, vec3* C, Material* mat)
	{
		this->A = A;
		this->B = B;
		this->C = C;
		this->matPtr = mat;
	}
	bool Triangle::hit(const Ray& r, float t_min, float t_max, hitRecord& rec)const
	{
		const float EPSILON = 0.0000001;

		vec3 edge1, edge2, h, s, q;
		float a, f, u, v;

		edge1 = *B - *A;
		edge2 = *C - *A;
		
		h = cross(r.direction(), edge2); //misschien niet direction
		a = dot(edge1, h);
		if (a > -EPSILON && a < EPSILON)
			return false;    // This ray is parallel to this triangle.

		f = 1.0 / a;
		s = r.origin() - *A;
		u = f * dot(s, h);
		if (u < 0.0 || u > 1.0)
			return false;

		q = cross(s, edge1);
		v = f * dot(r.direction(), q);
		if (v < 0.0 || u + v > 1.0)
			return false;

		// At this stage we can compute t to find out where the intersection point is on the line.
		float t = f * dot(edge2, q);
		if (t > EPSILON && t < 1 / EPSILON) // ray intersection
		{
			if (t < t_max && t > t_min) //object closer than previous
			{
				rec.t = t;
				rec.p = r.origin() + r.direction() * t;
				rec.normal = this->getNormal();
				rec.matPtr = matPtr;
				return true;
			}
			else
				return false; //this means there is a ray intersection, but it is behind a differend object
		}
		else // This means that there is a line intersection but not a ray intersection.
			return false;
	}

}

/*
https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
bool RayIntersectsTriangle(Vector3D rayOrigin,
						   Vector3D rayVector,
						   Triangle* inTriangle,
						   Vector3D& outIntersectionPoint)
{
	const float EPSILON = 0.0000001;
	Vector3D vertex0 = inTriangle->vertex0; A
	Vector3D vertex1 = inTriangle->vertex1; B
	Vector3D vertex2 = inTriangle->vertex2; C
	Vector3D edge1, edge2, h, s, q;
	float a,f,u,v;
	edge1 = vertex1 - vertex0;
	edge2 = vertex2 - vertex0;
	h = rayVector.crossProduct(edge2);
	a = edge1.dotProduct(h);
	if (a > -EPSILON && a < EPSILON)
		return false;    // This ray is parallel to this triangle.
	f = 1.0/a;
	s = rayOrigin - vertex0;
	u = f * s.dotProduct(h);
	if (u < 0.0 || u > 1.0)
		return false;
	q = s.crossProduct(edge1);
	v = f * rayVector.dotProduct(q);
	if (v < 0.0 || u + v > 1.0)
		return false;
	// At this stage we can compute t to find out where the intersection point is on the line.
	float t = f * edge2.dotProduct(q);
	if (t > EPSILON && t < 1/EPSILON) // ray intersection
	{
		outIntersectionPoint = rayOrigin + rayVector * t;
		return true;
	}
	else // This means that there is a line intersection but not a ray intersection.
		return false;
}

*/