#include "Transform.h"

namespace Trixs
{

	Transform::Transform() : position(vec3(0.0, 0.0, 0.0)), rotation(vec3(0.0, 0.0, 0.0)), scale(vec3(0.0, 0.0, 0.0))
	{
	}

	Transform::Transform(vec3 pos, vec3 rot, vec3 scale) : position(pos), rotation(rot), scale(scale)
	{
	}

	Transform::~Transform()
	{
	}
}