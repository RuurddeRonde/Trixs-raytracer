#pragma once
#include "Vec3.h"
namespace Trixs
{
	class Transform
	{
	public:
		Transform(vec3 pos, vec3 rot, vec3 scl);
		~Transform();

	private:
		vec3 position;
		vec3 rotation;
		vec3 scale;
	};

	Transform::Transform(vec3 pos, vec3 rot, vec3 scale) : position(pos), rotation(rot), scale(scale)
	{
	}

	Transform::~Transform()
	{
	}

}