#include "renderer.h"

// From pixman-combine32.h -> https://gitlab.freedesktop.org/pixman/pixman/-/blob/fdd716109787ef825f9eb88f73447297c43e5c10/pixman/pixman-combine32.h
#define MUL_UN8(a, b, t) ((t) = (a) * (uint16_t)(b) + 0x80, ((((t) >> 8) + (t)) >> 8))

sRGBA BlendAlpha(sRGBA src, sRGBA backdrop, uint8_t opacity) {
	if (src.a == 255) return src;
	else if (src.a == 0 || opacity == 0) return backdrop;

	int32_t t;
	src.a = MUL_UN8(src.a, opacity, t);

	sRGBA out;
	out.a = src.a + backdrop.a - MUL_UN8(src.a, backdrop.a, t);
	out.r = backdrop.r + (src.r - backdrop.r) * src.a / out.a;
	out.g = backdrop.g + (src.g - backdrop.g) * src.a / out.a;
	out.b = backdrop.b + (src.b - backdrop.b) * src.a / out.a;

	return out;
}

