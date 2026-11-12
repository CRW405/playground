#ifndef VECTORS_VECTOR_HPP
#define VECTORS_VECTOR_HPP

#include <cmath>
#include <cstddef>

union V2 {
	enum { dimension = 2 }; // Our alignment breaks indexing, this fixes it. Supposedly no tradeoff
	__extension__ struct {  // C++ is stupid and does not allow anonymous structs, this is a workaround
		double x;
		double y;
	};
	alignas(16) double comp[2];

	double       &operator[](std::size_t index) { return comp[index]; }
	const double &operator[](std::size_t index) const { return comp[index]; }
};

union V3 {
	enum { dimension = 3 };
	__extension__ struct {
		double x;
		double y;
		double z;
	};
	alignas(16) double comp[3];

	double       &operator[](std::size_t index) { return comp[index]; }
	const double &operator[](std::size_t index) const { return comp[index]; }
};

union V4 {
	enum { dimension = 4 };
	__extension__ struct {
		double x;
		double y;
		double z;
		double w;
	};
	alignas(16) double comp[4];

	double       &operator[](std::size_t index) { return comp[index]; }
	const double &operator[](std::size_t index) const { return comp[index]; }
};

template <std::size_t N>
struct Vector {
	enum { dimension = N };
	alignas(16) double comp[N];

	double       &operator[](std::size_t index) { return comp[index]; }
	const double &operator[](std::size_t index) const { return comp[index]; }
};

#define V(name, n) using name = Vector<n>;

inline V2 V2add(const V2 &v1, const V2 &v2) {
	return V2{
		{ v1.x + v2.x, v1.y + v2.y }
	};
}

inline V2 V2sub(const V2 &v1, const V2 &v2) {
	return V2{
		{ v1.x - v2.x, v1.y - v2.y }
	};
}

inline double V2dot(const V2 &v1, const V2 &v2) {
	return v1.x * v2.x + v1.y * v2.y;
}

inline double V2mag(const V2 &v) {
	return std::sqrt(v.x * v.x + v.y * v.y);
}

inline V2 V2norm(const V2 &v) {
	const double mag = V2mag(v);
	return V2{
		{ v.x / mag, v.y / mag }
	};
}

inline V2 V2scale(const V2 &v, double s) {
	return V2{
		{ v.x * s, v.y * s }
	};
}

inline double V2angle(const V2 &v1, const V2 &v2) {
	return std::acos(V2dot(v1, v2) / (V2mag(v1) * V2mag(v2)));
}

inline double V2dist(const V2 &v1, const V2 &v2) {
	const double x = v1.x - v2.x;
	const double y = v1.y - v2.y;
	return std::sqrt(x * x + y * y);
}

inline V2 V2lerp(const V2 &v1, const V2 &v2, double t) {
	return V2{
		{ v1.x * (1.0 - t) + v2.x * t, v1.y * (1.0 - t) + v2.y * t }
	};
}

inline V3 V3add(const V3 &v1, const V3 &v2) {
	return V3{
		{ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z }
	};
}

inline V3 V3sub(const V3 &v1, const V3 &v2) {
	return V3{
		{ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z }
	};
}

inline double V3dot(const V3 &v1, const V3 &v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline double V3mag(const V3 &v) {
	return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline V3 V3norm(const V3 &v) {
	const double mag = V3mag(v);
	return V3{
		{ v.x / mag, v.y / mag, v.z / mag }
	};
}

inline V3 V3scale(const V3 &v, double s) {
	return V3{
		{ v.x * s, v.y * s, v.z * s }
	};
}

inline double V3angle(const V3 &v1, const V3 &v2) {
	return std::acos(V3dot(v1, v2) / (V3mag(v1) * V3mag(v2)));
}

inline double V3dist(const V3 &v1, const V3 &v2) {
	const double x = v1.x - v2.x;
	const double y = v1.y - v2.y;
	const double z = v1.z - v2.z;
	return std::sqrt(x * x + y * y + z * z);
}

inline V3 V3lerp(const V3 &v1, const V3 &v2, double t) {
	return V3{
		{ v1.x * (1.0 - t) + v2.x * t,
         v1.y * (1.0 - t) + v2.y * t,
         v1.z * (1.0 - t) + v2.z * t }
	};
}

inline V3 V3cross(const V3 &v1, const V3 &v2) {
	return V3{
		{ v1.y * v2.z - v1.z * v2.y,
         v1.z * v2.x - v1.x * v2.z,
         v1.x * v2.y - v1.y * v2.x }
	};
}

inline V4 V4add(const V4 &v1, const V4 &v2) {
	return V4{
		{ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w }
	};
}

inline V4 V4sub(const V4 &v1, const V4 &v2) {
	return V4{
		{ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w }
	};
}

inline double V4dot(const V4 &v1, const V4 &v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

inline double V4mag(const V4 &v) {
	return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

inline V4 V4norm(const V4 &v) {
	const double mag = V4mag(v);
	return V4{
		{ v.x / mag, v.y / mag, v.z / mag, v.w / mag }
	};
}

inline V4 V4scale(const V4 &v, double s) {
	return V4{
		{ v.x * s, v.y * s, v.z * s, v.w * s }
	};
}

inline double V4angle(const V4 &v1, const V4 &v2) {
	return std::acos(V4dot(v1, v2) / (V4mag(v1) * V4mag(v2)));
}

inline double V4dist(const V4 &v1, const V4 &v2) {
	const double x = v1.x - v2.x;
	const double y = v1.y - v2.y;
	const double z = v1.z - v2.z;
	const double w = v1.w - v2.w;
	return std::sqrt(x * x + y * y + z * z + w * w);
}

inline V4 V4lerp(const V4 &v1, const V4 &v2, double t) {
	return V4{
		{ v1.x * (1.0 - t) + v2.x * t,
         v1.y * (1.0 - t) + v2.y * t,
         v1.z * (1.0 - t) + v2.z * t,
         v1.w * (1.0 - t) + v2.w * t }
	};
}

inline V2 operator+(const V2 &v1, const V2 &v2) { return V2add(v1, v2); }
inline V2 operator-(const V2 &v1, const V2 &v2) { return V2sub(v1, v2); }
inline V2 operator*(const V2 &v, double s) { return V2scale(v, s); }
inline V2 operator*(double s, const V2 &v) { return V2scale(v, s); }
inline V2 operator/(const V2 &v, double s) { return V2scale(v, 1.0 / s); }

inline V3 operator+(const V3 &v1, const V3 &v2) { return V3add(v1, v2); }
inline V3 operator-(const V3 &v1, const V3 &v2) { return V3sub(v1, v2); }
inline V3 operator*(const V3 &v, double s) { return V3scale(v, s); }
inline V3 operator*(double s, const V3 &v) { return V3scale(v, s); }
inline V3 operator/(const V3 &v, double s) { return V3scale(v, 1.0 / s); }

inline V4 operator+(const V4 &v1, const V4 &v2) { return V4add(v1, v2); }
inline V4 operator-(const V4 &v1, const V4 &v2) { return V4sub(v1, v2); }
inline V4 operator*(const V4 &v, double s) { return V4scale(v, s); }
inline V4 operator*(double s, const V4 &v) { return V4scale(v, s); }
inline V4 operator/(const V4 &v, double s) { return V4scale(v, 1.0 / s); }

template <typename Vtype>
Vtype operator+(const Vtype &v1, const Vtype &v2) {
	Vtype res{};
	for (std::size_t i = 0; i < Vtype::dimension; ++i) {
		res[i] = v1[i] + v2[i];
	}
	return res;
}

template <typename Vtype>
Vtype operator-(const Vtype &v1, const Vtype &v2) {
	Vtype res{};
	for (std::size_t i = 0; i < Vtype::dimension; ++i) {
		res[i] = v1[i] - v2[i];
	}
	return res;
}

template <typename Vtype>
Vtype operator*(const Vtype &v, double s) {
	Vtype res{};
	for (std::size_t i = 0; i < Vtype::dimension; ++i) {
		res[i] = v[i] * s;
	}
	return res;
}

template <typename Vtype>
Vtype operator*(double s, const Vtype &v) {
	return v * s;
}

template <typename Vtype>
Vtype operator/(const Vtype &v, double s) {
	Vtype res{};
	for (std::size_t i = 0; i < Vtype::dimension; ++i) {
		res[i] = v[i] / s;
	}
	return res;
}

template <typename Vtype>
Vtype &operator+=(Vtype &v1, const Vtype &v2) {
	for (std::size_t i = 0; i < Vtype::dimension; ++i) {
		v1[i] += v2[i];
	}
	return v1;
}

template <typename Vtype>
Vtype &operator-=(Vtype &v1, const Vtype &v2) {
	for (std::size_t i = 0; i < Vtype::dimension; ++i) {
		v1[i] -= v2[i];
	}
	return v1;
}

template <typename Vtype>
Vtype &operator*=(Vtype &v, double s) {
	for (std::size_t i = 0; i < Vtype::dimension; ++i) {
		v[i] *= s;
	}
	return v;
}

template <typename Vtype>
Vtype &operator/=(Vtype &v, double s) {
	for (std::size_t i = 0; i < Vtype::dimension; ++i) {
		v[i] /= s;
	}
	return v;
}

template <typename Vtype>
Vtype Vadd(const Vtype &v1, const Vtype &v2) {
	return v1 + v2;
}

template <typename Vtype>
Vtype Vsub(const Vtype &v1, const Vtype &v2) {
	return v1 - v2;
}

template <typename Vtype>
double Vdot(const Vtype &v1, const Vtype &v2) {
	double res = 0.0;
	for (std::size_t i = 0; i < Vtype::dimension; ++i) {
		res += v1[i] * v2[i];
	}
	return res;
}

template <typename Vtype>
double Vmag(const Vtype &v) {
	return std::sqrt(Vdot(v, v));
}

template <typename Vtype>
Vtype Vnorm(const Vtype &v) {
	return v / Vmag(v);
}

template <typename Vtype>
Vtype Vscale(const Vtype &v, double s) {
	return v * s;
}

template <typename Vtype>
double Vangle(const Vtype &v1, const Vtype &v2) {
	return std::acos(Vdot(v1, v2) / (Vmag(v1) * Vmag(v2)));
}

template <typename Vtype>
double Vdist(const Vtype &v1, const Vtype &v2) {
	return Vmag(v1 - v2);
}

template <typename Vtype>
Vtype Vlerp(const Vtype &v1, const Vtype &v2, double t) {
	return v1 * (1.0 - t) + v2 * t;
}

#endif
