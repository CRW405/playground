#include "vector.h"

#include <stdio.h>
#include <stdlib.h>

static inline V3 at(V3 orig, V3 dir, float t) {
	return (V3){
		orig.x + dir.x * t,
		orig.y + dir.y * t,
		orig.z + dir.z * t
	};
}

int    width        = 500;
int    height       = 500;
double aspect_ratio = width / height;
int    view_width   = width;
int    view_height  = height;

// camera
V3 eye    = (V3){ 0, 0, 0 };
V3 up     = (V3){ 0, 1, 0 };
V3 target = (V3){ 0, 0, 1 }; // focal length???

// viewport
V3 view_u = (V3){ view_width, 0, 0 };
V3 view_v = (V3){ 0, -view_height, 0 }; // negative so that it goes from top to bottom ???

// pixel delta / distance between a frag/pixel
V3 delta_u = (V3){ view_u.x / width, 0, 0 };
V3 delta_v = (V3){ 0, view_v.y / height, 0 };

// calculate upper left frag
V3 upper_left = (V3){
	eye.x - target.x - view_u.x / 2,
	eye.y - target.y - view_u.y / 2,
	eye.z - target.z
};
V3 pixel_center = V3add(upper_left, V3scale(V3add(delta_u, delta_v), .5)); // center of the upper left pixel

int main() {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			V3 pixel_center = V3add(upper_left, V3scale(V3add(V3scale(delta_u, x), V3scale(delta_v, y)), .5));
			// finish me
		}
	}

	return 0;
}
