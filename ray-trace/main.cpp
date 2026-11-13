#include "vector.hpp"

#include <iostream>

typedef struct R3 {
	V3 orig;
	V3 dir;
}

typedef struct Sphere {
	V3     center;
	double radius;
} Sphere;

bool sphere_hit(Sphere s, V3 r) { // fix me!!! ray vs raycast vs rayat vs V3
	// sphere: x^2 + y^2 + z^2 = r^2
	// for a center: (C_x-x)^2 + (C_y-y)^2 + (C_z-z)^2 = r^2
	// from surface point to center: C-P
	// if we dot (C-P) against itself, we get: (C_x-x)^2 + (C_y-y)^2 + (C_z-z)^2. so,
	// (C-P) . (C-P) = r^2
	// since P is our ray, we can expand: (C-(Q-td)) . (C-(Q-td)) = r^2
	// we can get freaky with algebra and expanding the dot and end up with,
	// (d.d)t^2 - 2d(C-Q)t + (C-Q).(C-Q)-r^2 = 0
	// this is a quadratic where:
	// a = d.d
	// b = -2d(C-Q)
	// c = (C-Q).(C-Q)-r^2
	// all in terms of t and obviously we can use the quadratic formula:
	double a = r.dir * r.dir;
	double b = -2 * r.dir * (s.center * r.orig);
	double c = (s.center * r.orig) * (s.center * r.orig) - s.radius * s.radius;
	return (b * b - 4 * a * c) >= 0;
}

void write_color(V3 color) {
	double r = color.x;
	double g = color.y;
	double b = color.z;

	int rbyte = int(255.999 * r);
	int gbyte = int(255.999 * g);
	int bbyte = int(255.999 * b);

	std::cout << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

static inline V3 rayat(R3 r, double t) {
	return r.orig + t * r.dir;
}

// create a gradient
V3 ray_color(V3 rc) {
	if (sphere_hit(Sphere{ 0, 0, -1, .5 }, rc))
		return V3{ 1, .5, .5 };
	V3     dir = V3norm(rc);
	double a   = .5 * (dir.y + 1);
	return (1 - a) * V3{ 1, 1, 1 } + a * V3{ .5, .5, 1 }; // lerp between colors
}

// real and virtual image setup
double width        = 500;
double height       = 500;
double aspect_ratio = width / height;
double view_width   = width;
double view_height  = height;

// camera
V3 eye    = { 0, 0, 0 };
V3 up     = { 0, 1, 0 };
V3 target = { 0, 0, 1 };

// viewport
V3 view_u = { view_width, 0, 0 };
V3 view_v = { 0, -view_height, 0 }; // negative so that it goes from top to bottom

// pixel delta / distance between a frag/pixel
V3 delta_u = view_u / width;
V3 delta_v = view_v / height;

// calculate upper left frag
V3 upper_left = eye - target - view_u / 2.0 - view_v / 2.0;

int main() {
	std::cout << "P3\n"
	          << width
	          << ' '
	          << height
	          << "\n255\n"; // ppm header

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			V3 pixel_center = upper_left + (delta_u * x + delta_v * y) * 0.5;
			R3 ray          = R3{ eye, pixel_center - eye };
			V3 raycast      = rayat(ray, 1);

			V3 frag_color = ray_color(raycast);
			write_color(frag_color);
		}
	}

	return 0;
}
