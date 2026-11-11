#include <stdlib.h>

typedef union V2 {
	struct {
		double x;
		double y;
	};
	double comp[2];
} V2;

static inline V2 V2add(V2 v1, V2 v2) {
	return (V2){ v1.x + v2.x, v1.y + v2.y };
}

static inline double V2dot(V2 v1, V2 v2) {
	return (v1.x * v2.x + v1.y * v2.y);
}

typedef union V3 {
	struct {
		double x;
		double y;
		double z;
	};
	double comp[3];
} V3;

static inline V3 V3add(V3 v1, V3 v2) {
	return (V3){ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

static inline double V3dot(V3 v1, V3 v2) {
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

static inline V3 V3cross(V3 v1, V3 v2) {
	return (V3){
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
	};
}

typedef union V4 {
	struct {
		double x;
		double y;
		double z;
		double w;
	};
	double comp[4];
} V4;

static inline V4 V4add(V4 v1, V4 v2) {
	return (V4){ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w };
}

static inline double V4dot(V4 v1, V4 v2) {
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
}

#define V(name, n)      \
	typedef struct {    \
		double comp[n]; \
	} name;

double *Vadd(double *res, double *v1, double *v2, size_t size) {
	for (size_t i = 0; i < size; i++) {
		res[i] = v1[i] + v2[i];
	}
	return res;
}

double Vdot(double *v1, double *v2, size_t size) {
	double res = 0;
	for (size_t i = 0; i < size; i++) {
		res += v1[i] * v2[i];
	}
	return res;
}
