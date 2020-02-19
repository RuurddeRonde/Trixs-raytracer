#pragma once
#include "Vec3.h"

namespace Trixs
{
	struct Vertex {
		Vertex() {}
		Vertex(vec3 pos, vec3 norm) : Position(pos), Normal(norm) {}
		vec3 Position;
		vec3 Normal;
	};
}