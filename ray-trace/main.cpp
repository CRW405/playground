#include "vector.hpp"

#include <iostream>

void write_color(V3 color) {
	double r = color.x;
	double g = color.y;
	double b = color.z;

	int rbyte = int(255.999 * r);
	int gbyte = int(255.999 * g);
	int bbyte = int(255.999 * b);

	std::cout << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

static inline V3 rayat(V3 orig, V3 dir, double t) {
	return orig + t * dir;
}

// create a gradient
V3 ray_color(V3 ray) {
	V3     dir = V3norm(ray);
	double a   = .5 * (dir.y + 1);
	return (1 - a) * V3{ 1, 1, 1 } + a * V3{ .5, .7, 1 }; // lerp between colors
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
			V3 ray_dir      = pixel_center - eye;
			V3 ray          = rayat(eye, ray_dir, 1);

			V3 frag_color = ray_color(ray);
			write_color(frag_color);
		}
	}

	return 0;
}
