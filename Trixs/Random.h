#pragma once
#include <random>
#include <functional>
#include "Vec3.h"
namespace Trixs
{
	namespace Core
	{
		class Random
		{
		public:
			static double randomDouble(double min = 0.0, double max = 1.0)
			{
				static std::uniform_real_distribution<double> distribution(0.0, 1.0);
				static std::mt19937 generator;
				static std::function<double()> rand_generator =
					std::bind(distribution, generator);
				return rand_generator();
			}
			static vec3 random_in_unit_sphere() {
				vec3 p;
				do {
					p = 2.0*vec3(Core::Random::randomDouble(), Core::Random::randomDouble(), Core::Random::randomDouble()) - vec3(1, 1, 1);
				} while (p.squared_length() >= 1.0);
				return p;
			}
			static vec3 random_in_unit_disk() {
				vec3 p;
				do {
					p = 2.0*vec3(randomDouble(), randomDouble(), 0) - vec3(1, 1, 0);
				} while (dot(p, p) >= 1.0);
				return p;
			}
		};
	}
}