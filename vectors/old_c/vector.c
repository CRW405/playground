#include "vector.h"

#include <math.h>
#include <stddef.h>

double *Vadd(double *restrict res, double *restrict v1, double *restrict v2, size_t size) {
	for (size_t i = 0; i < size; i++) {
		res[i] = v1[i] + v2[i];
	}
	return res;
}

double *Vsub(double *restrict res, double *restrict v1, double *restrict v2, size_t size) {
	for (size_t i = 0; i < size; i++) {
		res[i] = v1[i] - v2[i];
	}
	return res;
}

double Vdot(double *restrict v1, double *restrict v2, size_t size) {
	double res = 0;
	for (size_t i = 0; i < size; i++) {
		res += v1[i] * v2[i];
	}
	return res;
}

double Vmag(double *restrict v, size_t size) {
	double res = 0;
	for (size_t i = 0; i < size; i++) {
		res += v[i] * v[i];
	}
	return sqrt(res);
}

double *Vnorm(double *restrict res, double *restrict v, size_t size) {
	double mag = Vmag(v, size);
	for (size_t i = 0; i < size; i++) {
		res[i] = v[i] / mag;
	}
	return res;
}

double *Vscale(double *restrict res, double *restrict v, double s, size_t size) {
	for (size_t i = 0; i < size; i++) {
		res[i] = v[i] * s;
	}
	return res;
}

double Vangle(double *restrict v1, double *restrict v2, size_t size) {
	return acos(Vdot(v1, v2, size) / (Vmag(v1, size) * Vmag(v2, size)));
}

double Vdist(double *restrict v1, double *restrict v2, size_t size) {
	double res = 0;
	for (size_t i = 0; i < size; i++) {
		double diff = v1[i] - v2[i];
		res += diff * diff;
	}
	return sqrt(res);
}

double *Vlerp(double *restrict res, double *restrict v1, double *restrict v2, double t, size_t size) {
	for (size_t i = 0; i < size; i++) {
		res[i] = v1[i] * (1 - t) + v2[i] * t;
	}
	return res;
}
