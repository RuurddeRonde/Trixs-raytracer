#pragma once
#include "Ray.h"
#include "Random.h"
#include "../glm/glm/glm.hpp"
namespace Trixs
{
	constexpr double PI = 3.14159256;

	class Camera
	{
	public:
		Camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect,
			float aperture, float focus_dist) {
			this->vfov = vfov;
			this->aspect = aspect;
			this->aperture = aperture;
			this->focus_dist = focus_dist;
			setCam(lookfrom, lookat, vup, vfov, aspect, aperture, focus_dist);
		}

		Ray getRay(float s, float t) {
			vec3 rd = lens_radius * Core::Random::random_in_unit_disk();
			vec3 offset = u * rd.x() + v * rd.y();
			return Ray(origin + offset,
				lowerLeftCorner + s * horizontal + t * vertical
				- origin - offset);
		}
		void resetCamera(vec3 lookfrom, vec3 lookat, vec3 vup) {
			setCam(lookfrom, lookat, vup, vfov, aspect, aperture, focus_dist);
		}
		void resetCamera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect,
			float aperture, float focus_dist) {
			setCam(lookfrom, lookat, vup, vfov, aspect, aperture, focus_dist);
		}
		vec3 getPosition() { return origin; }
		vec3* getPosPTR() { return &origin; }
		vec3 getUp() { return u; }
		void setPos(vec3 pos) { origin = pos; }
	private:
		void setCam(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect,
			float aperture, float focus_dist)
		{
			lens_radius = aperture / 2;
			float theta = vfov * PI / 180;
			float half_height = tan(theta / 2);
			float half_width = aspect * half_height;
			origin = lookfrom;
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

		vec3 origin;
		vec3 lowerLeftCorner;
		vec3 horizontal;
		vec3 vertical;
		vec3 u, v, w;
		float lens_radius;
		float vfov;
		float aspect;
		float aperture;
		float focus_dist;
	};
}
