#pragma once
#include "Hitable.h"
namespace Trixs
{

class HittableList : public Hittable
{
public:
	HittableList() {}
	HittableList(Hittable **l, int n) { list = l; list_size = n; }
	virtual bool hit(
		const Ray& r, float tmin, float tmax, hitRecord& rec) const;

private:
	Hittable **list;
	int list_size;
};

bool HittableList::hit(const Ray& r, float t_min, float t_max,hitRecord& rec) const
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