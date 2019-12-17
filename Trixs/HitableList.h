#pragma once
#include "Hitable.h"
namespace Trixs
{

class HittableList : public Hittable
{
public:
	HittableList() {}
	HittableList(Hittable **l, int n) { list = l; list_size = n; }
	virtual bool hit(const Ray& r, float tmin, float tmax, hitRecord& rec) const;

private:
	Hittable **list;
	int list_size;
};


}