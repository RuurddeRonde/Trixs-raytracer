#include "Triangle.h"


namespace Trixs
{
	Triangle::Triangle(int A, int B, int C, std::vector<vec3>* indices, vec3 normal, Material* mat)
	{
		this->A = A;
		this->B = B;
		this->C = C;
		this->indices = indices;
		this->normal = normal;
		this->matPtr = mat;

		createBoundingBox();
	}
	Triangle::Triangle(int A, int B, int C, std::vector<vec3>* indices, Material * mat)
	{
		this->A = A;
		this->B = B;
		this->C = C;
		this->indices = indices;
		
		vec3 CA(indices->at(C).x() - indices->at(A).x(), indices->at(C).y() - indices->at(A).y(), indices->at(C).z() - indices->at(A).z());
		vec3 BA(indices->at(B).x() - indices->at(A).x(), indices->at(B).y() - indices->at(A).y(), indices->at(B).z() - indices->at(A).z());
		this->normal= normalize(cross(CA, BA));;
		this->matPtr = mat;

		createBoundingBox();
	}
	bool Triangle::hit(const Ray& r, float t_min, float t_max, hitRecord& rec)const
	{
		const float EPSILON = 0.0000001;

		vec3 edge1, edge2, h, s, q, ca, cb, cc;
		float a, f, u, v;

		ca = indices->at(A);
		cb = indices->at(B);
		cc = indices->at(C);

		edge1 = cb - ca;
		edge2 = cc - ca;
		
		h = cross(r.direction(), edge2); //misschien niet direction
		a = dot(edge1, h);
		if (a > -EPSILON && a < EPSILON)
			return false;    // This ray is parallel to this triangle.

		f = 1.0 / a;
		s = r.origin() - ca;
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

	std::string Triangle::getWritable() const
	{
		std::string writable;
		writable += A + " ";
		writable += B + " ";
		writable += C + " ";
		writable += normal.x();
		writable += " ";
		writable += normal.y();
		writable += " ";
		writable += normal.z();
		return writable;
	}

	void Triangle::createBoundingBox()
	{
		//create bounding box
		vec3 max(FLT_MIN, FLT_MIN, FLT_MIN);
		vec3 min(FLT_MAX, FLT_MAX, FLT_MAX);

		//set bounding box at min min min and max max max
		if (indices->at(A).x() < min.x()) { min.setx(indices->at(A).x()); }
		if (indices->at(A).x() > max.x()) { max.setx(indices->at(A).x()); }
		if (indices->at(A).y() < min.y()) { min.sety(indices->at(A).y()); }
		if (indices->at(A).y() > max.y()) { max.sety(indices->at(A).y()); }
		if (indices->at(A).z() < min.z()) { min.setz(indices->at(A).z()); }
		if (indices->at(A).z() > max.z()) { max.setz(indices->at(A).z()); }

		if (indices->at(B).x() < min.x()) { min.setx(indices->at(B).x()); }
		if (indices->at(B).x() > max.x()) { max.setx(indices->at(B).x()); }
		if (indices->at(B).y() < min.y()) { min.sety(indices->at(B).y()); }
		if (indices->at(B).y() > max.y()) { max.sety(indices->at(B).y()); }
		if (indices->at(B).z() < min.z()) { min.setz(indices->at(B).z()); }
		if (indices->at(B).z() > max.z()) { max.setz(indices->at(B).z()); }

		if (indices->at(C).x() < min.x()) { min.setx(indices->at(C).x()); }
		if (indices->at(C).x() > max.x()) { max.setx(indices->at(C).x()); }
		if (indices->at(C).y() < min.y()) { min.sety(indices->at(C).y()); }
		if (indices->at(C).y() > max.y()) { max.sety(indices->at(C).y()); }
		if (indices->at(C).z() < min.z()) { min.setz(indices->at(C).z()); }
		if (indices->at(C).z() > max.z()) { max.setz(indices->at(C).z()); }
		this->boundingBox = aabb(min, max);
	}

	void Triangle::draw()const
	{

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

//if (((verty[i] > y) != (verty[j] > y)) && (x <(vertx[j] - vertx[i]) * (y - verty[i]) / (verty[j] -	verty[i]) + vertx[i]))