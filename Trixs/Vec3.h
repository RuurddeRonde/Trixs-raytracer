#pragma once
#include <math.h>
#include <stdlib.h>
#include <iostream>
namespace Trixs
{
	class vec3 {
	public:
		vec3() {}
		vec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; }
		inline float x() const { return e[0]; }
		inline float y() const { return e[1]; }
		inline float z() const { return e[2]; }
		inline float r() const { return e[0]; }
		inline float g() const { return e[1]; }
		inline float b() const { return e[2]; }
		inline void setx(float x) { e[0] = x; }
		inline void sety(float y) { e[1] = y; }
		inline void setz(float z) { e[2] = z; }
		inline void setr(float r) { e[0] = r; }
		inline void setg(float g) { e[1] = g; }
		inline void setb(float b) { e[2] = b; }

		inline const vec3& operator+() const { return *this; }
		inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
		inline float operator[](int i) const { return e[i]; }
		inline float& operator[](int i) { return e[i]; }

		inline vec3& operator+=(const vec3 &v2);
		inline vec3& operator-=(const vec3 &v2);
		inline vec3& operator*=(const vec3 &v2);
		inline vec3& operator/=(const vec3 &v2);
		inline bool operator==(const vec3 &v2);
		inline vec3& operator*=(const float t);
		inline vec3& operator/=(const float t);

		inline float length() const { return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }
		inline float squared_length() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
		inline void make_unit_vector();
		float e[3];
	};


	inline std::istream& operator>>(std::istream &is, vec3 &t) {
		is >> t.e[0] >> t.e[1] >> t.e[2];
		return is;
	}

	inline std::ostream& operator<<(std::ostream &os, const vec3 &t) {
		os << t.e[0] << " " << t.e[1] << " " << t.e[2];
		return os;
	}

	inline void vec3::make_unit_vector() {
		float k = 1.0 / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
		e[0] *= k; e[1] *= k; e[2] *= k;
	}

	inline vec3 operator+(const vec3 &v1, const vec3 &v2) {
		return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
	}

	inline vec3 operator-(const vec3 &v1, const vec3 &v2) {
		return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
	}

	inline vec3 operator*(const vec3 &v1, const vec3 &v2) {
		return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
	}

	inline vec3 operator/(const vec3 &v1, const vec3 &v2) {
		return vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
	}

	inline vec3 operator*(float t, const vec3 &v) {
		return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
	}

	inline vec3 operator/(vec3 v, float t) {
		return vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
	}

	inline vec3 operator*(const vec3 &v, float t) {
		return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
	}

	inline bool vec3::operator==(const vec3 &v2)
	{
		if ((e[0] == v2.e[0] && e[1] == v2.e[1] && e[2] == v2.e[2]))
		{
			return true;
		}
		return false;
	}
	inline float dot(const vec3 &v1, const vec3 &v2) {
		return v1.e[0] * v2.e[0]
			+ v1.e[1] * v2.e[1]
			+ v1.e[2] * v2.e[2];
	}

	inline vec3 cross(const vec3 &v1, const vec3 &v2) {
		return vec3(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
			v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2],
			v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
	}

	inline vec3& vec3::operator+=(const vec3 &v) {
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}

	inline vec3& vec3::operator*=(const vec3 &v) {
		e[0] *= v.e[0];
		e[1] *= v.e[1];
		e[2] *= v.e[2];
		return *this;
	}

	inline vec3& vec3::operator/=(const vec3 &v) {
		e[0] /= v.e[0];
		e[1] /= v.e[1];
		e[2] /= v.e[2];
		return *this;
	}

	inline vec3& vec3::operator-=(const vec3& v) {
		e[0] -= v.e[0];
		e[1] -= v.e[1];
		e[2] -= v.e[2];
		return *this;
	}

	inline vec3& vec3::operator*=(const float t) {
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	inline vec3& vec3::operator/=(const float t) {
		float k = 1.0f / t;

		e[0] *= k;
		e[1] *= k;
		e[2] *= k;
		return *this;
	}

	inline vec3 unit_vector(vec3 v) {
		return v / v.length();
	}

	inline vec3 normalize(const vec3 &v)
	{
		float length_of_v = sqrt((v.x() * v.x()) + (v.y() * v.y()) + (v.z() * v.z()));
		return vec3((v.x() / length_of_v), (v.y() / length_of_v), (v.z() / length_of_v));
	}
}