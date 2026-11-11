#include <math.h>
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

static inline V2 V2sub(V2 v1, V2 v2) {
	return (V2){ v1.x - v2.x, v1.y - v2.y };
}

static inline double V2dot(V2 v1, V2 v2) {
	return (v1.x * v2.x + v1.y * v2.y);
}

static inline double V2mag(V2 v) {
	return sqrt(v.x * v.x + v.y * v.y);
}

static inline V2 V2norm(V2 v) {
	return (V2){ v.x / V2mag(v), v.y / V2mag(v) };
}

static inline V2 V2scale(V2 v, double s) {
	return (V2){ v.x * s, v.y * s };
}

static inline double V2angle(V2 v1, V2 v2) {
	return acos(V2dot(v1, v2) / (V2mag(v1) * V2mag(v2)));
}

static inline double V2dist(V2 v1, V2 v2) {
	return V2mag(V2sub(v1, v2));
}

static inline V2 V2lerp(V2 v1, V2 v2, double t) {
	return V2add(V2scale(v1, (1 - t)), V2scale(v2, t));
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

static inline V3 V3sub(V3 v1, V3 v2) {
	return (V3){ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}

static inline double V3dot(V3 v1, V3 v2) {
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

static inline double V3mag(V3 v) {
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

static inline V3 V3norm(V3 v) {
	double mag = V3mag(v);
	return (V3){ v.x / mag, v.y / mag, v.z / mag };
}

static inline V3 V3scale(V3 v, double s) {
	return (V3){ v.x * s, v.y * s, v.z * s };
}

static inline double V3angle(V3 v1, V3 v2) {
	return acos(V3dot(v1, v2) / (V3mag(v1) * V3mag(v2)));
}

static inline double V3dist(V3 v1, V3 v2) {
	return V3mag(V3sub(v1, v2));
}

static inline V3 V3lerp(V3 v1, V3 v2, double t) {
	return V3add(V3scale(v1, (1 - t)), V3scale(v2, t));
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

static inline V4 V4sub(V4 v1, V4 v2) {
	return (V4){ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w };
}

static inline double V4dot(V4 v1, V4 v2) {
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
}

static inline double V4mag(V4 v) {
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

static inline V4 V4norm(V4 v) {
	double mag = V4mag(v);
	return (V4){ v.x / mag, v.y / mag, v.z / mag, v.w / mag };
}

static inline V4 V4scale(V4 v, double s) {
	return (V4){ v.x * s, v.y * s, v.z * s, v.w * s };
}

static inline double V4angle(V4 v1, V4 v2) {
	return acos(V4dot(v1, v2) / (V4mag(v1) * V4mag(v2)));
}

static inline double V4dist(V4 v1, V4 v2) {
	return V4mag(V4sub(v1, v2));
}

static inline V4 V4lerp(V4 v1, V4 v2, double t) {
	return V4add(V4scale(v1, (1 - t)), V4scale(v2, t));
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

double *Vsub(double *res, double *v1, double *v2, size_t size) {
	for (size_t i = 0; i < size; i++) {
		res[i] = v1[i] - v2[i];
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

double Vmag(double *v, size_t size) {
	double res = 0;
	for (size_t i = 0; i < size; i++) {
		res += v[i] * v[i];
	}
	return sqrt(res);
}

double *Vnorm(double *res, double *v, size_t size) {
	double mag = Vmag(v, size);
	for (size_t i = 0; i < size; i++) {
		res[i] = v[i] / mag;
	}
	return res;
}

double *Vscale(double *res, double *v, double s, size_t size) {
	for (size_t i = 0; i < size; i++) {
		res[i] = v[i] * s;
	}
	return res;
}

double Vangle(double *v1, double *v2, size_t size) {
	return acos(Vdot(v1, v2, size) / (Vmag(v1, size) * Vmag(v2, size)));
}

double Vdist(double *v1, double *v2, size_t size) {
	double res = 0;
	for (size_t i = 0; i < size; i++) {
		double diff = v1[i] - v2[i];
		res += diff * diff;
	}
	return sqrt(res);
}

double *Vlerp(double *res, double *v1, double *v2, double t, size_t size) {
	for (size_t i = 0; i < size; i++) {
		res[i] = v1[i] * (1 - t) + v2[i] * t;
	}
	return res;
}
