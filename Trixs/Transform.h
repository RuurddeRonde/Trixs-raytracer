#pragma once
#include "Vec3.h"
namespace Trixs
{
	class Transform
	{
	public:
		Transform();
		Transform(vec3 pos, vec3 rot, vec3 scl);
		~Transform();
		vec3 getPos()const { return position; }
		vec3 getRot()const { return rotation; }
		vec3 getScale()const { return scale; }
	private:
		vec3 position;
		vec3 rotation;
		vec3 scale;
	};


}