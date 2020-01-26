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
		vec3 getPos() { return position; } //cant be const
		vec3 getRot(){ return rotation; }
		vec3 getScale(){ return scale; }
		vec3* getPosPtr() { return &position; }
	private:
		vec3 position;
		vec3 rotation;
		vec3 scale;
	};


}