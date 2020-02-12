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

			Yaw = -90.0f;
			Pitch = 0.0f;
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

		//obsolete
		void moveForward(float amount) { origin.e[2] = origin.z() + amount; }
		void moveUp(float amount) { origin.e[1] = origin.y() + amount; }
		void moveSide(float amount) { origin.e[0] = origin.x() + amount; }
		void ProcessMouse(float x, float y)
		{
			Yaw += x;
			Pitch += y;


			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;

			glm::vec3 front;
			front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
			front.y = sin(glm::radians(Pitch));
			front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
			glm::vec3 lookat = glm::vec3(LookAt.e[0], LookAt.e[1], LookAt.e[2] );
			lookat = glm::normalize(front);
			// Also re-calculate the Right and Up vector

			glm::vec3 right = glm::normalize(glm::cross(lookat, glm::vec3(0.0f, 1.0f, 0.0f)));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
			glm::vec3 Up = glm::normalize(glm::cross(right, lookat));

			//up
			up.setx(Up.x);
			up.sety(Up.y);
			up.setz(Up.z);
			//lookat 
			LookAt.setx(lookat.x);
			LookAt.sety(lookat.y);
			LookAt.setz(lookat.z);
			//horizontal = right
			horizontal.setx(right.x);
			horizontal.sety(right.y);
			horizontal.setz(right.z);

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
		float Yaw;
		float Pitch;
	};
}
