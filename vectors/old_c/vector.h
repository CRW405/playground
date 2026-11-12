/**
 * @file vector.h
 * @brief Small double-precision vector math library.
 *
 * Provides two families of operations:
 *
 * - Fixed-size vectors `V2`, `V3` and `V4`, implemented as `static inline`
 *   functions so they can be used without a library link.
 * - Variable-size vectors, stored as a plain `double` array of `size`
 *   components, implemented in `vector.c`. These operate in place through a
 *   caller-provided result buffer.
 *
 * All angles are in radians.
 *
 * The fixed-size types are declared `alignas(16)` so they can be loaded and
 * stored with SIMD instructions. The variable-size functions mark their
 * pointers `restrict`, so result buffers must not overlap their inputs.
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>
#include <stdalign.h>
#include <stddef.h>

/* ------------------------------------------------------------------------- */
/* Fixed-size vectors                                                        */
/* ------------------------------------------------------------------------- */

/**
 * @brief 2-component vector.
 *
 * Components are accessible either by name (`x`, `y`) or by index
 * (`comp[0]`, `comp[1]`). The type is 16-byte aligned.
 */
typedef union V2 {
	struct {
		double x; /**< First component. */
		double y; /**< Second component. */
	};
	alignas(16) double comp[2]; /**< Indexed, 16-byte aligned component view. */
} V2;

/**
 * @brief Component-wise addition.
 * @param v1 Left operand.
 * @param v2 Right operand.
 * @return `v1 + v2`.
 */
static inline V2 V2add(V2 v1, V2 v2) {
	return (V2){{ v1.x + v2.x, v1.y + v2.y }};
}

/**
 * @brief Component-wise subtraction.
 * @param v1 Left operand.
 * @param v2 Right operand.
 * @return `v1 - v2`.
 */
static inline V2 V2sub(V2 v1, V2 v2) {
	return (V2){{ v1.x - v2.x, v1.y - v2.y }};
}

/**
 * @brief Dot product.
 * @param v1 Left operand.
 * @param v2 Right operand.
 * @return Scalar dot product of @p v1 and @p v2.
 */
static inline double V2dot(V2 v1, V2 v2) {
	return (v1.x * v2.x + v1.y * v2.y);
}

/**
 * @brief Euclidean length.
 * @param v Vector to measure.
 * @return Magnitude (norm) of @p v.
 */
static inline double V2mag(V2 v) {
	return sqrt(v.x * v.x + v.y * v.y);
}

/**
 * @brief Normalize to unit length.
 * @param v Vector to normalize; must be non-zero.
 * @return Unit vector in the direction of @p v.
 */
static inline V2 V2norm(V2 v) {
	return (V2){{ v.x / V2mag(v), v.y / V2mag(v) }};
}

/**
 * @brief Multiply by a scalar.
 * @param v Vector to scale.
 * @param s Scale factor.
 * @return `v * s`.
 */
static inline V2 V2scale(V2 v, double s) {
	return (V2){{ v.x * s, v.y * s }};
}

/**
 * @brief Angle between two vectors.
 * @param v1 First vector; must be non-zero.
 * @param v2 Second vector; must be non-zero.
 * @return Angle between @p v1 and @p v2 in radians, in `[0, pi]`.
 */
static inline double V2angle(V2 v1, V2 v2) {
	return acos(V2dot(v1, v2) / (V2mag(v1) * V2mag(v2)));
}

/**
 * @brief Euclidean distance between two points.
 * @param v1 First point.
 * @param v2 Second point.
 * @return Distance between @p v1 and @p v2.
 */
static inline double V2dist(V2 v1, V2 v2) {
	return V2mag(V2sub(v1, v2));
}

/**
 * @brief Linear interpolation.
 * @param v1 Value at `t == 0`.
 * @param v2 Value at `t == 1`.
 * @param t Interpolation factor, normally in `[0, 1]`.
 * @return `v1 * (1 - t) + v2 * t`.
 */
static inline V2 V2lerp(V2 v1, V2 v2, double t) {
	return V2add(V2scale(v1, (1 - t)), V2scale(v2, t));
}

/**
 * @brief 3-component vector.
 *
 * Components are accessible either by name (`x`, `y`, `z`) or by index
 * (`comp[0]` .. `comp[2]`). The type is 16-byte aligned and therefore
 * padded to 32 bytes.
 */
typedef union V3 {
	struct {
		double x; /**< First component. */
		double y; /**< Second component. */
		double z; /**< Third component. */
	};
	alignas(16) double comp[3]; /**< Indexed, 16-byte aligned component view. */
} V3;

/**
 * @brief Component-wise addition.
 * @param v1 Left operand.
 * @param v2 Right operand.
 * @return `v1 + v2`.
 */
static inline V3 V3add(V3 v1, V3 v2) {
	return (V3){{ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z }};
}

/**
 * @brief Component-wise subtraction.
 * @param v1 Left operand.
 * @param v2 Right operand.
 * @return `v1 - v2`.
 */
static inline V3 V3sub(V3 v1, V3 v2) {
	return (V3){{ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z }};
}

/**
 * @brief Dot product.
 * @param v1 Left operand.
 * @param v2 Right operand.
 * @return Scalar dot product of @p v1 and @p v2.
 */
static inline double V3dot(V3 v1, V3 v2) {
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

/**
 * @brief Euclidean length.
 * @param v Vector to measure.
 * @return Magnitude (norm) of @p v.
 */
static inline double V3mag(V3 v) {
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

/**
 * @brief Normalize to unit length.
 * @param v Vector to normalize; must be non-zero.
 * @return Unit vector in the direction of @p v.
 */
static inline V3 V3norm(V3 v) {
	double mag = V3mag(v);
	return (V3){{ v.x / mag, v.y / mag, v.z / mag }};
}

/**
 * @brief Multiply by a scalar.
 * @param v Vector to scale.
 * @param s Scale factor.
 * @return `v * s`.
 */
static inline V3 V3scale(V3 v, double s) {
	return (V3){{ v.x * s, v.y * s, v.z * s }};
}

/**
 * @brief Angle between two vectors.
 * @param v1 First vector; must be non-zero.
 * @param v2 Second vector; must be non-zero.
 * @return Angle between @p v1 and @p v2 in radians, in `[0, pi]`.
 */
static inline double V3angle(V3 v1, V3 v2) {
	return acos(V3dot(v1, v2) / (V3mag(v1) * V3mag(v2)));
}

/**
 * @brief Euclidean distance between two points.
 * @param v1 First point.
 * @param v2 Second point.
 * @return Distance between @p v1 and @p v2.
 */
static inline double V3dist(V3 v1, V3 v2) {
	return V3mag(V3sub(v1, v2));
}

/**
 * @brief Linear interpolation.
 * @param v1 Value at `t == 0`.
 * @param v2 Value at `t == 1`.
 * @param t Interpolation factor, normally in `[0, 1]`.
 * @return `v1 * (1 - t) + v2 * t`.
 */
static inline V3 V3lerp(V3 v1, V3 v2, double t) {
	return V3add(V3scale(v1, (1 - t)), V3scale(v2, t));
}

/**
 * @brief Cross product.
 * @param v1 Left operand.
 * @param v2 Right operand.
 * @return `v1 x v2`, perpendicular to both operands.
 */
static inline V3 V3cross(V3 v1, V3 v2) {
	return (V3){{
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
	}};
}

/**
 * @brief 4-component vector.
 *
 * Components are accessible either by name (`x`, `y`, `z`, `w`) or by index
 * (`comp[0]` .. `comp[3]`). The type is 16-byte aligned.
 */
typedef union V4 {
	struct {
		double x; /**< First component. */
		double y; /**< Second component. */
		double z; /**< Third component. */
		double w; /**< Fourth component. */
	};
	alignas(16) double comp[4]; /**< Indexed, 16-byte aligned component view. */
} V4;

/**
 * @brief Component-wise addition.
 * @param v1 Left operand.
 * @param v2 Right operand.
 * @return `v1 + v2`.
 */
static inline V4 V4add(V4 v1, V4 v2) {
	return (V4){{ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w }};
}

/**
 * @brief Component-wise subtraction.
 * @param v1 Left operand.
 * @param v2 Right operand.
 * @return `v1 - v2`.
 */
static inline V4 V4sub(V4 v1, V4 v2) {
	return (V4){{ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w }};
}

/**
 * @brief Dot product.
 * @param v1 Left operand.
 * @param v2 Right operand.
 * @return Scalar dot product of @p v1 and @p v2.
 */
static inline double V4dot(V4 v1, V4 v2) {
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
}

/**
 * @brief Euclidean length.
 * @param v Vector to measure.
 * @return Magnitude (norm) of @p v.
 */
static inline double V4mag(V4 v) {
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

/**
 * @brief Normalize to unit length.
 * @param v Vector to normalize; must be non-zero.
 * @return Unit vector in the direction of @p v.
 */
static inline V4 V4norm(V4 v) {
	double mag = V4mag(v);
	return (V4){{ v.x / mag, v.y / mag, v.z / mag, v.w / mag }};
}

/**
 * @brief Multiply by a scalar.
 * @param v Vector to scale.
 * @param s Scale factor.
 * @return `v * s`.
 */
static inline V4 V4scale(V4 v, double s) {
	return (V4){{ v.x * s, v.y * s, v.z * s, v.w * s }};
}

/**
 * @brief Angle between two vectors.
 * @param v1 First vector; must be non-zero.
 * @param v2 Second vector; must be non-zero.
 * @return Angle between @p v1 and @p v2 in radians, in `[0, pi]`.
 */
static inline double V4angle(V4 v1, V4 v2) {
	return acos(V4dot(v1, v2) / (V4mag(v1) * V4mag(v2)));
}

/**
 * @brief Euclidean distance between two points.
 * @param v1 First point.
 * @param v2 Second point.
 * @return Distance between @p v1 and @p v2.
 */
static inline double V4dist(V4 v1, V4 v2) {
	return V4mag(V4sub(v1, v2));
}

/**
 * @brief Linear interpolation.
 * @param v1 Value at `t == 0`.
 * @param v2 Value at `t == 1`.
 * @param t Interpolation factor, normally in `[0, 1]`.
 * @return `v1 * (1 - t) + v2 * t`.
 */
static inline V4 V4lerp(V4 v1, V4 v2, double t) {
	return V4add(V4scale(v1, (1 - t)), V4scale(v2, t));
}

/* ------------------------------------------------------------------------- */
/* Variable-size vectors                                                     */
/* ------------------------------------------------------------------------- */

/**
 * @brief Declare a fixed-size vector type backed by a `double` array.
 *
 * @code
 * V(Vec8, 8) // typedef struct { double comp[8]; } Vec8;
 * @endcode
 *
 * The resulting type is layout-compatible with `double[n]` and can therefore
 * be passed to the variable-size functions below via its `comp` member.
 */
#define V(name, n)                    \
	typedef struct {                  \
		alignas(16) double comp[n]; \
	} name;

/**
 * @brief Component-wise addition of two vectors.
 * @param[out] res Destination vector; must not overlap @p v1 or @p v2.
 * @param[in]  v1  Left operand.
 * @param[in]  v2  Right operand.
 * @param[in]  size Number of components.
 * @return @p res.
 */
double *Vadd(double *restrict res, double *restrict v1, double *restrict v2, size_t size);

/**
 * @brief Component-wise subtraction of two vectors.
 * @param[out] res Destination vector; must not overlap @p v1 or @p v2.
 * @param[in]  v1  Left operand.
 * @param[in]  v2  Right operand.
 * @param[in]  size Number of components.
 * @return @p res.
 */
double *Vsub(double *restrict res, double *restrict v1, double *restrict v2, size_t size);

/**
 * @brief Dot product of two vectors.
 * @param[in] v1   Left operand.
 * @param[in] v2   Right operand.
 * @param[in] size Number of components.
 * @return Scalar dot product of @p v1 and @p v2.
 */
double Vdot(double *restrict v1, double *restrict v2, size_t size);

/**
 * @brief Euclidean length of a vector.
 * @param[in] v    Vector to measure.
 * @param[in] size Number of components.
 * @return Magnitude (norm) of @p v.
 */
double Vmag(double *restrict v, size_t size);

/**
 * @brief Normalize a vector to unit length.
 * @param[out] res  Destination vector; must not overlap @p v.
 * @param[in]  v    Vector to normalize; must be non-zero.
 * @param[in]  size Number of components.
 * @return @p res.
 */
double *Vnorm(double *restrict res, double *restrict v, size_t size);

/**
 * @brief Multiply a vector by a scalar.
 * @param[out] res  Destination vector; must not overlap @p v.
 * @param[in]  v    Vector to scale.
 * @param[in]  s    Scale factor.
 * @param[in]  size Number of components.
 * @return @p res.
 */
double *Vscale(double *restrict res, double *restrict v, double s, size_t size);

/**
 * @brief Angle between two vectors.
 * @param[in] v1   First vector; must be non-zero.
 * @param[in] v2   Second vector; must be non-zero.
 * @param[in] size Number of components.
 * @return Angle between @p v1 and @p v2 in radians, in `[0, pi]`.
 */
double Vangle(double *restrict v1, double *restrict v2, size_t size);

/**
 * @brief Euclidean distance between two points.
 * @param[in] v1   First point.
 * @param[in] v2   Second point.
 * @param[in] size Number of components.
 * @return Distance between @p v1 and @p v2.
 */
double Vdist(double *restrict v1, double *restrict v2, size_t size);

/**
 * @brief Linear interpolation between two vectors.
 * @param[out] res  Destination vector; must not overlap the inputs.
 * @param[in]  v1   Value at `t == 0`.
 * @param[in]  v2   Value at `t == 1`.
 * @param[in]  t    Interpolation factor, normally in `[0, 1]`.
 * @param[in]  size Number of components.
 * @return @p res.
 */
double *Vlerp(double *restrict res, double *restrict v1, double *restrict v2, double t, size_t size);

#endif /* VECTOR_H */
