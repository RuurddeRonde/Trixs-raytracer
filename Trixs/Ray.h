#pragma once
#include "Vec3.h"
namespace Trixs
{

class Ray
{
public:
	Ray();
	Ray(const vec3& a, const vec3& b);
	vec3 origin()const;
	vec3 direction()const;
	vec3 pointAtParameter(float t)const;

private:
	vec3 A; //origin
	vec3 B; //direction
};

}
