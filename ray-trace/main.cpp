#include "vector.hpp"

int    width        = 500;
int    height       = 500;
double aspect_ratio = static_cast<double>(width) / height;
int    view_width   = width;
int    view_height  = height;

// camera
V3 eye    = { 0, 0, 0 };
V3 up     = { 0, 1, 0 };
V3 target = { 0, 0, 1 }; // focal length???

// viewport
V3 view_u = { static_cast<double>(view_width), 0, 0 };
V3 view_v = { 0, -static_cast<double>(view_height), 0 }; // negative so that it goes from top to bottom ???

// pixel delta / distance between a frag/pixel
V3 delta_u = view_u / width;
V3 delta_v = view_v / height;

// calculate upper left frag
V3 upper_left = eye - target - view_u / 2.0 - view_v / 2.0;

int main() {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			V3 pixel_center = upper_left + (delta_u * x + delta_v * y) * 0.5;
			static_cast<void>(pixel_center);
			// finish me
		}
	}

	return 0;
}
