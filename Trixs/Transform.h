#pragma once
#include "Vec3.h"
namespace Trixs
{
	class Transform
	{
	public:
		Transform();
		Transform(vec3 pos, vec3 rot, vec3 scl);
		//Transform(const Transform &t2);
		~Transform();
		vec3 getPos() { return position; } //cant be const
		vec3 getRot(){ return rotation; }
		vec3 getScale(){ return scale; }
		vec3* getPosPtr() { return &position; }
		vec3* getRotPtr() { return &rotation; }
		vec3* getScalePtr() { return &scale; }
	private:
		vec3 position;
		vec3 rotation;
		vec3 scale;
	};


}