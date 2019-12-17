#include "HitableList.h"

namespace Trixs
{
	bool HittableList::hit(const Ray& r, float t_min, float t_max, hitRecord& rec) const
	{
		hitRecord temp_rec;
		bool hit_anything = false;
		double closest_so_far = t_max;
		for (int i = 0; i < list_size; i++) {
			if (list[i]->hit(r, t_min, closest_so_far, temp_rec)) {
				hit_anything = true;
				closest_so_far = temp_rec.t;
				rec = temp_rec;
			}
		}
		return hit_anything;
	}
}