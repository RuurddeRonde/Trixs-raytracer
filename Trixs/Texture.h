#pragma once
#include "Vec3.h"
namespace Trixs
{
	class Texture {
	public:
		virtual vec3 value(float u, float v, const vec3& p) const = 0;
		virtual std::string getWritable() const { return ""; };
	};

	class ConstantTexture : public Texture {
	public:
		ConstantTexture() {}
		ConstantTexture(vec3 c) : color(c) {}
		virtual vec3 value(float u, float v, const vec3& p) const {
			return color;
		}
		virtual std::string getWritable() const {
			std::string writable;
			writable += "ConstantTexture ";
			writable += color.x();
			writable += " ";
			writable += color.y();
			writable += " ";
			writable += color.z();
			return writable;
		}
		vec3 color;
	};

	class CheckerTexture : public Texture {
	public:
		CheckerTexture() {}
		CheckerTexture(Texture *t0, Texture *t1) : even(t0), odd(t1) {}
		virtual vec3 value(float u, float v, const vec3& p) const {
			float sines = sin(10 * p.x())*sin(10 * p.y())*sin(10 * p.z());
			if (sines < 0)
				return odd->value(u, v, p);
			else
				return even->value(u, v, p);
		}
	private:
		Texture *odd;
		Texture *even;
	};

	class Imagetexture : public Texture {
	public:
		Imagetexture() {}
		Imagetexture(unsigned char *pixels, int A, int B)
			: data(pixels), nx(A), ny(B) {}
		virtual vec3 value(float u, float v, const vec3& p) const {
			int i = (u)* nx;
			int j = (1 - v) * ny - 0.001;
			if (i < 0) i = 0;
			if (j < 0) j = 0;
			if (i > nx - 1) i = nx - 1;
			if (j > ny - 1) j = ny - 1;
			float r = int(data[3 * i + 3 * nx*j]) / 255.0;
			float g = int(data[3 * i + 3 * nx*j + 1]) / 255.0;
			float b = int(data[3 * i + 3 * nx*j + 2]) / 255.0;
			return vec3(r, g, b);
		}
		unsigned char *data;
		int nx, ny;
	};
}