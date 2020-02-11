#pragma once
#include "Ray.h"
#include "Random.h"
namespace Trixs
{

constexpr double PI = 3.14159256;

class Camera
{
public:
	Camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect,
		float aperture, float focus_dist) {
		lens_radius = aperture / 2;
		float theta = vfov * PI / 180;
		float half_height = tan(theta / 2);
		float half_width = aspect * half_height;
		origin = lookfrom;
		LookAt = lookat;
		up = vup;
		w = unit_vector(lookfrom - lookat);
		u = unit_vector(cross(vup, w));
		v = cross(w, u);
		lowerLeftCorner = origin
			- half_width * focus_dist * u
			- half_height * focus_dist * v
			- focus_dist * w;
		horizontal = 2 * half_width*focus_dist*u;
		vertical = 2 * half_height*focus_dist*v;
	}
	Ray getRay(float s, float t)
	{
		vec3 rd = lens_radius * Trixs::Core::Random::random_in_unit_disk();
		vec3 offset = u * rd.x() + v * rd.y();
		return Ray(origin + offset,
			lowerLeftCorner + s * horizontal + t * vertical
			- origin - offset);
	}
	vec3 getPosition() { return origin; }
	vec3* getPosPTR() { return &origin; }
	vec3 getLookAt() { return LookAt; }
	vec3 getUp() { return up; }
	void moveForward(float amount) { origin.e[2] = origin.z() + amount; }
	void moveUp(float amount) { origin.e[1] = origin.y() + amount; }
	void moveSide(float amount) { origin.e[0] = origin.x() + amount; }
	void moveLookAt(float addx, float addy, float addz)
	{
		LookAt.e[0] += addx;
		LookAt.e[1] += addy;
		LookAt.e[2] += addz;

		w = unit_vector(origin - LookAt);
		u = unit_vector(cross(up, w));
		v = cross(w, u);
	}
private:
	vec3 lowerLeftCorner;
	vec3 horizontal;
	vec3 vertical;
	vec3 origin;
	vec3 u, v, w;
	vec3 LookAt;
	vec3 up;
	float lens_radius;
};
}
