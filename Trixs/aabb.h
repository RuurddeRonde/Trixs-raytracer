#pragma once
#include "Vec3.h"
#include "Ray.h"
namespace Trixs
{
	inline float ffmin(float a, float b) { return a < b ? a : b; }
	inline float ffmax(float a, float b) { return a > b ? a : b; }

	class aabb {
	public:
		aabb() { _min = vec3(0, 0, 0); _max = vec3(0, 0, 0); }
		aabb(const vec3& a, const vec3& b) { _min = a; _max = b; }

		vec3 min() const { return _min; }
		vec3 max() const { return _max; }

		inline bool hit(const Ray& r, float tmin, float tmax) const {
			for (int a = 0; a < 3; a++) {
				float invD = 1.0f / r.direction()[a];
				float t0 = (min()[a] - r.origin()[a]) * invD;
				float t1 = (max()[a] - r.origin()[a]) * invD;
				if (invD < 0.0f)
					std::swap(t0, t1);
				tmin = t0 > tmin ? t0 : tmin;
				tmax = t1 < tmax ? t1 : tmax;
				if (tmax <= tmin)
					return false;
			}
			return true;
		}
		inline bool collide(aabb other)
		{
			return	(this->min().x() <= other.max().x() && this->max().x() >= other.min().x()) &&
					(this->min().y() <= other.max().y() && this->max().y() >= other.min().y()) &&
					(this->min().z() <= other.max().z() && this->max().z() >= other.min().z());
		}
	private:
		vec3 _min;
		vec3 _max;
	};
}
//return (a.minX <= b.maxX && a.maxX >= b.minX) &&
//(a.minY <= b.maxY && a.maxY >= b.minY) &&
//(a.minZ <= b.maxZ && a.maxZ >= b.minZ);